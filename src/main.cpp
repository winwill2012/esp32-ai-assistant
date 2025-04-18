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

void setup() {
    Serial.begin(115200);
    Settings::begin();
    LvglDisplay::begin();
    analogWrite(8, static_cast<int>(Settings::getScreenBrightness() * 2.55)); // 设置屏幕亮度

    const auto wifiInfo = Settings::getWifiInfo();
    if (wifiInfo.first.empty() || wifiInfo.second.empty()) {
        log_e("no wifi configuration found");
        GlobalState::setState(NetworkConfigurationNotFound);
    } else {
        connectWifi(wifiInfo.first.c_str(), wifiInfo.second.c_str(), 20);
    }
    log_d("waiting for network connected...");
    // 等待网络连接成功
    xEventGroupWaitBits(GlobalState::getEventGroup(), GlobalState::getEventBits({NetworkConnected}),
                        false, true, portMAX_DELAY);
    log_d("network connect successfully");
    GlobalState::setState(Sleep);

    Application::getInstance().begin();
}

void loop() {
}