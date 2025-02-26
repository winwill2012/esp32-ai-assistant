#include "Recording.h"
#include "Utils.h"
#include "GlobalState.h"

RecordingManager::RecordingManager(DoubaoSTT &sstClient) : _sttClient(sstClient) {
    _soundPowerThreshold = RECORDING_POWER_THRESHOLD;
    _maxIdleTimeInMs = RECORDING_MAX_IDLE_TIME;
    _recordingBufferSize = 3200;
    _recordingBuffer = static_cast<uint8_t *>(malloc(3200));
}

RecordingManager::~RecordingManager() {
    delete _recordingBuffer;
    _recordingBuffer = nullptr;
}

[[noreturn]] void RecordingManager::begin() {
    GlobalState::setEvents(EVENT_LISTENING);
    size_t bytesRead;
    bool hasSoundFlag = false;
    unsigned long idleBeginTime = 0;
    bool firstPacket = true;
    while (true) {
        GlobalState::waitAllEvents(EVENT_LISTENING, portMAX_DELAY); // 等待进入监听模式再录音
        const esp_err_t err = i2s_read(_sttClient.getI2sNumber(), _recordingBuffer, _recordingBufferSize, &bytesRead,
                                       portMAX_DELAY);
        if (err == ESP_OK) {
            // 如有有声音
            if (hasSound(_recordingBuffer, bytesRead, _soundPowerThreshold)) {
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
