#ifndef ESP32_AI_ASSISTANT_AUDIOPLAYER_H
#define ESP32_AI_ASSISTANT_AUDIOPLAYER_H

#include "Arduino.h"
#include <vector>

#define MAX98357_I2S_NUM  I2S_NUM_0
#define SAMPLE_RATE       16000
#define MAX98357_DOUT     38
#define MAX98357_LRC      40
#define MAX98357_BCLK     39

struct PlayAudioTask {
    size_t length;
    uint8_t *data;
};

class AudioPlayer {
public:
    static void begin();

    static void publishTask(PlayAudioTask task);

    static void resetTaskQueue();

    static inline QueueHandle_t getTaskQueue();

    static std::vector<int16_t> adjustVolume(PlayAudioTask task, float volumeRatio);

private:
    static QueueHandle_t _taskQueue;
};


#endif //ESP32_AI_ASSISTANT_AUDIOPLAYER_H
