#ifndef DOUBAO_STT_H
#define DOUBAO_STT_H

#include <Arduino.h>
#include <CozeLLMAgent.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"
#include <vector>

// 默认头部
constexpr byte DefaultFullClientWsHeader[] = {0x11, 0x10, 0x10, 0x00};
constexpr byte DefaultAudioOnlyWsHeader[] = {0x11, 0x20, 0x10, 0x00};
constexpr byte DefaultLastAudioWsHeader[] = {0x11, 0x22, 0x10, 0x00};

class DoubaoSTT : public WebSocketsClient {
public:
    DoubaoSTT(const CozeLLMAgent &llmAgent, const String &appId, const String &token,
              const String &host, int port, const String &url);

    void eventCallback(WStype_t type, uint8_t *payload, size_t length);

    void begin();

    void parseResponse(const uint8_t *response);

    void buildFullClientRequest();

    void buildAudioOnlyRequest(uint8_t *audio, size_t size, bool lastPacket);

    void recognize(uint8_t *audio, size_t size, bool firstPacket, bool lastPacket);

private:
    String _appId;
    String _token;
    String _host;
    uint16_t _port;
    String _url;
    String _voiceType;
    String _emotion;
    CozeLLMAgent _llmAgent;
    bool _firstPacket;
    SemaphoreHandle_t _taskFinished;
    std::vector<uint8_t> _requestBuilder;
};

#endif
