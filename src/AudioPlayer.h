#ifndef ESP32_AI_ASSISTANT_AUDIOPLAYER_H
#define ESP32_AI_ASSISTANT_AUDIOPLAYER_H

#include "Arduino.h"
#include "driver/i2s.h"

#define SAMPLE_RATE 16000
#define MAX98357_DOUT  38
#define MAX98357_LRC   40
#define MAX98357_BCLK  39

struct PlayAudioTask {
    size_t length;
    uint8_t *data;
};

class AudioPlayer {
public:
    static AudioPlayer &getInstance();

    void begin();

    void publishTask(PlayAudioTask task);

    QueueHandle_t getTaskQueue();

private:
    AudioPlayer();

    AudioPlayer(const AudioPlayer &) = delete;

    AudioPlayer &operator=(const AudioPlayer &) = delete;

    static AudioPlayer instance;
    QueueHandle_t _taskQueue;
};


#endif //ESP32_AI_ASSISTANT_AUDIOPLAYER_H
