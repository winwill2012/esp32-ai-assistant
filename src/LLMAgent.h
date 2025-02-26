#ifndef LLMAGENT_H
#define LLMAGENT_H

#include <map>
#include <ArduinoJson.h>
#include "DoubaoTTS.h"
#define DELIMITER "^"

class LLMAgent {
public:
    enum State {
        Init,
        Started,
        EmotionCompleted,
        ResponseCompleted,
        CmdCompleted,
        ContentCompleted,
    };

    enum Event {
        Begin, // 开始调用接口
        NormalCharReceived, // 收到普通字符
        DelimiterReceived, // 收到字段分隔符
    };

    std::map<std::pair<State, Event>, State> StateTransferRouter = {
        {{Init, Begin}, Started},
        {{Started, NormalCharReceived}, Started},
        {{Started, DelimiterReceived}, EmotionCompleted},
        {{EmotionCompleted, NormalCharReceived}, EmotionCompleted},
        {{EmotionCompleted, DelimiterReceived}, ResponseCompleted},
        {{ResponseCompleted, NormalCharReceived}, ResponseCompleted},
        {{ResponseCompleted, DelimiterReceived}, CmdCompleted},
        {{CmdCompleted, NormalCharReceived}, CmdCompleted},
        {{CmdCompleted, DelimiterReceived}, ContentCompleted},
    };

    LLMAgent(DoubaoTTS tts, const String &url, String botId, const String &token);

    ~LLMAgent();

    void begin(const String &input);

    void show() const;

    String response() const {
        return _response;
    }

    String content() const {
        return _content;
    }

    State ProcessStreamOutput(String data);

    void ProcessContent(String &content);

    void reset();

private :
    DoubaoTTS _tts;
    String _url;
    String _botId;
    String _token;

    String _emotion;
    String _response;
    String _cmd;
    String _content;
    String _ttsTextBuffer;

    State _state = Init;
    JsonDocument _document;
};


#endif
