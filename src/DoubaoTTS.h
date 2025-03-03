#ifndef DOUBAO_TTS_H
#define DOUBAO_TTS_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"

class DoubaoTTS : public WebSocketsClient {
public:
    DoubaoTTS(i2s_port_t i2SPort, uint32_t sampleRate, String voice,
              const String &appId, const String &token,
              const String &host, int port,
              const String &url, int i2sDout, int i2sBclk, int i2sLrc);

    void setupMax98357() const;

    void eventCallback(const WStype_t type, uint8_t *payload, const size_t length);

    void begin();

    String buildFullClientRequest(const String emotion, const String &text) const;

    void parseResponse(uint8_t *response);

    void synth(const String &emotion, const String &text);

private:
    String _appId;
    String _token;
    String _host;
    uint16_t _port;
    String _url;
    String _voiceType;
    String _emotion;
    uint32_t _sampleRate;
    i2s_port_t _i2sNumber;
    int _i2sDout;
    int _i2sBclk;
    int _i2sLrc;
    SemaphoreHandle_t _taskFinished;
};

#endif
