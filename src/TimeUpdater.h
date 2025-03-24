#ifndef ESP32_AI_ASSISTANT_TIMEUPDATER_H
#define ESP32_AI_ASSISTANT_TIMEUPDATER_H

#include <WiFiUdp.h>
#include "NTPClient.h"

class TimeUpdater {
public:
    TimeUpdater();

    static void begin();

private :
    static unsigned long _lastMinute;
};


#endif //ESP32_AI_ASSISTANT_TIMEUPDATER_H
