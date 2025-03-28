#ifndef DOUBAO_TTS_H
#define DOUBAO_TTS_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"


class DoubaoTTS final : public WebSocketsClient {
public:
    DoubaoTTS();

    void eventCallback(WStype_t type, uint8_t *payload, size_t length);

    void begin();

    static String buildFullClientRequest(const String &text);

    void parseResponse(const uint8_t *response);

    void synth(const String &text, bool disconnectAfter);

    void interrupt(bool value);

private:
    bool _interrupted = false;
    unsigned long _taskStartTime = 0;
    size_t _audioSize = 0;
    SemaphoreHandle_t _taskFinished;
};

#endif
