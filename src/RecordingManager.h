#ifndef IOT_AI_CONTROLLER_RECORDING_H
#define IOT_AI_CONTROLLER_RECORDING_H

#include <freertos/ringbuf.h>
#include "DoubaoSTT.h"

#define MICROPHONE_I2S_NUM          I2S_NUM_1
#define AUDIO_SAMPLE_RATE           16000
#define AUDIO_RECORDING_BUFFER_SIZE (160 * sizeof(int16_t)) // 10ms音频数据
#define MICROPHONE_I2S_BCLK         42
#define MICROPHONE_I2S_LRC          2
#define MICROPHONE_I2S_DOUT         1

class RecordingManager {
public:
    explicit RecordingManager(DoubaoSTT &sttClient);

    [[noreturn]] void begin();

    DoubaoSTT &getSttClient();

    RingbufHandle_t getRingBuffer();

private:
    DoubaoSTT _sttClient;
    RingbufHandle_t _ringBuffer;
};

#endif //IOT_AI_CONTROLLER_RECORDING_H
