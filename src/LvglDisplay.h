#ifndef ESP32_AI_ASSISTANT_LVGLDISPLAY_H
#define ESP32_AI_ASSISTANT_LVGLDISPLAY_H

#include "string"
#include <lvgl.h>
#include <semphr.h>

enum MessageRole {
    Robot,
    User
};

class LvglDisplay {
public:
    static void begin();

    static void updateChatText(MessageRole messageRole, bool newLine, const std::string &text);

    static void updateState(const std::string &state);

    static void updateTime(const std::string &time);

    static void updateWifiState(bool success);

    static void updateRecordingButtonImage(const void *img);

    static void loadSystemSettingData();

    static void loadWifiList(bool forceRefresh);

    static void updateRecordingState(bool active);

private:
    static lv_obj_t *last_message;
    static int current_message_number;
    static SemaphoreHandle_t lvglUpdateLock;
};


#endif //ESP32_AI_ASSISTANT_LVGLDISPLAY_H
