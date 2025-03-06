#include "Recording.h"
#include <Settings.h>
#include <utility>
#include "Utils.h"
#include "GlobalState.h"

RecordingManager::RecordingManager(DoubaoSTT sttClient) : _sttClient(std::move(sttClient)) {
    _soundPowerThreshold = RECORDING_POWER_THRESHOLD;
    _recordingBufferSize = 4000; // 125ms的音频数据
    _recordingBuffer = std::vector<uint8_t>(_recordingBufferSize);
}

RecordingManager::~RecordingManager() = default;

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
        const esp_err_t err = i2s_read(_sttClient.getI2sNumber(), _recordingBuffer.data(), _recordingBufferSize,
                                       &bytesRead,
                                       portMAX_DELAY);
        if (err == ESP_OK) {
            // 如有有声音
            if (calculateSoundRMS(_recordingBuffer.data(), bytesRead) > Settings::getBackgroundNoiseRMS()) {
                hasSoundFlag = true;
                _sttClient.recognize(_recordingBuffer.data(), bytesRead, firstPacket, false);
                if (firstPacket) {
                    firstPacket = false;
                }
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
        }
    }
}
