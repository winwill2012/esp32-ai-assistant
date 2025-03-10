#include "CozeLLMAgent.h"
#include <HTTPClient.h>
#include <PsramJson.h>
#include <utility>
#include "Utils.h"
#include "GlobalState.h"
#include "LvglDisplay.h"

CozeLLMAgent::CozeLLMAgent(DoubaoTTS tts, const String &url, const String &botId, const String &token) : _tts(
        std::move(tts)) {
    _url = url;
    _botId = botId;
    _token = token;
    _state = Init;
}

CozeLLMAgent::~CozeLLMAgent() = default;

void CozeLLMAgent::begin(const String &input) {
    reset();
    HTTPClient http;
    http.begin(_url + GlobalState::getConversationId());
    http.addHeader("Authorization", "Bearer " + _token);
    http.addHeader("Content-Type", "application/json");
    // 构建请求体
    JsonDocument requestBody;
    requestBody.clear();
    requestBody["stream"] = true;
    requestBody["bot_id"] = _botId;
    requestBody["user_id"] = getChipId(nullptr);
    const JsonArray additionalMessages = requestBody["additional_messages"].to<JsonArray>();
    JsonObject message = additionalMessages.add<JsonObject>();
    message["content_type"] = "text";
    message["content"] = input;
    message["role"] = "user";
    std::string requestBodyStr;
    serializeJson(requestBody, requestBodyStr);
    _state = Started;
    int httpResponseCode = http.POST(requestBodyStr.c_str());
    if (httpResponseCode > 0) {
        WiFiClient *stream = http.getStreamPtr();
        String line = "";
        while (stream->connected() || stream->available()) {
            if (stream->available()) {
                line = stream->readStringUntil('\n');
                if (!line.isEmpty()) {
                    if (ProcessStreamOutput(line) == ContentCompleted) {
                        break;
                    }
                }
            }
        }
    } else {
        Serial.print("LLM调用失败: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

void CozeLLMAgent::show() const {
    Serial.println("-----------LLMAgent调用结果--------------------");
    Serial.printf("    state = %d\n", _state);
    Serial.printf(" response = %s\n", _response.c_str());
    Serial.printf("ttsBuffer = %s\n", _ttsTextBuffer.c_str());
    Serial.printf("      cmd = %s\n", _cmd.c_str());
    Serial.printf("  content = %s\n", _content.c_str());
    Serial.println("-----------------------------------------------");
}

CozeLLMAgent::LLMState CozeLLMAgent::ProcessStreamOutput(String data) {
    // 只处理data开头，并且是助手回答的数据类型
    if (!data.startsWith("data:") || data.indexOf(R"("role":"assistant","type":"answer")") < 0) {
        return _state;
    }
    data.replace("data:", "");
    log_d("处理LLM返回数据: %s", data.c_str());
    JsonDocument document;
    document.clear();
    const DeserializationError error = deserializeJson(document, data);
    if (error != DeserializationError::Ok) {
        Serial.printf("反序列化大模型返回结果失败: ");
        Serial.println(data);
        return _state;
    }
    String content = document["content"];
    String conversationId = document["conversation_id"];
    GlobalState::setConversationId(conversationId);
    while (!content.isEmpty()) {
        ProcessContent(content);
    }
    return _state;
}

void CozeLLMAgent::reset() {
    _state = Init;
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
    // 内容不包含分隔符，状态不会发生变化
    if (content.indexOf(DELIMITER) < 0) {
        switch (_state) {
            case Started: {
                _response += content;
                LvglDisplay::updateChatText(Robot, _firstPacket, _response.c_str());
                if (_firstPacket) {
                    _firstPacket = false;
                }
                _ttsTextBuffer += content;
                // 回复的内容里面包含一些可以断句的标点符号时，直接发送给TTS进行语音合成，降低响应延迟
                const std::pair<int, size_t> delimiterIndex = findMinIndexOfDelimiter(_ttsTextBuffer);
                if (delimiterIndex.first >= 0) {
                    _tts.synth(_ttsTextBuffer.substring(0, delimiterIndex.first));
                    _ttsTextBuffer = _ttsTextBuffer.substring(delimiterIndex.first + delimiterIndex.second);
                }
                break;
            }
            case ResponseCompleted: {
                _cmd += content;
                break;
            }
            case CmdCompleted: {
                _content += content;
                break;
            }
            default:
                break;
        }
        content = "";
        return;
    }
    // 如果包含分隔符^,前半部分和后半部分分开处理，递归调用本函数
    const int index = content.indexOf(DELIMITER);
    String fistHalfContent = content.substring(0, index);
    // 递归处理前半部分内容
    ProcessContent(fistHalfContent);
    // 执行状态转移相关逻辑
    const auto it = StateTransferRouter.find(std::make_pair(_state, DelimiterReceived));
    if (it != StateTransferRouter.end()) {
        _state = it->second;
    }
    if (_state == ResponseCompleted && !_ttsTextBuffer.isEmpty()) {
        LvglDisplay::updateChatText(Robot, _firstPacket, _response.c_str());
        _tts.synth(_ttsTextBuffer);
    }
    content = content.substring(index + 1);
}
