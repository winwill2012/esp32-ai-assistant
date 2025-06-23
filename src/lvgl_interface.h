#ifndef ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
#define ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
#include "misc/lv_types.h"

#ifdef __cplusplus

extern "C" {
#endif
#define ENV_QUIET   20  // 安静
#define ENV_GENERAL 30  // 正常
#define ENV_NOISY   50  // 嘈杂

void set_current_voice(const char* voice);

void set_current_persona(const char* persona);

void set_volume_ratio(double volume);

void set_speak_speed(double speed);

void set_screen_brightness(int brightness);

void load_system_setting_data();

void load_wifi_list(lv_timer_t* timer);

void connect_wifi(lv_timer_t* timer, const char* ssid, const char* password);

void on_btn_speak_pressed();

void on_btn_speak_released();

void reset_settings();

#ifdef __cplusplus
}
#endif
#endif //ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
