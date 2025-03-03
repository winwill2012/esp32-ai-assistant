#ifndef DOUBAO_STT_H
#define DOUBAO_STT_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"
#include "LLMAgent.h"
#include <vector>

// 默认头部
const byte DefaultFullClientWsHeader[] = {0x11, 0x10, 0x10, 0x00};
const byte DefaultAudioOnlyWsHeader[] = {0x11, 0x20, 0x10, 0x00};
const byte DefaultLastAudioWsHeader[] = {0x11, 0x22, 0x10, 0x00};

class DoubaoSTT : public WebSocketsClient {
public:
    DoubaoSTT(const LLMAgent &llmAgent, i2s_port_t i2SPort, const String &appId, const String &token,
              const String &host,
              int port, const String &url, int i2sDout, int i2sBclk, int i2sLrc);

    void setupINMP441() const;

    void eventCallback(WStype_t type, uint8_t *payload, size_t length);

    void begin();

    void parseResponse(const uint8_t *response);

    void buildFullClientRequest();

    void buildAudioOnlyRequest(uint8_t *audio, size_t size, bool lastPacket);

    void recognize(uint8_t *audio, size_t size, bool firstPacket, bool lastPacket);

    i2s_port_t getI2sNumber() const;

private:
    String _appId;
    String _token;
    String _host;
    uint16_t _port;
    String _url;
    String _voiceType;
    String _emotion;
    i2s_port_t _i2sNumber;
    LLMAgent _llmAgent;
    int _i2sDout;
    int _i2sBclk;
    int _i2sLrc;
    SemaphoreHandle_t _taskFinished;
    std::vector<uint8_t> _requestBuilder;
};

#endif
