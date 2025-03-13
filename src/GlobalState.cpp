#include "GlobalState.h"
#include "LvglDisplay.h"
#include <utility>

String GlobalState::conversationId = "";
MachineState GlobalState::machineState = Sleep;

void GlobalState::setConversationId(String conversationId) {
    GlobalState::conversationId = std::move(conversationId);
}

String GlobalState::getConversationId() {
    return conversationId;
}

MachineState GlobalState::getState() {
    return machineState;
}

void GlobalState::setState(MachineState state) {
    machineState = state;
    switch (state) {
        case Sleep:
            LvglDisplay::updateState("待命中...");
            break;
        case NetworkConnecting:
            LvglDisplay::updateState("正在连网...");
            break;
        case NetworkConnected:
            LvglDisplay::updateState("连网成功");
            LvglDisplay::updateWifiState(true);
            break;
        case Listening:
            LvglDisplay::updateState("正在聆听...");
            LvglDisplay::updateRecordingButtonState(true);
            LvglDisplay::updateRecordingButtonImage(false);
            break;
        case Thinking:
            LvglDisplay::updateState("正在思考...");
            LvglDisplay::updateRecordingButtonState(false);
            break;
        case Playing:
            LvglDisplay::updateState("正在说话...");
            LvglDisplay::updateRecordingButtonState(false);
            LvglDisplay::updateRecordingButtonImage(true);
            break;
    }
}
