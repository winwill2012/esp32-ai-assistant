#ifndef IOT_AI_CONTROLLER_RECORDING_H
#define IOT_AI_CONTROLLER_RECORDING_H

#include "DoubaoSTT.h"

#define RECORDING_POWER_THRESHOLD 5000
#define RECORDING_MAX_IDLE_TIME 1000

class RecordingManager {
public:
    explicit RecordingManager(DoubaoSTT &sttClient);

    ~RecordingManager();

    void begin();

private:
    DoubaoSTT _sttClient;
    float _soundPowerThreshold;
    uint32_t _maxIdleTimeInMs;
    size_t _recordingBufferSize;
    uint8_t *_recordingBuffer;
};

#endif //IOT_AI_CONTROLLER_RECORDING_H
