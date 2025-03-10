#ifndef COZE_LLMAGENT_H
#define COZE_LLMAGENT_H

#include <map>
#include <ArduinoJson.h>
#include "DoubaoTTS.h"

#define DELIMITER "^"

class CozeLLMAgent {
public:
    enum LLMState {
        Init,
        Started,
        ResponseCompleted,
        CmdCompleted,
        ContentCompleted,
    };

    enum LLMEvent {
        Begin, // 开始调用接口
        NormalCharReceived, // 收到普通字符
        DelimiterReceived, // 收到字段分隔符
    };

    std::map<std::pair<LLMState, LLMEvent>, LLMState> StateTransferRouter = {
            {{Init,              Begin},              Started},
            {{Started,           NormalCharReceived}, Started},
            {{Started,           DelimiterReceived},  ResponseCompleted},
            {{ResponseCompleted, NormalCharReceived}, ResponseCompleted},
            {{ResponseCompleted, DelimiterReceived},  CmdCompleted},
            {{CmdCompleted,      NormalCharReceived}, CmdCompleted},
            {{CmdCompleted,      DelimiterReceived},  ContentCompleted},
    };

    CozeLLMAgent(DoubaoTTS tts, const String &url, const String &botId, const String &token);

    ~CozeLLMAgent();

    void begin(const String &input);

    void show() const;

    String response() const {
        return _response;
    }

    String content() const {
        return _content;
    }

    LLMState ProcessStreamOutput(String data);

    void ProcessContent(String &content);

    void reset();

private :
    DoubaoTTS _tts;
    String _url;
    String _botId;
    String _token;

    String _response;
    String _cmd;
    String _content;
    String _ttsTextBuffer;
    bool _firstPacket;
    LLMState _state = Init;
};


#endif
