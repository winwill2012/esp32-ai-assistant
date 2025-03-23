#ifndef ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
#define ESP32_AI_ASSISTANT_LVGL_INTERFACE_H

#ifdef __cplusplus

extern "C" {
#endif
#define ENV_QUIET   8000  // 安静
#define ENV_GENERAL 11000  // 正常
#define ENV_NOISY   15000  // 嘈杂

void set_current_voice(const char *voice);

void set_current_persona(const char *persona);

void set_environment_noise(const char *noise);

void set_volume_ratio(float volume);

void set_speak_speed(float speed);

void set_screen_brightness(int brightness);

void set_speak_pause_duration(int duration);

void load_system_setting_data();

void load_wifi_list(void *refresh);

bool connect_wifi(const char *ssid, const char *password);

void onMicrophoneClicked();

#ifdef __cplusplus
}
#endif
#endif //ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
