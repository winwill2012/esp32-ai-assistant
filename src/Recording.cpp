#include "Recording.h"
#include "Utils.h"
#include "GlobalState.h"

RecordingManager::RecordingManager(DoubaoSTT &sstClient) : _sttClient(sstClient) {
    _soundPowerThreshold = RECORDING_POWER_THRESHOLD;
    _maxIdleTimeInMs = RECORDING_MAX_IDLE_TIME;
    _recordingBufferSize = RECORDING_BUFFER_SIZE;
    _recordingBuffer = static_cast<uint8_t *>(malloc(_recordingBufferSize));
}

RecordingManager::~RecordingManager() {
    delete _recordingBuffer;
    _recordingBuffer = nullptr;
}

void RecordingManager::beginRecording() {
    globalState = Listening;
    size_t bytesRead;
    bool hasSoundFlag = false;
    unsigned long idleBeginTime = 0;
    bool firstPacket = true;
    while (true) {
        if (globalState == Listening) {
            esp_err_t err = i2s_read(_sttClient.getI2sNumber(), _recordingBuffer,
                                     _recordingBufferSize, &bytesRead, portMAX_DELAY);
            if (err == ESP_OK) {
                // 如有有声音
                if (hasSound(_recordingBuffer, bytesRead, _soundPowerThreshold)) {
                    Serial.println("识别到声音");
                    hasSoundFlag = true;
                    _sttClient.recognize(_recordingBuffer, bytesRead, firstPacket, false);
                    if (firstPacket) {
                        firstPacket = false;
                    }
                    idleBeginTime = 0;
                } else if (hasSoundFlag) {
                    // 如果之前有声音，本次没有声音
                    if (idleBeginTime == 0) {
                        idleBeginTime = millis();
                    } else if (millis() - idleBeginTime > _maxIdleTimeInMs) {
                        _sttClient.recognize(_recordingBuffer, bytesRead, firstPacket, true);
                        Serial.println("本次录音结束");
                        hasSoundFlag = false;
                        firstPacket = true;
                    }
                }
            }
        }
    }
}
