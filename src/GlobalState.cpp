#include "GlobalState.h"
#include "LvglDisplay.h"
#include <utility>

String GlobalState::conversationId = "";
MachineState GlobalState::machineState = Sleep;
EventGroupHandle_t GlobalState::eventGroup = xEventGroupCreate();

void GlobalState::setConversationId(String conversationId) {
    GlobalState::conversationId = std::move(conversationId);
}

EventGroupHandle_t GlobalState::getEventGroup() {
    return eventGroup;
}

String GlobalState::getConversationId() {
    return conversationId;
}

EventBits_t GlobalState::getEventBits(const MachineState state) {
    return 1 << state;
}

MachineState GlobalState::getState() {
    return machineState;
}

void GlobalState::setState(const MachineState state) {
    xEventGroupClearBits(eventGroup, xEventGroupGetBits(eventGroup));
    xEventGroupSetBits(eventGroup, 1 << state);
    machineState = state;
    switch (state) {
        case Sleep:
            LvglDisplay::updateState("待命中...");
            break;
        case NetworkConfigurationNotFound:
            LvglDisplay::updateState("网络未连接");
            break;
        case NetworkConnecting:
            LvglDisplay::updateState("正在连网...");
            break;
        case NetworkConnected:
            LvglDisplay::updateState("连网成功");
            LvglDisplay::updateWifiState(true);
            break;
        case NetworkConnectFailed:
            LvglDisplay::updateState("连网失败");
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
        case Speaking:
            LvglDisplay::updateState("正在说话...");
            LvglDisplay::updateRecordingButtonState(false);
            LvglDisplay::updateRecordingButtonImage(true);
            break;
    }
}
