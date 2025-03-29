#include "DoubaoASR.h"
#include "Utils.h"
#include "Settings.h"
#include <Arduino.h>
#include <RecordingManager.h>
#include <vector>
#include "LvglDisplay.h"
#include "Application.h"
#include "ArduinoJson.h"

DoubaoASR::DoubaoASR() {
    _eventGroup = xEventGroupCreate();
    _requestBuilder = std::vector<uint8_t>();
    _firstPacket = true;
    setExtraHeaders(("Authorization: Bearer; " + Settings::getDoubaoAccessToken()).c_str());
    beginSSL("openspeech.bytedance.com", 443, "/api/v2/asr");
    onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
        this->eventCallback(type, payload, length);
    });
}

void DoubaoASR::eventCallback(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_PING:
        case WStype_ERROR:
            break;
        case WStype_CONNECTED:
            log_d("websocket连接成功");
            break;
        case WStype_DISCONNECTED:
            log_d("websocket断开连接");
            break;
        case WStype_TEXT: {
            break;
        }
        case WStype_BIN:
            parseResponse(payload);
            break;
        default:
            break;
    }
}

void DoubaoASR::buildFullClientRequest() {
    JsonDocument doc;
    doc.clear();
    const JsonObject app = doc["app"].to<JsonObject>();
    app["appid"] = Settings::getDoubaoAppId();
    app["cluster"] = "volcengine_input_common";
    app["token"] = Settings::getDoubaoAccessToken();
    const JsonObject user = doc["user"].to<JsonObject>();
    user["uid"] = getChipId(nullptr);
    const JsonObject request = doc["request"].to<JsonObject>();
    request["reqid"] = generateTaskId();
    request["nbest"] = 1;
    request["result_type"] = "full";
    request["sequence"] = 1;
    request["workflow"] = "audio_in,resample,partition,vad,fe,decode,itn,nlu_ddc,nlu_punctuate";
    const JsonObject audio = doc["audio"].to<JsonObject>();
    audio["format"] = "raw";
    audio["codec"] = "raw";
    audio["channel"] = 1;
    audio["rate"] = AUDIO_SAMPLE_RATE;
    String payloadStr;
    serializeJson(doc, payloadStr);
    uint8_t payload[payloadStr.length() + 1];
    for (int i = 0; i < payloadStr.length(); i++) {
        payload[i] = static_cast<uint8_t>(payloadStr.charAt(i));
    }
    payload[payloadStr.length()] = '\0';
    std::vector<uint8_t> payloadSize = uint32ToUint8Array(payloadStr.length());
    _requestBuilder.clear();
    // 先写入报头（四字节）
    _requestBuilder.insert(_requestBuilder.end(), DoubaoTTSDefaultFullClientWsHeader,
                           DoubaoTTSDefaultFullClientWsHeader + sizeof(DoubaoTTSDefaultFullClientWsHeader));
    // 写入payload长度（四字节）
    _requestBuilder.insert(_requestBuilder.end(), payloadSize.begin(), payloadSize.end());
    // 写入payload内容
    _requestBuilder.insert(_requestBuilder.end(), payload, payload + payloadStr.length());
}

void DoubaoASR::buildAudioOnlyRequest(uint8_t *audio, const size_t size, const bool lastPacket) {
    _requestBuilder.clear();
    std::vector<uint8_t> payloadLength = uint32ToUint8Array(size);

    if (lastPacket) {
        // 先写入报头（四字节）
        _requestBuilder.insert(_requestBuilder.end(), DoubaoTTSDefaultLastAudioWsHeader,
                               DoubaoTTSDefaultLastAudioWsHeader + sizeof(DoubaoTTSDefaultLastAudioWsHeader));
    } else {
        // 先写入报头（四字节）
        _requestBuilder.insert(_requestBuilder.end(), DoubaoTTSDefaultAudioOnlyWsHeader,
                               DoubaoTTSDefaultAudioOnlyWsHeader + sizeof(DoubaoTTSDefaultAudioOnlyWsHeader));
    }

    // 写入payload长度（四字节）
    _requestBuilder.insert(_requestBuilder.end(), payloadLength.begin(), payloadLength.end());
    // 写入payload内容
    _requestBuilder.insert(_requestBuilder.end(), audio, audio + size);
}

void DoubaoASR::recognize(WebSocketASRTask task) {
    log_d("speech recognize request: %d, %d, %d", task.data.size(), task.firstPacket, task.lastPacket);
    if (task.firstPacket) {
        xEventGroupClearBits(_eventGroup, STT_TASK_COMPLETED_EVENT);
        while (!isConnected()) {
            loop();
            vTaskDelay(1);
        }
        buildFullClientRequest();
        if (!sendBIN(_requestBuilder.data(), _requestBuilder.size())) {
            log_e("send speech recognize full client request packet failed");
        }
        loop();
    }
    buildAudioOnlyRequest(task.data.data(), task.data.size(), task.lastPacket);
    if (!sendBIN(_requestBuilder.data(), _requestBuilder.size())) {
        log_e("send speech recognize audio only packet failed");
    }
    loop();
    if (task.lastPacket) {
        while ((xEventGroupWaitBits(_eventGroup, STT_TASK_COMPLETED_EVENT,
                                    false, true, pdMS_TO_TICKS(1)) & STT_TASK_COMPLETED_EVENT) == 0) {
            loop();
            vTaskDelay(1);
        }
        disconnect();
    }
}

void DoubaoASR::parseResponse(const uint8_t *response) {
    const uint8_t messageType = response[1] >> 4;
    const uint8_t *payload = response + 4;
    log_d("message type: %d", messageType);
    switch (messageType) {
        case 0b1001: {
            // 服务端下发包含识别结果的 full server response
            const uint32_t payloadSize = readInt32(payload);
            payload += 4;
            std::string recognizeResult = readString(payload, payloadSize);
            JsonDocument jsonResult;
            const DeserializationError err = deserializeJson(jsonResult, recognizeResult);
            if (err) {
                log_e("parse speech recognize result failed");
                return;
            }
            const String reqId = jsonResult["reqid"];
            const int32_t code = jsonResult["code"];
            const String message = jsonResult["message"];
            const int32_t sequence = jsonResult["sequence"];
            const JsonArray result = jsonResult["result"];
            log_d("sequence = %d, code = %d, message = %s, result size = %d", sequence, code, message.c_str(), result.size());
            if (sequence < 0) {
                xEventGroupSetBits(_eventGroup, STT_TASK_COMPLETED_EVENT);
            }
            if (code == 1000 && result.size() > 0) {
                for (const auto &item: result) {
                    String text = item["text"];
                    log_d("text = %s", text.c_str());
                    LvglDisplay::updateChatText(User, _firstPacket, text.c_str());
                    if (_firstPacket) {
                        _firstPacket = false;
                    }
                    if (sequence < 0) {
                        log_i("speech recognize result: %s", text.c_str());
                        LLMTask task{};
                        task.message = static_cast<char *>(ps_malloc(sizeof(char) * text.length()));
                        task.length = text.length();
                        text.toCharArray(task.message, task.length);
                        Application::llm()->publishTask(task);
                        _firstPacket = true;
                    }
                }
            }
            break;
        }
        case 0b1111: {
            // 服务端处理错误时下发的消息类型（如无效的消息格式，不支持的序列化方法等）
            const uint32_t errorCode = readInt32(payload);
            payload += 4;
            const uint32_t messageLength = readInt32(payload);
            payload += 4;
            const std::string errorMessage = readString(payload, messageLength);
            log_e("speech recognize failed: ");
            log_e("   errorCode =  %u\n", errorCode);
            log_e("errorMessage =  %s\n", errorMessage.c_str());
            xEventGroupSetBits(_eventGroup, STT_TASK_COMPLETED_EVENT);
        }
        default: {
            break;
        }
    }
}
