#include <Settings.h>
#include <utils.h>
#include "GlobalState.h"
#include "Arduino.h"
#include "LvglDisplay.h"
#include "Application.h"

/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */

void setup()
{
    Serial.begin(115200);
    Settings::begin();
    LvglDisplay::begin();

    const auto wifiInfo = Settings::getWifiInfo();
    if (wifiInfo.first.empty() || wifiInfo.second.empty())
    {
        ESP_LOGE("Main", "未发现可用WiFi配置");
        GlobalState::setState(NetworkConfigurationNotFound);
    }
    else
    {
        connectSavedWifi(wifiInfo.first.c_str(), wifiInfo.second.c_str(), 10);
    }
    ESP_LOGD("Main", "等待网络连接...");
    // 等待网络连接成功
    xEventGroupWaitBits(GlobalState::getEventGroup(), GlobalState::getEventBits({NetworkConnected}),
                        false, true, portMAX_DELAY);
    ESP_LOGD("Main", "网络连接成功");
    GlobalState::setState(Sleep);

    Application::getInstance().begin();
}

void loop()
{
}
