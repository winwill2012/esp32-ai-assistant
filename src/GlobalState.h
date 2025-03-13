#ifndef IOT_AI_CONTROLLER_GLOBALSTATE_H
#define IOT_AI_CONTROLLER_GLOBALSTATE_H

#include <Arduino.h>
#include <map>

#define EVENT_TTS_WS_TASK_FINISHED (1<<2)
#define EVENT_STT_WS_TASK_FINISHED (1<<4)
#define EVENT_LISTENING        (1<<5)
#define EVENT_PLAYING_AUDIO    (1<<6)

enum MachineState {
    Sleep,
    NetworkConnecting,
    NetworkConnected,
    NetworkConnectFailed,
    Listening,
    Thinking,
    Playing
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
        {{Playing, InterruptPlaying}, Listening},
        {{Playing, StopListening}, Sleep}
    };

    static void setConversationId(String conversationId);

    static String getConversationId();

    static MachineState getState();

    static void setState(MachineState state);

private:
    static String conversationId;
    static MachineState machineState;
};


#endif
