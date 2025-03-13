#include <DoubaoSTT.h>

#include "RecordingManager.h"
#include <Settings.h>
#include <utility>
#include "Utils.h"
#include "GlobalState.h"

RecordingManager::RecordingManager(DoubaoSTT sttClient) : _sttClient(std::move(sttClient)) {
    constexpr i2s_config_t i2s_config = {
        .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .use_apll = true
    };
    constexpr i2s_pin_config_t pin_config = {
        .bck_io_num = MICROPHONE_I2S_BCLK,
        .ws_io_num = MICROPHONE_I2S_LRC,
        .data_out_num = -1,
        .data_in_num = MICROPHONE_I2S_DOUT
    };

    i2s_driver_install(MICROPHONE_I2S_NUM, &i2s_config, 0, nullptr);
    i2s_set_pin(MICROPHONE_I2S_NUM, &pin_config);
    i2s_zero_dma_buffer(MICROPHONE_I2S_NUM);

    _recordingBuffer = std::vector<uint8_t>(AUDIO_RECORDING_BUFFER_SIZE);
    _lastRecordingBuffer = std::vector<uint8_t>(AUDIO_RECORDING_BUFFER_SIZE);
}

[[noreturn]] void RecordingManager::begin() {
    size_t bytesRead;
    bool hasSoundFlag = false;
    unsigned long idleBeginTime = 0;
    bool firstPacket = true;
    GlobalState::setState(Listening);
    while (true) {
        if (GlobalState::getState() != Listening) {
            continue;
        }
        const esp_err_t err = i2s_read(MICROPHONE_I2S_NUM, _recordingBuffer.data(), AUDIO_RECORDING_BUFFER_SIZE,
                                       &bytesRead, portMAX_DELAY);
        if (err == ESP_OK) {
            // 如有有声音
            if (calculateSoundRMS(_recordingBuffer.data(), bytesRead) > Settings::getBackgroundNoiseRMS()) {
                hasSoundFlag = true;
                if (firstPacket) {
                    // 发送第一个数据包时，先发送能够检测到声音的前一帧数据(因为识别有误差，不发前一帧数据，语音识别会丢失一开始的数据)
                    _sttClient.recognize(_lastRecordingBuffer.data(), bytesRead, firstPacket, false);
                    firstPacket = false;
                }
                _sttClient.recognize(_recordingBuffer.data(), bytesRead, firstPacket, false);
                idleBeginTime = 0;
            } else if (hasSoundFlag) {
                // 如果之前有声音，本次没有声音
                if (idleBeginTime == 0) {
                    idleBeginTime = millis();
                } else if (millis() - idleBeginTime > Settings::getRecordingSilenceTime()) {
                    _sttClient.recognize(_recordingBuffer.data(), bytesRead, firstPacket, true);
                    hasSoundFlag = false;
                    firstPacket = true;
                }
            }
            _lastRecordingBuffer = _recordingBuffer;
        }
    }
}
