#include "TimeUpdater.h"
#include "LvglDisplay.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
// 上一次的分钟数
int lastMinute = -1;
// 上次更新NTP时间的时间戳
unsigned long lastUpdateTime = 0;
// NTP更新间隔（毫秒），这里设置为1分钟
const unsigned long updateInterval = 60 * 1000;
// 本地时钟起始时间戳
unsigned long localTimeStart = 0;
// 从NTP获取的起始时间（秒）
unsigned long ntpStartTime = 0;

void TimeUpdater::begin() {
    timeClient.begin();
    timeClient.setTimeOffset(28800); // 设置时区，这里是北京时间（UTC+8），8 * 60 * 60 = 28800

    // 首次获取NTP时间
    timeClient.update();
    ntpStartTime = timeClient.getEpochTime();
    localTimeStart = millis();
    lastUpdateTime = millis();

    xTaskCreate([](void *ptr) {
        while (true) {
            unsigned long currentTime = millis();
            if (currentTime - lastUpdateTime >= updateInterval) {
                timeClient.update();
                ntpStartTime = timeClient.getEpochTime();
                localTimeStart = millis();
                lastUpdateTime = currentTime;
            }

            // 计算本地时钟的当前时间（秒）
            unsigned long localEpochTime = ntpStartTime + (currentTime - localTimeStart) / 1000;

            // 获取当前小时和分钟
            int currentHour = (localEpochTime % 86400) / 3600;
            int currentMinute = (localEpochTime % 3600) / 60;

            // 检查分钟是否变化
            if (currentMinute != lastMinute) {
                lastMinute = currentMinute;

                // 格式化时间字符串
                char timeStr[6];
                snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentHour, currentMinute);

                // 更新LVGL Label
                LvglDisplay::updateTime(timeStr);
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }, "timeUpdater", 2048, nullptr, 1, nullptr);
}