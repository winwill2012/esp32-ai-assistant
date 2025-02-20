#include "LLMAgent.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Utils.h"

LLMAgent::LLMAgent(const String &url, const String botId, const String &token) {
    _url = url;
    _botId = botId;
    _token = token;
    _state = Init;
}

LLMAgent::~LLMAgent() {
}

void LLMAgent::begin(const String &input) {
    reset();
    HTTPClient http;
    http.begin(_url);
    http.addHeader("Authorization", "Bearer " + _token);
    http.addHeader("Content-Type", "application/json");
    // 构建请求体
    JsonDocument requestBody;
    requestBody["stream"] = true;
    requestBody["bot_id"] = _botId;
    requestBody["user_id"] = getChipId(nullptr);
    const JsonArray additionalMessages = requestBody["additional_messages"].to<JsonArray>();
    JsonObject message = additionalMessages.add<JsonObject>();
    message["content_type"] = "text";
    message["content"] = input;
    message["role"] = "user";
    String requestBodyStr;
    serializeJson(requestBody, requestBodyStr);
    _state = Started;
    int httpResponseCode = http.POST(requestBodyStr);
    if (httpResponseCode > 0) {
        WiFiClient *stream = http.getStreamPtr();
        String line;
        while (stream->connected() || stream->available()) {
            if (stream->available()) {
                const char c = stream->read();
                if (c == '\n') {
                    if (!line.isEmpty()) {
                        if (ProcessStreamOutput(line) == ContentCompleted) {
                            Serial.println("LLMAgent::process completed");
                            break;
                        }
                    }
                    line = "";
                } else {
                    line += c;
                }
            }
        }
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void LLMAgent::show() const {
    Serial.println("LLMAgent调用结果: ");
    Serial.printf("   state = %d\n", _state);
    Serial.printf("response = %s\n", _response.c_str());
    Serial.printf("     cmd = %s\n", _cmd.c_str());
    Serial.printf(" content = %s\n", _content.c_str());
}

LLMAgent::State LLMAgent::ProcessStreamOutput(String input) {
    // 只处理data开头，并且是助手回答的数据类型
    if (!input.startsWith("data:") || input.indexOf("\"role\":\"assistant\",\"type\":\"answer\"") < 0) {
        return _state;
    }
    input.replace("data:", "");
    _document.clear();
    DeserializationError error = deserializeJson(_document, input);
    if (error != DeserializationError::Ok) {
        Serial.printf("Failed to deserialize JSON: ");
        Serial.println(input);
        return _state;
    }
    String content = _document["content"];
    Event event;
    if (content.compareTo(";") == 0) {
        event = SemicolonReceived;
    } else {
        event = NormalCharReceived;
        switch (_state) {
            case Started:
                _emotion += content;
                break;
            case EmotionCompleted:
                _response += content;
                break;
            case ResponseCompleted:
                _cmd += content;
                break;
            case CmdCompleted:
                _content += content;
                break;
            default: ;
        }
    }
    const auto it = StateTransferRouter.find(std::make_pair<>(_state, event));
    if (it != StateTransferRouter.end()) {
        _state = it->second;
    }
    return _state;
}

void LLMAgent::reset() {
    _state = Init;
    _emotion = "";
    _response = "";
    _cmd = "";
    _content = "";
}
