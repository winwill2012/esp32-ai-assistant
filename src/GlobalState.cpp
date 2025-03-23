#include "GlobalState.h"
#include "LvglDisplay.h"
#include "gui/gui_guider.h"
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

EventBits_t GlobalState::getEventBits(std::vector<MachineState> states) {
    EventBits_t result = 0;
    for (int i = 0; i < states.size(); i++) {
        result |= (1 << states[i]);
    }
    return result;
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
            LvglDisplay::updateRecordingButtonImage(&_mic_off_alpha_40x40);
            break;
        case NetworkConfigurationNotFound:
            LvglDisplay::updateState("等待配网...");
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
            LvglDisplay::updateRecordingButtonImage(&_mic_on_alpha_40x40);
            break;
        case Thinking:
            LvglDisplay::updateState("正在思考...");
            LvglDisplay::updateRecordingButtonImage(&_stop_alpha_40x40);
            break;
        case Speaking:
            LvglDisplay::updateState("正在说话...");
            LvglDisplay::updateRecordingButtonImage(&_stop_alpha_40x40);
            break;
    }
}
