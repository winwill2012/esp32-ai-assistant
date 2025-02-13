#ifndef IOT_AI_CONTROLLER_DOUBAOSTT_H
#define IOT_AI_CONTROLLER_DOUBAOSTT_H
#ifndef DOUBAO_STT_H
#define DOUBAO_STT_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "driver/i2s.h"
#include <vector>

// 常量定义
const byte PROTOCOL_VERSION = 0b0001;
const byte DEFAULT_HEADER_SIZE = 0b0001;
const byte PROTOCOL_VERSION_BITS = 4;
const byte HEADER_BITS = 4;
const byte MESSAGE_TYPE_BITS = 4;
const byte MESSAGE_TYPE_SPECIFIC_FLAGS_BITS = 4;
const byte MESSAGE_SERIALIZATION_BITS = 4;
const byte MESSAGE_COMPRESSION_BITS = 4;
const byte RESERVED_BITS = 8;
// Message Type
const byte CLIENT_FULL_REQUEST = 0b0001;
const byte CLIENT_AUDIO_ONLY_REQUEST = 0b0010;
const byte SERVER_FULL_RESPONSE = 0b1001;
const byte SERVER_ACK = 0b1011;
const byte SERVER_ERROR_RESPONSE = 0b1111;
// Message Type Specific Flags
const byte NO_SEQUENCE = 0b0000;
const byte POS_SEQUENCE = 0b0001;
const byte NEG_SEQUENCE = 0b0010;
const byte NEG_SEQUENCE_1 = 0b0011;
// Message Serialization
const byte NO_SERIALIZATION = 0b0000;
const byte JSON = 0b0001;
const byte THRIFT = 0b0011;
const byte CUSTOM_TYPE = 0b1111;
// Message Compression
const byte NO_COMPRESSION = 0b0000;
const byte GZIP = 0b0001;
const byte CUSTOM_COMPRESSION = 0b1111;
// 默认头部
const byte DefaultFullClientWsHeader[] = {0x11, 0x10, 0x10, 0x00};
const byte DefaultAudioOnlyWsHeader[] = {0x11, 0x20, 0x10, 0x00};
const byte DefaultLastAudioWsHeader[] = {0x11, 0x22, 0x10, 0x00};


class DoubaoSTT : public WebSocketsClient {
public:
    DoubaoSTT(i2s_port_t i2SPort, const String &appId, const String &token, const String &host,
              int port, const String &url, int i2sDout, int i2sBclk, int i2sLrc);

    void setupINMP441() const;

    void eventCallback(WStype_t type, uint8_t *payload, size_t length);

    void begin();

    void parseResponse(const uint8_t *response) const;

    std::vector<uint8_t> buildFullClientRequest();

    static std::vector<uint8_t> buildAudioOnlyRequest(uint8_t *audio, size_t size, bool lastPacket);

    void recognize(uint8_t *audio, size_t size, bool firstPacket, bool lastPacket);

private:
    String _appId;
    String _token;
    String _host;
    uint16_t _port;
    String _url;
    String _voiceType;
    String _emotion;
    i2s_port_t _i2sNumber;
    int _i2sDout;
    int _i2sBclk;
    int _i2sLrc;
    SemaphoreHandle_t _available;
};

#endif

#endif
