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
    log_d("Free ram: %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    log_d("Free psram: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    void *pVoid1 = malloc(64 * 1024);
    log_d("ram address = %x", pVoid1);
    void *pVoid = ps_malloc(64 * 1024);
    log_d("psram address = %x", pVoid);
    log_d("Free ram: %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    log_d("Free psram: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
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