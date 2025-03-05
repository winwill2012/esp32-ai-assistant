#include "DoubaoSTT.h"
#include "ArduinoJson.h"
#include "Utils.h"
#include <Arduino.h>
#include <CozeLLMAgent.h>
#include <vector>

#define AUDIO_SAMPLE_RATE 16000

JsonDocument doc;

DoubaoSTT::DoubaoSTT(const CozeLLMAgent &llmAgent, i2s_port_t i2sNumber, const String &appId, const String &token,
                     const String &host, int port, const String &url, int i2sDout, int i2sBclk, int i2sLrc)
    : _llmAgent(llmAgent) {
    _i2sNumber = i2sNumber;
    _appId = appId;
    _token = token;
    _host = host;
    _port = port;
    _url = url;
    _i2sDout = i2sDout;
    _i2sBclk = i2sBclk;
    _i2sLrc = i2sLrc;
    _requestBuilder = std::vector<uint8_t>();
    _taskFinished = xSemaphoreCreateBinary();
    setupINMP441();
    begin();
}

void DoubaoSTT::eventCallback(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_PING:
        case WStype_ERROR:
        case WStype_CONNECTED:
        case WStype_DISCONNECTED:
        case WStype_TEXT:
            break;
        case WStype_BIN:
            parseResponse(payload);
            break;
        default:
            break;
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
}

void DoubaoSTT::setupINMP441() const {
    constexpr i2s_config_t i2s_config = {
        .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .use_apll = true
    };
    const i2s_pin_config_t pin_config = {
        .bck_io_num = _i2sBclk,
        .ws_io_num = _i2sLrc,
        .data_out_num = -1,
        .data_in_num = _i2sDout
    };

    i2s_driver_install(_i2sNumber, &i2s_config, 0, nullptr);
    i2s_set_pin(_i2sNumber, &pin_config);
    i2s_zero_dma_buffer(_i2sNumber);
}

void DoubaoSTT::buildFullClientRequest() {
    doc.clear();
    const JsonObject app = doc["app"].to<JsonObject>();
    app["appid"] = _appId;
    app["cluster"] = "volcengine_input_common";
    app["token"] = _token;
    const JsonObject user = doc["user"].to<JsonObject>();
    user["uid"] = getChipId(nullptr);
    const JsonObject request = doc["request"].to<JsonObject>();
    request["reqid"] = generateTaskId();
    request["nbest"] = 1;
    request["result_type"] = "full";
    request["sequence"] = 1;
    request["workflow"] = "audio_in,resample,partition,vad,fe,decode,nlu_punctuate";
    const JsonObject audio = doc["audio"].to<JsonObject>();
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
    std::vector<uint8_t> payloadSize = int2Array(payloadStr.length());

    _requestBuilder.clear();
    // 先写入报头（四字节）
    _requestBuilder.insert(_requestBuilder.end(), DefaultFullClientWsHeader,
                           DefaultFullClientWsHeader + sizeof(DefaultFullClientWsHeader));
    // 写入payload长度（四字节）
    _requestBuilder.insert(_requestBuilder.end(), payloadSize.begin(), payloadSize.end());
    // 写入payload内容
    _requestBuilder.insert(_requestBuilder.end(), payload, payload + payloadStr.length());
}

void DoubaoSTT::buildAudioOnlyRequest(uint8_t *audio, const size_t size, const bool lastPacket) {
    _requestBuilder.clear();
    std::vector<uint8_t> payloadLength = int2Array(size);

    if (lastPacket) {
        // 先写入报头（四字节）
        _requestBuilder.insert(_requestBuilder.end(), DefaultLastAudioWsHeader,
                               DefaultLastAudioWsHeader + sizeof(DefaultLastAudioWsHeader));
    } else {
        // 先写入报头（四字节）
        _requestBuilder.insert(_requestBuilder.end(), DefaultAudioOnlyWsHeader,
                               DefaultAudioOnlyWsHeader + sizeof(DefaultAudioOnlyWsHeader));
    }

    // 写入payload长度（四字节）
    _requestBuilder.insert(_requestBuilder.end(), payloadLength.begin(), payloadLength.end());
    // 写入payload内容
    _requestBuilder.insert(_requestBuilder.end(), audio, audio + size);
}

void DoubaoSTT::recognize(uint8_t *audio, const size_t size, const bool firstPacket, const bool lastPacket) {
    Serial.printf("语音识别: %d, firstPacket: %d, lastPacket: %d\n", size, firstPacket, lastPacket);
    if (firstPacket) {
        while (!isConnected()) {
            loop();
            vTaskDelay(1);
        }
        buildFullClientRequest();
        sendBIN(_requestBuilder.data(), _requestBuilder.size());
        loop();
    }
    buildAudioOnlyRequest(audio, size, lastPacket);
    sendBIN(_requestBuilder.data(), _requestBuilder.size());
    loop();
    if (lastPacket) {
        // 等待本次合成完毕
        while (xSemaphoreTake(_taskFinished, 0) == pdFALSE) {
            loop();
            vTaskDelay(1);
        }
        disconnect();
    }
}

void DoubaoSTT::parseResponse(const uint8_t *response) {
    const uint8_t messageType = response[1] >> 4;
    const uint8_t *payload = response + 4;
    switch (messageType) {
        case 0b1001: {
            // 服务端下发包含识别结果的 full server response
            const uint32_t payloadSize = parseInt32(payload);
            payload += 4;
            std::string recognizeResult = parseString(payload, payloadSize);
            JsonDocument jsonResult;
            const DeserializationError err = deserializeJson(jsonResult, recognizeResult);
            if (err) {
                Serial.println("解析语音识别结果失败");
                return;
            }
            const String reqId = jsonResult["reqid"];
            const int32_t code = jsonResult["code"];
            const String message = jsonResult["message"];
            const int32_t sequence = jsonResult["sequence"];
            const JsonArray result = jsonResult["result"];
            if (sequence < 0) {
                xSemaphoreGive(_taskFinished);
            }
            if (code == 1000 && result.size() > 0) {
                for (const auto &item: result) {
                    String text = item["text"];
                    if (sequence < 0) {
                        Serial.printf("[语音识别] 识别到文字: %s\n", text.c_str());
                        _llmAgent.begin(text);
                    }
                }
            } else {
                Serial.printf("未识别到文字: %d, %s\n", code, message.c_str());
            }
            break;
        }
        case 0b1111: {
            // 服务端处理错误时下发的消息类型（如无效的消息格式，不支持的序列化方法等）
            const uint32_t errorCode = parseInt32(payload);
            payload += 4;
            const uint32_t messageLength = parseInt32(payload);
            payload += 4;
            const std::string errorMessage = parseString(payload, messageLength);
            Serial.println("语音识别失败: ");
            Serial.printf("   errorCode =  %u\n", errorCode);
            Serial.printf("errorMessage =  %s\n", errorMessage.c_str());
            xSemaphoreGive(_taskFinished);
        }
        default: {
            break;
        }
    }
}

i2s_port_t DoubaoSTT::getI2sNumber() const {
    return _i2sNumber;
}
