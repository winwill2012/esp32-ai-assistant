#ifndef DOUBAO_ASR_H
#define DOUBAO_ASR_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "WebSocketASR.h"
#include <vector>

#define STT_TASK_COMPLETED_EVENT (1<<1)

// 默认头部
constexpr byte DoubaoTTSDefaultFullClientWsHeader[] = {0x11, 0x10, 0x10, 0x00};
constexpr byte DoubaoTTSDefaultAudioOnlyWsHeader[] = {0x11, 0x20, 0x10, 0x00};
constexpr byte DoubaoTTSDefaultLastAudioWsHeader[] = {0x11, 0x22, 0x10, 0x00};

class DoubaoASR final : public WebSocketASR {
public:
    DoubaoASR();

    void eventCallback(WStype_t type, uint8_t *payload, size_t length);

    void parseResponse(const uint8_t *response);

    void buildFullClientRequest();

    void buildAudioOnlyRequest(uint8_t *audio, size_t size, bool lastPacket);

    void recognize(WebSocketASRTask task) override;

private:
    EventGroupHandle_t _eventGroup;
    bool _firstPacket;
    std::vector<uint8_t> _requestBuilder;
};

#endif
