#include "DoubaoBigModelSTT.h"
#include "Utils.h"
#include "Settings.h"
#include <Arduino.h>
#include <CozeLLMAgent.h>
#include <vector>
#include "LvglDisplay.h"

DoubaoBigModelSTT::DoubaoBigModelSTT(const CozeLLMAgent &llmAgent)
        : _llmAgent(llmAgent) {
    _requestBuilder = std::vector<uint8_t>();
    _taskFinished = xSemaphoreCreateBinary();
    _firstPacket = true;
    begin();
}

void DoubaoBigModelSTT::eventCallback(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_PING:
        case WStype_ERROR:
        case WStype_CONNECTED:
            log_d("大模型语音识别连接成功");
        case WStype_DISCONNECTED:
        case WStype_TEXT:
            break;
        case WStype_BIN:
            log_d("收到大模型语音识别相应结果");
            parseResponse(payload);
            break;
        default:
            break;
    }
}

void DoubaoBigModelSTT::begin() {
    if (isConnected()) {
        return;
    }
    char headers[200];
    snprintf(headers, sizeof(headers),
             "X-Api-App-Key: %s\r\n"
             "X-Api-Access-Key: %s\r\n"
             "X-Api-Resource-Id: volc.bigasr.sauc.duration\r\n"
             "X-Api-Connect-Id: %s",
             Settings::getDoubaoAppId().c_str(), Settings::getDoubaoAccessToken().c_str(), generateTaskId().c_str());
    setExtraHeaders(headers);
    beginSSL("openspeech.bytedance.com", 443, "/api/v3/sauc/bigmodel");
    onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
        this->eventCallback(type, payload, length);
    });
}


void DoubaoBigModelSTT::buildFullClientRequest() {
    JsonDocument doc;
    doc.clear();
    const JsonObject user = doc["user"].to<JsonObject>();
    user["uid"] = getChipId(nullptr);

    const JsonObject audio = doc["audio"].to<JsonObject>();
    audio["format"] = "pcm";
    audio["codec"] = "raw";
    audio["channel"] = 1;

    const JsonObject request = doc["request"].to<JsonObject>();
    request["model_name"] = "bigmodel";
    request["enable_itn"] = true;
    request["enable_punc"] = true;
    request["enable_ddc"] = true;
    request["result_type"] = "full";
    request["workflow"] = "audio_in,resample,partition,vad,fe,decode,nlu_punctuate";

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
    _requestBuilder.insert(_requestBuilder.end(), DoubaoBigModelSTTDefaultFullClientWsHeader,
                           DoubaoBigModelSTTDefaultFullClientWsHeader +
                           sizeof(DoubaoBigModelSTTDefaultFullClientWsHeader));
    // 写入payload长度（四字节）
    _requestBuilder.insert(_requestBuilder.end(), payloadSize.begin(), payloadSize.end());
    // 写入payload内容
    _requestBuilder.insert(_requestBuilder.end(), payload, payload + payloadStr.length());
}

void DoubaoBigModelSTT::buildAudioOnlyRequest(uint8_t *audio, const size_t size, const bool lastPacket) {
    _requestBuilder.clear();
    std::vector<uint8_t> payloadLength = int2Array(size);

    if (lastPacket) {
        // 先写入报头（四字节）
        _requestBuilder.insert(_requestBuilder.end(), DoubaoBigModelSTTDefaultLastAudioWsHeader,
                               DoubaoBigModelSTTDefaultLastAudioWsHeader +
                               sizeof(DoubaoBigModelSTTDefaultLastAudioWsHeader));
    } else {
        // 先写入报头（四字节）
        _requestBuilder.insert(_requestBuilder.end(), DoubaoBigModelSTTDefaultAudioOnlyWsHeader,
                               DoubaoBigModelSTTDefaultAudioOnlyWsHeader +
                               sizeof(DoubaoBigModelSTTDefaultAudioOnlyWsHeader));
    }

    // 写入payload长度（四字节）
    _requestBuilder.insert(_requestBuilder.end(), payloadLength.begin(), payloadLength.end());
    // 写入payload内容
    _requestBuilder.insert(_requestBuilder.end(), audio, audio + size);
}

void DoubaoBigModelSTT::recognize(uint8_t *audio, const size_t size, const bool firstPacket, const bool lastPacket) {
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

void DoubaoBigModelSTT::parseResponse(const uint8_t *response) {
    const uint8_t messageType = response[1] >> 4;
    const uint8_t messageSpecificFlag = response[1] & 0b1111;
    switch (messageType) {
        case 0b1001: {
            const uint8_t *size = response + 8;
            const uint8_t *payload = response + 12;
            // 服务端下发包含识别结果的 full server response
            const uint32_t payloadSize = parseInt32(size);
            std::string recognizeResult = parseString(payload, payloadSize);
            JsonDocument jsonResult;
            const DeserializationError err = deserializeJson(jsonResult, recognizeResult);
            if (err) {
                log_e("解析语音识别结果失败");
                xSemaphoreGive(_taskFinished);
                _firstPacket = true;
                return;
            }
            const String text = jsonResult["result"]["text"];
            log_i("[语音识别] 识别到文字: %s", text.c_str());
            if (text != "") {
                LvglDisplay::updateChatText(User, _firstPacket, text.c_str());
                if (_firstPacket) {
                    _firstPacket = false;
                }
            }
            if (messageSpecificFlag == 0b0011) {
                _llmAgent.begin(text);
                xSemaphoreGive(_taskFinished);
                _firstPacket = true;
            }
            break;
        }
        case 0b1111: {
            const uint8_t *payload = response + 4;
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
