#ifndef LLMAGENT_H
#define LLMAGENT_H

#include <Arduino.h>
#include <map>
#include <ArduinoJson.h>

class LLMAgent {
public:
    enum State {
        Illegal,
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
        SemicolonReceived, // 收到分号
    };

    std::map<std::pair<State, Event>, State> StateTransferRouter = {
        {{Init, Begin}, Started},
        {{Started, NormalCharReceived}, Started},
        {{Started, SemicolonReceived}, EmotionCompleted},
        {{EmotionCompleted, NormalCharReceived}, EmotionCompleted},
        {{EmotionCompleted, SemicolonReceived}, ResponseCompleted},
        {{ResponseCompleted, NormalCharReceived}, ResponseCompleted},
        {{ResponseCompleted, SemicolonReceived}, CmdCompleted},
        {{CmdCompleted, NormalCharReceived}, CmdCompleted},
        {{CmdCompleted, SemicolonReceived}, ContentCompleted},
    };

    LLMAgent(const String &url, String botId, const String &token);

    ~LLMAgent();

    void begin(const String &input);

    void show() const;

    String emotion() const {
        return _emotion;
    }

    String response() const {
        return _response;
    }

    String cmd() const {
        return _cmd;
    }

    String content() const {
        return _content;
    }

    State ProcessStreamOutput(String data);

    void reset();

private :
    String _url;
    String _botId;
    String _token;

    String _emotion;
    String _response;
    String _cmd;
    String _content;

    State _state = Init;
    JsonDocument _document;
};


#endif
