#include "lvgl_interface.h"
#include "Settings.h"
#include "Application.h"
#include "LvglDisplay.h"
#include "Utils.h"
#include "AudioPlayer.h"
#include "GlobalState.h"
#include "gui/gui_guider.h"

void set_current_voice(const char *voice) {
    Settings::setCurrentVoice(voice);
}

void set_current_persona(const char *persona) {
    Settings::setCurrentPersona(persona);
}

void set_volume_ratio(const double volume) {
    Settings::setCurrentSpeakVolumeRatio(volume);
}

void set_speak_speed(const double speed) {
    Settings::setCurrentSpeakSpeedRatio(speed);
}

void load_system_setting_data() {
    LvglDisplay::loadSystemSettingData();
}

void load_wifi_list(lv_timer_t* timer) {
    LvglDisplay::loadWifiList(timer);
}

void connect_wifi(lv_timer_t* timer, const char *ssid, const char *password) {
    log_d("连接网络: %s, %s", ssid, password);
    if (reconnectWifi(timer, ssid, password, 20)) {
        Settings::setWifiInfo(ssid, password);
        lv_screen_load(guider_ui.screen_main);
    }
}

void set_screen_brightness(int brightness) {
    Settings::setScreenBrightness(brightness);
}

void on_btn_speak_clicked() {
    // 正在说话或者思考，直接进入聆听模式
    if (GlobalState::getState() == Speaking || GlobalState::getState() == Thinking) {
        Application::llm()->interrupt(true);
        Application::tts()->interrupt(true);
        Application::audioPlayer()->interrupt(true);
        vTaskDelay(pdMS_TO_TICKS(500));
        GlobalState::setState(Sleep);
    }
}

void on_btn_speak_pressed()
{
    if (GlobalState::getState() == Sleep || GlobalState::getState() == NetworkConnected)
    {
        // 正在待机，进入聆听状态
        GlobalState::setState(Listening);
        LvglDisplay::playSpeakAnim();
    }
}

void on_btn_speak_released()
{
    if (GlobalState::getState() == Listening)
    {
        GlobalState::setState(Recognizing);
        LvglDisplay::stopSpeakAnim();
    }
}

void reset_settings()
{
    Settings::reset();
}
