#ifndef IOT_AI_CONTROLLER_GLOBALSTATE_H
#define IOT_AI_CONTROLLER_GLOBALSTATE_H

#include <Arduino.h>
#include <map>

enum MachineState {
    Sleep,
    NetworkConfigurationNotFound,
    NetworkConnecting,
    NetworkConnected,
    NetworkConnectFailed,
    Listening,
    Thinking,
    Speaking
};

enum MachineEvent {
    StartListen, // 开始监听
    StopListening, // 停止监听
    InterruptPlaying, // 打断播放
};

class GlobalState {
public:
    std::map<std::pair<MachineState, MachineEvent>, MachineState> machineStateTransferRouter = {
        {{Sleep, StartListen}, Listening},
        {{Listening, StopListening}, Sleep},
        {{Speaking, InterruptPlaying}, Listening},
        {{Speaking, StopListening}, Sleep}
    };

    static void setConversationId(String conversationId);

    static EventGroupHandle_t GlobalState::getEventGroup();

    static String getConversationId();

    static EventBits_t getEventBits(MachineState state);

    static MachineState getState();

    static void setState(MachineState state);

private:
    static String conversationId;
    static MachineState machineState;
    static EventGroupHandle_t eventGroup;
};


#endif
