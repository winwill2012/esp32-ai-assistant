#ifndef DOUBAO_TTS_H
#define DOUBAO_TTS_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"
#include "vector"

class DoubaoTTS : public WebSocketsClient {
public:
    DoubaoTTS(const String &appId, const String &token, const String &host, int port, const String &url);

    void eventCallback(WStype_t type, uint8_t *payload, size_t length) const;

    void begin();

    String buildFullClientRequest(const String &text) const;

    void parseResponse(const uint8_t *response) const;

    void synth(const String &text, bool disconnectAfter);

private:
    String _appId;
    String _token;
    String _host;
    uint16_t _port;
    String _url;
    SemaphoreHandle_t _taskFinished;
};

#endif
