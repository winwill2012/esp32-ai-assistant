#ifndef DOUBAO_TTS_H
#define DOUBAO_TTS_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"
#include "vector"

class DoubaoTTS : public WebSocketsClient {
public:
    DoubaoTTS();

    void eventCallback(WStype_t type, uint8_t *payload, size_t length) const;

    void begin();

    static String buildFullClientRequest(const String &text);

    void parseResponse(const uint8_t *response) const;

    void synth(const String &text, bool disconnectAfter);

private:
    SemaphoreHandle_t _taskFinished;
};

#endif
