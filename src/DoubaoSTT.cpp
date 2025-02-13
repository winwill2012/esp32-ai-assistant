#include "DoubaoSTT.h"
#include "ArduinoJson.h"
#include "Utils.h"
#include <vector>

#define AUDIO_SAMPLE_RATE 441000

DoubaoSTT::DoubaoSTT(i2s_port_t i2sNumber, const String &appId, const String &token,
                     const String &host, int port, const String &url, int i2sDout, int i2sBclk, int i2sLrc) {
    _i2sNumber = i2sNumber;
    _appId = appId;
    _token = token;
    _host = host;
    _port = port;
    _url = url;
    _i2sDout = i2sDout;
    _i2sBclk = i2sBclk;
    _i2sLrc = i2sLrc;
    _available = xSemaphoreCreateBinary();
    setupINMP441();
}

void DoubaoSTT::eventCallback(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_PING:
            break;
        case WStype_ERROR:
            Serial.println("Connect error: ");
            for (size_t i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        case WStype_CONNECTED: {
            Serial.println("WebSocket connected");
            xSemaphoreGive(_available);
            break;
        }
        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected");
            xSemaphoreTake(_available, portMAX_DELAY);
            break;
        case WStype_TEXT: {
            Serial.println("收到TEXT回复: ");
            for (int i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        }
        case WStype_BIN:
            Serial.println("收到BIN回复: ");
            parseResponse(payload);
            break;
        default:
            break;
    }
}

[[noreturn]] void sttWebSocketLoop(void *ptr) {
    auto *client = static_cast<DoubaoSTT *>(ptr);
    while (true) {
        client->loop();
        vTaskDelay(1);
    }
}

void DoubaoSTT::begin() {
    if (isConnected()) {
        return;
    }
    setExtraHeaders(("Authorization: Bearer; " + _token).c_str());
    beginSSL(_host, _port, _url);
    onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
        this->eventCallback(type, payload, length);
    });
    xTaskCreate(sttWebSocketLoop, "sttWebSocketLoop", 4096, this, 1, nullptr);
}

void DoubaoSTT::setupINMP441() const {
    const i2s_config_t i2s_config = {
            .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
            .sample_rate = AUDIO_SAMPLE_RATE,
            .bits_per_sample = i2s_bits_per_sample_t(16),
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
            .intr_alloc_flags = 0,
            .dma_buf_count = 8,
            .dma_buf_len = 1024,
            .use_apll = false
    };
    const i2s_pin_config_t pin_config = {
            .bck_io_num = _i2sBclk,
            .ws_io_num = _i2sLrc,
            .data_out_num = -1,
            .data_in_num = _i2sDout
    };

    i2s_driver_install(_i2sNumber, &i2s_config, 0, NULL);
    i2s_set_pin(_i2sNumber, &pin_config);
    i2s_zero_dma_buffer(_i2sNumber);
}

std::vector<uint8_t> DoubaoSTT::buildFullClientRequest() {
    JsonDocument doc;
    JsonObject app = doc["app"].to<JsonObject>();
    app["appid"] = _appId;
    app["cluster"] = "volcengine_input_common";
    app["token"] = _token;
    JsonObject user = doc["user"].to<JsonObject>();
    user["uid"] = getChipId(nullptr);
    JsonObject request = doc["request"].to<JsonObject>();
    request["reqid"] = generateTaskId();
    request["nbest"] = 1;
    request["result_type"] = "full";
    request["sequence"] = 1;
    JsonObject audio = doc["audio"].to<JsonObject>();
    audio["format"] = "raw";
    audio["codec"] = "raw";
    audio["channel"] = 1;
    audio["rate"] = AUDIO_SAMPLE_RATE;
    String payloadStr;
    serializeJson(doc, payloadStr);

    uint8_t payload[payloadStr.length()];
    for (int i = 0; i < payloadStr.length(); i++) {
        payload[i] = static_cast<uint8_t>(payloadStr.charAt(i));
    }
    payload[payloadStr.length()] = '\0';
    uint8_t *payloadSize = int2Array(payloadStr.length());

    // 先写入报头（四字节）
    std::vector<uint8_t> clientRequest(DefaultFullClientWsHeader,
                                       DefaultFullClientWsHeader + sizeof(DefaultFullClientWsHeader));
    // 写入payload长度（四字节）
    clientRequest.insert(clientRequest.end(), payloadSize, payloadSize + 4);
    // 写入payload内容
    clientRequest.insert(clientRequest.end(), payload, payload + payloadStr.length());
    return clientRequest;
}

std::vector<uint8_t> DoubaoSTT::buildAudioOnlyRequest(uint8_t *audio, size_t size, bool lastPacket) {
    uint8_t *payloadLength = int2Array(size);

    std::vector<uint8_t> clientRequest;
    if (lastPacket) {
        // 先写入报头（四字节）
        clientRequest.insert(clientRequest.end(), DefaultLastAudioWsHeader,
                             DefaultLastAudioWsHeader + sizeof(DefaultLastAudioWsHeader));
    } else {
        // 先写入报头（四字节）
        clientRequest.insert(clientRequest.end(), DefaultAudioOnlyWsHeader,
                             DefaultAudioOnlyWsHeader + sizeof(DefaultAudioOnlyWsHeader));
    }

    // 写入payload长度（四字节）
    clientRequest.insert(clientRequest.end(), payloadLength, payloadLength + 4);
    // 写入payload内容
    clientRequest.insert(clientRequest.end(), audio, audio + size);
    return clientRequest;
}

void DoubaoSTT::recognize(uint8_t *audio, size_t size, bool firstPacket, bool lastPacket) {
    if (firstPacket && xSemaphoreTake(_available, 5000) == pdFALSE) {
        Serial.println("stt is busy");
        return;
    }
    if (firstPacket) {
        std::vector<uint8_t> payloadFullClientRequest = buildFullClientRequest();
        String base64 = base64_encode(payloadFullClientRequest.data(), payloadFullClientRequest.size());
        Serial.println(base64);
        sendBIN(payloadFullClientRequest.data(), payloadFullClientRequest.size());
    }
    std::vector<uint8_t> audioOnlyClientRequest = buildAudioOnlyRequest(audio, size, lastPacket);
    sendBIN(audioOnlyClientRequest.data(), audioOnlyClientRequest.size());
}

void DoubaoSTT::parseResponse(const uint8_t *response) const {
    const uint8_t messageType = response[1] >> 4;
    const uint8_t messageTypeSpecificFlags = response[1] & 0x0f;
    const uint8_t *payload = response + 4;

    Serial.printf("[语音识别] message type: %d\n", messageType);
    Serial.printf("[语音识别] messageTypeSpecificFlags: %d\n", messageTypeSpecificFlags);
    switch (messageType) {
        case 0b1001: {
            // 服务端下发包含识别结果的 full server response
            const uint32_t payloadSize = parseInt32(payload);
            payload += 4;
            String recognizeResult = parseString(payload, payloadSize);
            JsonDocument jsonResult;
            const DeserializationError err = deserializeJson(jsonResult, recognizeResult);
            if (err) {
                Serial.println("解析语音识别结果失败");
                return;
            }
            const int32_t code = jsonResult["code"];
            const String message = jsonResult["message"];
            const int32_t sequence = jsonResult["sequence"];
            const JsonArray result = jsonResult["result"].to<JsonArray>();
            Serial.println(result.size());
            if (!result) {
                Serial.printf("[语音识别]     code = %d\n", code);
                Serial.printf("[语音识别]  message = %s\n", message.c_str());
                Serial.printf("[语音识别] sequence = %d\n", sequence);
                for (const auto &item: result) {
                    String text = item["text"];
                    Serial.printf("[语音识别] 识别到文字: %s\n", text.c_str());
                }
            }
            // sequence小于0表示这是最后返回的一个分片，本次识别结束
            if (sequence < 0) {
                xSemaphoreGive(_available);
            }
            break;
        }
        case 0b1111: {
            // 服务端处理错误时下发的消息类型（如无效的消息格式，不支持的序列化方法等）
            const uint32_t errorCode = parseInt32(payload);
            payload += 4;
            const uint32_t messageLength = parseInt32(payload);
            payload += 4;
            String errorMessage = parseString(payload, messageLength);
            Serial.println("语音合成失败: ");
            Serial.printf("   errorCode =  %u\n", errorCode);
            Serial.printf("errorMessage =  %s\n", errorMessage.c_str());
            xSemaphoreGive(_available);
        }
        default: {
            break;
        }
    }
}
