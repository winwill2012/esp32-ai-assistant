#include "GlobalState.h"
#include "LvglDisplay.h"
#include "gui/gui_guider.h"
#include <utility>

String GlobalState::conversationId = "";
MachineState GlobalState::machineState = Sleep;
EventGroupHandle_t GlobalState::eventGroup = xEventGroupCreate();

void GlobalState::setConversationId(String conversationId)
{
    GlobalState::conversationId = std::move(conversationId);
}

EventGroupHandle_t GlobalState::getEventGroup()
{
    return eventGroup;
}

String GlobalState::getConversationId()
{
    return conversationId;
}

EventBits_t GlobalState::getEventBits(const std::vector<MachineState>& states)
{
    EventBits_t result = 0;
    for (const auto& state : states)
    {
        result |= (1 << state);
    }
    return result;
}

MachineState GlobalState::getState()
{
    return machineState;
}

void GlobalState::removeState(const MachineState state)
{
    xEventGroupClearBits(eventGroup, 1 << state);
}

void GlobalState::setState(const MachineState state)
{
    xEventGroupClearBits(eventGroup, xEventGroupGetBits(eventGroup));
    xEventGroupSetBits(eventGroup, 1 << state);
    machineState = state;
    switch (state)
    {
    case Sleep:
        LvglDisplay::updateState("待命中...");
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
