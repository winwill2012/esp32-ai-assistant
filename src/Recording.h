#ifndef IOT_AI_CONTROLLER_RECORDING_H
#define IOT_AI_CONTROLLER_RECORDING_H

#include "driver/i2s.h"
#include "DoubaoSTT.h"

#define RECORDING_BUFFER_SIZE 3200
#define RECORDING_POWER_THRESHOLD 5000
#define RECORDING_MAX_IDLE_TIME 1000

class RecordingManager {
public:
    explicit RecordingManager(DoubaoSTT &sttClient);

    ~RecordingManager();

    void beginRecording();

private:
    DoubaoSTT _sttClient;
    float _soundPowerThreshold;
    uint32_t _maxIdleTimeInMs;
    uint8_t *_recordingBuffer;
    uint16_t _recordingBufferSize;
};

#endif //IOT_AI_CONTROLLER_RECORDING_H
