#include "lvgl_interface.h"
#include "Settings.h"
#include "LvglDisplay.h"

void set_current_voice(const char *voice) {
    Settings::setCurrentVoice(voice);
}

void set_current_persona(const char *persona) {
    Settings::setCurrentPersona(persona);
}

void set_volume_ratio(float volume) {
    Settings::setCurrentSpeakVolumeRatio(volume);
}

void set_speak_speed(float speed) {
    Settings::setCurrentSpeakSpeedRatio(speed);
}

void load_speaker_setting_data() {
    LvglDisplay::loadSpeakerSettingData();
}

void set_environment_noise(const char *noise) {
    if (strcmp(noise, "安静") == 0) {
        Settings::setRecordingRmsThreshold(4500);
    } else if (strcmp(noise, "一般") == 0) {
        Settings::setRecordingRmsThreshold(6000);
    } else if (strcmp(noise, "嘈杂") == 0) {
        Settings::setRecordingRmsThreshold(7500);
    }
}

void set_speak_pause_duration(int duration) {
    Settings::setSpeakPauseDuration(duration);
}
