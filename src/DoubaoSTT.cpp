#include "DoubaoSTT.h"
#include "ArduinoJson.h"
#include "Utils.h"
#include <Arduino.h>
#include <GlobalState.h>
#include <vector>

#define AUDIO_SAMPLE_RATE 16000

JsonDocument doc;

DoubaoSTT::DoubaoSTT(const LLMAgent &llmAgent, i2s_port_t i2sNumber, const String &appId, const String &token,
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
    setupINMP441();
    begin();
}

void DoubaoSTT::eventCallback(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_PING:
            break;
        case WStype_ERROR:
            Serial.println("DoubaoSTT连接错误: ");
            for (size_t i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        case WStype_CONNECTED: {
            GlobalState::setEvents(EVENT_STT_WS_CONNECTED);
            break;
        }
        case WStype_DISCONNECTED:
            GlobalState::unsetEvents(EVENT_STT_WS_CONNECTED);
            break;
        case WStype_TEXT: {
            Serial.println("DoubaoSTT收到Text回复: ");
            for (int i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        }
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
    const i2s_config_t i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = i2s_bits_per_sample_t(16),
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
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
    request["workflow"] = "audio_in,resample,partition,vad,fe,decode,nlu_punctuate";
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

void DoubaoSTT::recognize(uint8_t *audio, size_t size, bool firstPacket, bool lastPacket) {
    if (firstPacket) {
        // 等待STT websocket连接成功
        while (!GlobalState::waitAllEvents(EVENT_STT_WS_CONNECTED, 0)) {
            loop();
            vTaskDelay(1);
        }
        buildFullClientRequest();
        // 清空合成完毕状态
        GlobalState::unsetEvents(EVENT_STT_WS_TASK_FINISHED);
        sendBIN(_requestBuilder.data(), _requestBuilder.size());
        loop();
    }
    buildAudioOnlyRequest(audio, size, lastPacket);
    sendBIN(_requestBuilder.data(), _requestBuilder.size());
    loop();
    if (lastPacket) {
        // 等待本次合成完毕
        while (!GlobalState::waitAllEvents(EVENT_STT_WS_TASK_FINISHED, 0)) {
            loop();
            vTaskDelay(1);
        }
        disconnect();
        Serial.println("语音识别任务完成");
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
            const JsonArray result = jsonResult["result"];
            if (code == 1000 && result.size() > 0) {
                for (const auto &item: result) {
                    String text = item["text"];
                    if (sequence < 0) {
                        Serial.printf("[语音识别] 识别到文字: %s\n", text.c_str());
                        _llmAgent.begin(text);
                    }
                }
            } else {
                Serial.printf("[语音识别错误]: code = %d, seq = %d, message = %s\n", code, sequence, message.c_str());
            }
            if (sequence < 0) {
                GlobalState::setEvents(EVENT_STT_WS_TASK_FINISHED);
            }
            break;
        }
        case 0b1111: {
            // 服务端处理错误时下发的消息类型（如无效的消息格式，不支持的序列化方法等）
            const uint32_t errorCode = parseInt32(payload);
            payload += 4;
            const uint32_t messageLength = parseInt32(payload);
            payload += 4;
            const String errorMessage = parseString(payload, messageLength);
            Serial.println("语音识别失败: ");
            Serial.printf("   errorCode =  %u\n", errorCode);
            Serial.printf("errorMessage =  %s\n", errorMessage.c_str());
            GlobalState::setEvents(EVENT_STT_WS_TASK_FINISHED);
        }
        default: {
            break;
        }
    }
}

i2s_port_t DoubaoSTT::getI2sNumber() const {
    return _i2sNumber;
}
