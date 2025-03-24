#include <DoubaoSTT.h>
#include "RecordingManager.h"
#include <Settings.h>

#include <utility>
#include "Utils.h"
#include "LvglDisplay.h"
#include "GlobalState.h"

RecordingManager::RecordingManager(DoubaoSTT sttClient) : _sttClient(std::move(sttClient)) {
    constexpr i2s_config_t i2s_config = {
        .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // 这里的左右声道要和电路保持一致
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL6,
        .dma_buf_count = 4,
        .dma_buf_len = 1024,
        .use_apll = false
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
    _ringBuffer = xRingbufferCreate(1024 * 32, RINGBUF_TYPE_BYTEBUF);
}

[[noreturn]] void consumeBufferedData(void *arg) {
    auto *instance = static_cast<RecordingManager *>(arg);
    size_t bytes_read;
    bool firstPacket = true;
    auto lastPacketBuff = std::vector<uint8_t>();
    lastPacketBuff.push_back(0);
    while (true) {
        auto *buffer = static_cast<uint8_t *>(xRingbufferReceive(instance->getRingBuffer(), &bytes_read,
                                                                 pdMS_TO_TICKS(Settings::getSpeakPauseDuration())));
        if (buffer == nullptr) {
            if (!firstPacket) {
                instance->getSttClient().recognize(lastPacketBuff.data(), lastPacketBuff.size(), firstPacket, true);
                firstPacket = true;
            }
        } else {
            instance->getSttClient().recognize(buffer, bytes_read, firstPacket, false);
            if (firstPacket) {
                firstPacket = false;
            }
            vRingbufferReturnItem(instance->getRingBuffer(), (void *) buffer);
        }
        vTaskDelay(1);
    }
}

[[noreturn]] void RecordingManager::begin() {
    size_t bytesRead;
    xTaskCreate(consumeBufferedData, "consumeBufferTask", 1024 * 8, this, 1, nullptr);
    const auto buffer = static_cast<uint8_t *>(ps_malloc(AUDIO_RECORDING_BUFFER_SIZE));
    while (true) {
        xEventGroupWaitBits(GlobalState::getEventGroup(), GlobalState::getEventBits({Listening}),
                            false, false, portMAX_DELAY);
        const esp_err_t err = i2s_read(MICROPHONE_I2S_NUM, buffer, AUDIO_RECORDING_BUFFER_SIZE,
                                       &bytesRead, portMAX_DELAY);
        if (err == ESP_OK) {
            if (calculateSoundRMS(buffer, bytesRead) > Settings::getRecordingRmsThreshold()) {
                LvglDisplay::updateRecordingState(true);
                xRingbufferSend(_ringBuffer, buffer, bytesRead, portMAX_DELAY);
            } else {
                LvglDisplay::updateRecordingState(false);
            }
        }
        vTaskDelay(1);
    }
}

inline RingbufHandle_t RecordingManager::getRingBuffer() const {
    return _ringBuffer;
}

inline DoubaoSTT &RecordingManager::getSttClient() {
    return _sttClient;
}
