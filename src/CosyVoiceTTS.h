#ifndef COSY_VOICE_TTS_H
#define COSY_VOICE_TTS_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"

class CosyVoiceTTS : public WebSocketsClient {
public:
    CosyVoiceTTS(i2s_port_t i2SPort, uint32_t sampleRate, String voice);

    void setupMax98357();

    void eventCallback(WStype_t type, uint8_t *payload, size_t length) const;

    void begin(const String &sk, const String &host, int port,
               const String &url, int i2sDout, int i2sBclk, int i2sLrc);

    String buildRunTask();

    static String buildContinueTask(const String &text);

    static String buildFinishTask();

    void tts(const String &text);

private:
    String voice;
    uint32_t sampleRate;
    i2s_port_t i2sNumber;
    int i2sDout;
    int i2sBclk;
    int i2sLrc;
    SemaphoreHandle_t connected;
    SemaphoreHandle_t taskStarted;
    SemaphoreHandle_t taskRunning;
};

#endif
