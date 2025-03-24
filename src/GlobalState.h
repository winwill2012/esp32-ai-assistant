#ifndef IOT_AI_CONTROLLER_GLOBALSTATE_H
#define IOT_AI_CONTROLLER_GLOBALSTATE_H

#include <Arduino.h>
#include <vector>

enum MachineState {
    Sleep,
    NetworkConfigurationNotFound,
    NetworkConnecting,
    NetworkConnected,
    NetworkConnectFailed,
    Listening,
    Thinking,
    Speaking,
    ForceStop
};

class GlobalState {
public:
    static void setConversationId(String conversationId);

    static EventGroupHandle_t getEventGroup();

    static inline String getConversationId();

    static EventBits_t getEventBits(const std::vector<MachineState> &states);

    static inline MachineState getState();

    static void setState(MachineState state);

private:
    static String conversationId;
    static MachineState machineState;
    static EventGroupHandle_t eventGroup;
};


#endif
