#include <SPIFFS.h>
#include "Recording.h"
#include "Utils.h"

RecordingManager::RecordingManager(DoubaoSTT &sstClient) : _sttClient(sstClient) {
    _soundPowerThreshold = RECORDING_POWER_THRESHOLD;
    _maxIdleTimeInMs = RECORDING_MAX_IDLE_TIME;
    _recordingBufferSize = RECORDING_BUFFER_SIZE;
    _recordingBuffer = new uint8_t[_recordingBufferSize];
}

RecordingManager::~RecordingManager() {
    delete _recordingBuffer;
    _recordingBuffer = nullptr;
}

void RecordingManager::beginRecording() {
    size_t bytesRead;
    bool hasSoundFlag = false;
    unsigned long idleBeginTime = 0;
    bool firstPacket = true;
    File file = SPIFFS.open("/recording.pcm", FILE_WRITE);
    while (true) {
        esp_err_t err = i2s_read(_sttClient.getI2sNumber(), _recordingBuffer,
                                 _recordingBufferSize, &bytesRead, portMAX_DELAY);
        if (err == ESP_OK) {
            // 如有有声音
            if (hasSound(_recordingBuffer, bytesRead, _soundPowerThreshold)) {
                hasSoundFlag = true;
                file.write(_recordingBuffer, bytesRead);
                _sttClient.recognize(_recordingBuffer, bytesRead, firstPacket, false);
                if (firstPacket) {
                    firstPacket = false;
                }
                idleBeginTime = 0;
            } else if (hasSoundFlag) { // 如果之前有声音，本次没有声音
                if (idleBeginTime == 0) {
                    idleBeginTime = millis();
                } else if (millis() - idleBeginTime > _maxIdleTimeInMs) {
                    _sttClient.recognize(_recordingBuffer, bytesRead, firstPacket, true);
                    file.close();
                    Serial.println("本次录音结束");
                    break;
                }
            }
        } else {
            Serial.printf("读取录音信息失败: %d\n", err);
        }
    }
}