#ifndef ESP32_AI_ASSISTANT_LVGLDISPLAY_H
#define ESP32_AI_ASSISTANT_LVGLDISPLAY_H

#include "string"
#include <lvgl.h>
#include "FT6336.h"
#include "gui/gui_guider.h"
#include "gui/events_init.h"
#include "TFT_eSPI.h"

enum MessageRole {
    Robot,
    User
};

class LvglDisplay {
public:
    static void begin();

    static void updateChatText(MessageRole messageRole, const std::string& text);

    static void updateState(const std::string& state);
    static void updateTime(const std::string& time);
private:
    static lv_style_t *message_style_robot;
    static lv_style_t *message_style_user;
};


#endif //ESP32_AI_ASSISTANT_LVGLDISPLAY_H
