#include "lvgl_interface.h"
#include "Settings.h"
#include "LvglDisplay.h"
#include "Utils.h"
#include "driver/i2s.h"
#include "AudioPlayer.h"
#include "GlobalState.h"

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

void load_system_setting_data() {
    LvglDisplay::loadSystemSettingData();
}

void set_environment_noise(const char *noise) {
    if (strcmp(noise, "安静") == 0) {
        Settings::setRecordingRmsThreshold(ENV_QUIET);
    } else if (strcmp(noise, "一般") == 0) {
        Settings::setRecordingRmsThreshold(ENV_GENERAL);
    } else if (strcmp(noise, "嘈杂") == 0) {
        Settings::setRecordingRmsThreshold(ENV_NOISY);
    }
}

void set_speak_pause_duration(int duration) {
    Settings::setSpeakPauseDuration(duration);
}

void load_wifi_list(void *refresh) {
    LvglDisplay::loadWifiList((bool *) refresh);
}

bool connect_wifi(const char *ssid, const char *password) {
    log_d("连接网络: %s, %s", ssid, password);
    if (connectWifi(ssid, password, 20)) {
        Settings::setWifiInfo(ssid, password);
        return true;
    }
    return false;
}

void set_screen_brightness(int brightness) {
    Settings::setScreenBrightness(brightness);
}

void onMicrophoneClicked() {
    // 正在说话或者思考，直接进入聆听模式
    if (GlobalState::getState() == Speaking || GlobalState::getState() == Thinking) {
        i2s_stop(MAX98357_I2S_NUM);
        i2s_zero_dma_buffer(MAX98357_I2S_NUM);
        AudioPlayer::resetTaskQueue();  // 清空当前音频播放队列
        vTaskDelay(pdMS_TO_TICKS(500));
        GlobalState::setState(Listening);
    } else if (GlobalState::getState() == Listening) {  // 正在聆听，自己进入待机模式
        GlobalState::setState(Sleep);
    } else if (GlobalState::getState() == Sleep) {
        GlobalState::setState(Listening);
    }
}
