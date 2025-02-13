#ifndef LLMAGENT_H
#define LLMAGENT_H
#include <Arduino.h>

struct AgentResponse {
    AgentResponse(const String &cmd,
                  const String &response,
                  const String &content,
                  const String &emotion): cmd(cmd), response(response), content(content), emotion(emotion) {
    }

    String cmd;
    String response;
    String content;
    String emotion;
};

class LLMAgent {
public:
    LLMAgent(const String &url, const String botId, const String &token);

    ~LLMAgent();

    AgentResponse *chat(String input) const;

private :
    String _url;
    String _botId;
    String _token;
};


#endif
