#ifndef IOT_AI_CONTROLLER_RECORDING_H
#define IOT_AI_CONTROLLER_RECORDING_H

#include "DoubaoSTT.h"

class RecordingManager {
public:
    explicit RecordingManager(DoubaoSTT sttClient);

    ~RecordingManager();

    [[noreturn]] void begin();

private:
    DoubaoSTT _sttClient;
    size_t _recordingBufferSize;
    std::vector<uint8_t> _recordingBuffer;
    std::vector<uint8_t> _lastRecordingBuffer;
};

#endif //IOT_AI_CONTROLLER_RECORDING_H
