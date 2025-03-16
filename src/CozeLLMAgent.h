#ifndef COZE_LLMAGENT_H
#define COZE_LLMAGENT_H

#include <map>
#include <ArduinoJson.h>
#include "DoubaoTTS.h"

class CozeLLMAgent {
public:

    CozeLLMAgent(DoubaoTTS &tts);

    ~CozeLLMAgent();

    void begin(const String &input);

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
};


#endif
