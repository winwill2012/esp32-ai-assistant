#include "GlobalState.h"
#include "LvglDisplay.h"
#include "gui/gui_guider.h"
#include <utility>

String GlobalState::conversationId = "";
MachineState GlobalState::machineState = Sleep;
String GlobalState::connectingWiFiMessage = "正在连网";
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

EventBits_t GlobalState::getEventBits(const std::vector<MachineState> &states) {
    EventBits_t result = 0;
    for (const auto &state: states) {
        result |= (1 << state);
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
            break;
        case NetworkConfigurationNotFound:
            LvglDisplay::updateState("等待配网...");
            break;
        case NetworkConnecting:
            LvglDisplay::updateState(connectingWiFiMessage.c_str());
            connectingWiFiMessage = connectingWiFiMessage + ".";
            if (connectingWiFiMessage.compareTo("正在连网....")) {
                connectingWiFiMessage = "正在连网";
            }
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
            break;
        case Recognizing:
            LvglDisplay::updateState("正在识别...");
            break;
        case Thinking:
            LvglDisplay::updateState("正在思考...");
            break;
        case Speaking:
            LvglDisplay::updateState("正在说话...");
            break;
        default:
            break;
    }
}
