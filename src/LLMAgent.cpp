#include "LLMAgent.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Utils.h"

LLMAgent::LLMAgent(const String &url, const String botId, const String &token) {
    _url = url;
    _botId = botId;
    _token = token;
}

LLMAgent::~LLMAgent() {
}

AgentResponse *LLMAgent::chat(String input) const {
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
    int httpResponseCode = http.POST(requestBodyStr);
    if (httpResponseCode > 0) {
        WiFiClient *stream = http.getStreamPtr();
        String line;
        bool completed = false;
        while (stream->connected() || stream->available()) {
            if (stream->available()) {
                char c = stream->read();
                if (c == '\n') {
                    if (!line.isEmpty()) {
                        if (line.startsWith("event:")) {
                            completed = line.indexOf("event:conversation.message.completed") != -1;
                            line = "";
                            continue;
                        }
                        if (completed && line.indexOf("\"role\":\"assistant\",\"type\":\"answer\"") != -1) {
                            JsonDocument doc;
                            if (line.startsWith("data:")) {
                                line.replace("data:", "");
                            }
                            DeserializationError error = deserializeJson(doc, line);
                            if (!error) {
                                if (doc["role"] == "assistant" && doc["type"] == "answer") {
                                    const char *content = doc["content"];
                                    JsonDocument res;
                                    DeserializationError err = deserializeJson(res, content);
                                    if (!err) {
                                        http.end();
                                        return new AgentResponse(res["cmd"], res["response"], res["content"],
                                                                 res["emotion"]);
                                    }
                                }
                            }
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
    return nullptr;
}
