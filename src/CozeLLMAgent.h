#ifndef COZE_LLMAGENT_H
#define COZE_LLMAGENT_H

#include "CozeLLMAgent.h"
#include "DoubaoTTS.h"

struct LLMTask {
    char *message;
    size_t length;
};

class CozeLLMAgent {
public:
    explicit CozeLLMAgent(const DoubaoTTS &tts);

    void publishTask(LLMTask task);

    void chat(const String &input);

    void ProcessStreamOutput(String data);

    void ProcessContent(String &content);

    void reset();

private :
    DoubaoTTS _tts;
    String _response;
    String _cmd;
    String _content;
    String _ttsTextBuffer;
    bool _firstPacket;
    QueueHandle_t _taskQueue;
};


#endif
