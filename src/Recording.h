#ifndef IOT_AI_CONTROLLER_RECORDING_H
#define IOT_AI_CONTROLLER_RECORDING_H

#include "DoubaoSTT.h"

#define RECORDING_POWER_THRESHOLD 5000

class RecordingManager {
public:
    explicit RecordingManager(DoubaoSTT sttClient);

    ~RecordingManager();

    [[noreturn]] void begin();

private:
    DoubaoSTT _sttClient;
    float _soundPowerThreshold;
    size_t _recordingBufferSize;
    std::vector<uint8_t> _recordingBuffer;
};

#endif //IOT_AI_CONTROLLER_RECORDING_H
