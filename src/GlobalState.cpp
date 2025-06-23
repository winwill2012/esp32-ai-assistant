#include "GlobalState.h"
#include "LvglDisplay.h"
#include <utility>

String GlobalState::conversationId = "";
MachineState GlobalState::machineState = Sleep;
String GlobalState::connectingWiFiMessage = "正在连网";
EventGroupHandle_t GlobalState::eventGroup = xEventGroupCreate();

#define LIGHT_GREEN 0x55b79d
#define RED 0xda4242

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

void GlobalState::setState(const MachineState state)
{
    ESP_LOGD("GlobalState", "设置设备状态到: %d", state);
    xEventGroupClearBits(eventGroup, xEventGroupGetBits(eventGroup));
    xEventGroupSetBits(eventGroup, 1 << state);
    machineState = state;
    switch (state)
    {
    case Sleep:
        LvglDisplay::updateState("待命中...");
        LvglDisplay::enableBtn("按住说话",LIGHT_GREEN);
        LvglDisplay::stopSpeakAnim();
        break;
    case NetworkConfigurationNotFound:
        LvglDisplay::updateState("等待配网...");
        LvglDisplay::disableBtn("请先左滑配置wifi网络", RED);
        break;
    case NetworkConnecting:
        LvglDisplay::disableBtn("正在等待网络连接", RED);
        LvglDisplay::updateState(connectingWiFiMessage.c_str());
        connectingWiFiMessage = connectingWiFiMessage + ".";
        if (connectingWiFiMessage.compareTo("正在连网....") == 0)
        {
            connectingWiFiMessage = "正在连网";
        }
        break;
    case NetworkConnected:
        LvglDisplay::updateState("连网成功");
        LvglDisplay::updateWifiState(true);
        LvglDisplay::enableBtn("按住说话", LIGHT_GREEN);
        break;
    case NetworkConnectFailed:
        LvglDisplay::updateState("连网失败");
        LvglDisplay::disableBtn("请先左滑配置wifi网络", RED);
        break;
    case Listening:
        LvglDisplay::updateState("正在聆听...");
        LvglDisplay::enableBtn("正在聆听", RED);
        LvglDisplay::playSpeakAnim();
        break;
    case Thinking:
        LvglDisplay::updateState("正在思考...");
        LvglDisplay::disableBtn("正在思考", RED);
        LvglDisplay::stopSpeakAnim();
        break;
    case Recognizing:
        LvglDisplay::updateState("正在识别...");
        LvglDisplay::disableBtn("正在识别", RED);
        LvglDisplay::stopSpeakAnim();
        break;
    case Speaking:
        LvglDisplay::updateState("正在说话...");
        LvglDisplay::disableBtn("正在说话", RED);
        LvglDisplay::stopSpeakAnim();
        break;
    default:
        break;
    }
}
