#include "TimeUpdater.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "LvglDisplay.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time1.aliyun.com");
unsigned long lastMinute = -1;

[[noreturn]] void TimeUpdater::begin() {
    timeClient.begin();
    timeClient.setTimeOffset(28800); // 设置时区，这里是北京时间（UTC+8），8 * 60 * 60 = 28800
    xTaskCreate([](void *ptr) {
        while (true) {
            timeClient.update(); // update函数内部做了更新间隔检测，并不会每一次都从网络获取时间
            const unsigned long localEpochTime = timeClient.getEpochTime();
            const unsigned long currentHour = (localEpochTime % 86400) / 3600;
            const unsigned long currentMinute = (localEpochTime % 3600) / 60;
            if (currentMinute != lastMinute) {
                char timeStr[6];
                snprintf(timeStr, sizeof(timeStr), "%02lu:%02lu", currentHour, currentMinute);
                LvglDisplay::updateTime(timeStr);
                lastMinute = currentMinute;
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }, "timeUpdater", 1024 * 4, nullptr, 0, nullptr);
}
