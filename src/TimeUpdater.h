#ifndef ESP32_AI_ASSISTANT_TIMEUPDATER_H
#define ESP32_AI_ASSISTANT_TIMEUPDATER_H

#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeUpdater {
public:
    static void begin();

private:
    TimeUpdater();

    ~TimeUpdater();
};


#endif //ESP32_AI_ASSISTANT_TIMEUPDATER_H
