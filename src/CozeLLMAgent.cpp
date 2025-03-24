#include "CozeLLMAgent.h"
#include <HTTPClient.h>
#include <utility>
#include <Arduino.h>
#include "Utils.h"
#include "Settings.h"
#include "GlobalState.h"
#include "LvglDisplay.h"

CozeLLMAgent::CozeLLMAgent(const DoubaoTTS &tts) : _tts(tts) {
    _firstPacket = true;
    _taskQueue = xQueueCreate(5, sizeof(LLMTask));
    xTaskCreate([](void *ptr) {
        auto *instance = static_cast<CozeLLMAgent *>(ptr);
        LLMTask task{};
        while (true) {
            if (xQueueReceive(instance->_taskQueue, &task, pdMS_TO_TICKS(1)) == pdTRUE) {
                instance->chat(String(task.message, task.length));
                free(task.message);
            }
            vTaskDelay(1);
        }
    }, "llmTaskLoop", 1024 * 8, this, 1, nullptr);
}

void CozeLLMAgent::chat(const String &input) {
    if (input == "") return;
    log_d("Ready to send query to coze agent: %s", input.c_str());
    GlobalState::setState(Thinking);
    reset();
    HTTPClient http;
    http.begin("https://api.coze.cn/v3/chat?conversation_id=" + GlobalState::getConversationId());
    http.addHeader("Authorization", ("Bearer " + Settings::getCozeToken()).c_str());
    http.addHeader("Content-Type", "application/json");
    // 构建请求体
    JsonDocument requestBody;
    requestBody.clear();
    requestBody["stream"] = true;
    std::map<std::string, std::string> personaMap = Settings::getPersonaMap();
    requestBody["bot_id"] = personaMap[Settings::getCurrentPersona().c_str()];
    requestBody["user_id"] = getChipId(nullptr);
    const JsonArray additionalMessages = requestBody["additional_messages"].to<JsonArray>();
    JsonObject message = additionalMessages.add<JsonObject>();
    message["content_type"] = "text";
    message["content"] = input;
    message["role"] = "user";
    std::string requestBodyStr;
    serializeJson(requestBody, requestBodyStr);
    int httpResponseCode = http.POST(requestBodyStr.c_str());
    String lastEvent;
    if (httpResponseCode > 0) {
        WiFiClient *stream = http.getStreamPtr();
        String line = "";
        while (stream->connected() || stream->available()) {
            vTaskDelay(1);
            if (stream->available()) {
                line = stream->readStringUntil('\n');
                if (!line.isEmpty()) {
                    if (line.compareTo("event:conversation.message.completed") == 0
                        && lastEvent.compareTo("event:conversation.message.delta") == 0) {
                        if (_ttsTextBuffer != "") {
                            _tts.synth(_ttsTextBuffer, true);
                        } else {
                            _tts.disconnect();
                        }
                        break;
                    }
                    ProcessStreamOutput(line);
                    if (line.startsWith("event:")) {
                        lastEvent = line;
                    }
                }
            }
        }
    } else {
        log_e("Send query to coze agent error: %s", httpResponseCode);
    }
    http.end();
}

void CozeLLMAgent::ProcessStreamOutput(String data) {
    log_v("Process coze agent response fragment: %s", data.c_str());
    // 只处理data开头，并且是助手回答的数据类型
    if (!data.startsWith("data:") || data.indexOf(R"("role":"assistant","type":"answer")") < 0) {
        return;
    }
    data.replace("data:", "");
    JsonDocument document;
    document.clear();
    const DeserializationError error = deserializeJson(document, data);
    if (error != DeserializationError::Ok) {
        log_e("Deserialization coze agent response error: %s", data.c_str());
        return;
    }
    String content = document["content"];
    String conversationId = document["conversation_id"];
    GlobalState::setConversationId(conversationId);
    ProcessContent(content);
}

void CozeLLMAgent::reset() {
    _response = "";
    _ttsTextBuffer = "";
    _cmd = "";
    _content = "";
    _firstPacket = true;
}

void CozeLLMAgent::ProcessContent(String &content) {
    content.trim();
    if (content.isEmpty()) {
        return;
    }
    _response += content;
    LvglDisplay::updateChatText(Robot, _firstPacket, _response.c_str());
    if (_firstPacket) {
        _firstPacket = false;
    }
    _ttsTextBuffer += content;
    // 回复的内容里面包含一些可以断句的标点符号时，直接发送给TTS进行语音合成，降低响应延迟
    while (true) {
        const std::pair<int, size_t> delimiterIndex = findMinIndexOfDelimiter(_ttsTextBuffer);
        if (delimiterIndex.first >= 0) {
            _tts.synth(_ttsTextBuffer.substring(0, delimiterIndex.first), false);
            _ttsTextBuffer = _ttsTextBuffer.substring(delimiterIndex.first + delimiterIndex.second);
        } else {
            break;
        }
    }
}

void CozeLLMAgent::publishTask(LLMTask task) {
    if (xQueueSend(_taskQueue, &task, portMAX_DELAY) == pdFALSE) {
        log_e("send llm task to queue failed");
        free(task.message);
    }
}
