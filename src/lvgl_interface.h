
#ifndef ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
#define ESP32_AI_ASSISTANT_LVGL_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

void set_current_voice(const char *voice);

void set_current_persona(const char *persona);

void set_environment_noise(const char *noise);

void set_volume_ratio(float volume);

void set_speak_speed(float speed);

void set_speak_pause_duration(int duration);

void load_speaker_setting_data();

void load_wifi_list(bool refresh);
#ifdef __cplusplus
}
#endif
#endif //ESP32_AI_ASSISTANT_LVGL_INTERFACE_H
