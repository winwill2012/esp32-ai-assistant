#ifndef IOT_AI_CONTROLLER_RECORDING_H
#define IOT_AI_CONTROLLER_RECORDING_H

#include "DoubaoSTT.h"

#define MICROPHONE_I2S_NUM          I2S_NUM_1
#define AUDIO_SAMPLE_RATE           16000
#define AUDIO_RECORDING_BUFFER_SIZE (1600 * sizeof(int16_t)) // 100ms音频数据
#define MICROPHONE_I2S_BCLK         42
#define MICROPHONE_I2S_LRC          2
#define MICROPHONE_I2S_DOUT         1

class RecordingManager {
public:
    explicit RecordingManager(DoubaoSTT &sttClient);

    [[noreturn]] void begin();

private:
    DoubaoSTT _sttClient;
    std::vector<uint8_t> _recordingBuffer;
    std::vector<uint8_t> _lastRecordingBuffer;
};

#endif //IOT_AI_CONTROLLER_RECORDING_H
