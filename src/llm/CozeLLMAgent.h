#ifndef COZE_LLMAGENT_H
#define COZE_LLMAGENT_H

#include "Arduino.h"
#include "CozeLLMAgent.h"

struct LLMTask {
    char *message;
    size_t length;
};

class CozeLLMAgent {
public:
    CozeLLMAgent();

    void publishTask(LLMTask task) const;

    void chat(const String &input);

    void ProcessStreamOutput(String data);

    void ProcessContent(const String &content);

    void reset();

    void interrupt(bool value);

private:
    bool _interrupted = false;
    String _response = "";
    String _cmd = "";
    String _content = "";
    String _ttsTextBuffer = "";
    bool _firstPacket;
    QueueHandle_t _taskQueue;
};


#endif
