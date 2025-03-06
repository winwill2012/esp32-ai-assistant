#ifndef ESP32_AI_ASSISTANT_LVGLDISPLAY_H
#define ESP32_AI_ASSISTANT_LVGLDISPLAY_H

#include "string"
#include <lvgl.h>
#include "FT6336.h"
#include "gui/gui_guider.h"
#include "gui/events_init.h"
#include "TFT_eSPI.h"

class LvglDisplay {
public:
    static void begin();

    static void updateChatText(std::string text);

private:

};


#endif //ESP32_AI_ASSISTANT_LVGLDISPLAY_H
