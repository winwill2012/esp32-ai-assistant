#include <Arduino.h>
#include "LvglDisplay.h"
#include "Settings.h"
#include <FT6336.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <gui/events_init.h>
#include <gui/gui_guider.h>
#include "lvgl_interface.h"

#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define I2C_SDA 10
#define I2C_SCL 13
#define RST_N_PIN 9
#define INT_N_PIN 12
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
FT6336 ts(I2C_SDA, I2C_SCL, INT_N_PIN, RST_N_PIN, TFT_WIDTH, TFT_HEIGHT);
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

lv_ui guider_ui;
lv_obj_t* LvglDisplay::last_message;
int LvglDisplay::current_message_number = 0;
bool LvglDisplay::scanningWifi = false;
int LvglDisplay::refreshImageAngle = 3600;

SemaphoreHandle_t LvglDisplay::lvglUpdateLock = xSemaphoreCreateRecursiveMutex();

void my_touchpad_read(lv_indev_t* indev, lv_indev_data_t* data)
{
    ts.read();
    if (ts.isTouched)
    {
        data->point.x = static_cast<lv_coord_t>(ts.points[0].x);
        data->point.y = static_cast<lv_coord_t>(ts.points[0].y);
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

// 这个函数是在lvgl线程中调用的，无需加锁
void LvglDisplay::loadSystemSettingData()
{
    const std::map<std::string, std::string>& voiceMap = Settings::getVoiceMap();
    const std::map<std::string, std::string>& personaMap = Settings::getPersonaMap();
    std::string voiceList;
    std::string personaList;
    uint16_t selectedVoiceIndex = 0;
    uint16_t selectedPersonaIndex = 0;
    uint16_t i = 0, j = 0;
    for (const auto& item : voiceMap)
    {
        voiceList += (item.first + "\n");
        if (Settings::getCurrentVoice().compareTo(item.first.c_str()) == 0)
        {
            selectedVoiceIndex = i;
        }
        i++;
    }
    voiceList.pop_back();
    for (const auto& item : personaMap)
    {
        personaList += (item.first + "\n");
        if (Settings::getCurrentPersona().compareTo(item.first.c_str()) == 0)
        {
            selectedPersonaIndex = j;
        }
        j++;
    }
    personaList.pop_back();
    lv_dropdown_set_options(guider_ui.screen_system_setting_ddlist_voice_type, voiceList.c_str());
    lv_dropdown_set_symbol(guider_ui.screen_system_setting_ddlist_voice_type, LV_SYMBOL_DOWN);
    lv_dropdown_set_selected(guider_ui.screen_system_setting_ddlist_voice_type, selectedVoiceIndex);
    lv_obj_t* voice_list = lv_dropdown_get_list(guider_ui.screen_system_setting_ddlist_voice_type);
    lv_obj_set_style_text_font(voice_list, &lv_customer_font_Siyuan_Regular_14, 0);

    lv_dropdown_set_options(guider_ui.screen_system_setting_ddlist_persona, personaList.c_str());
    lv_dropdown_set_symbol(guider_ui.screen_system_setting_ddlist_persona, LV_SYMBOL_DOWN);
    lv_dropdown_set_selected(guider_ui.screen_system_setting_ddlist_persona, selectedPersonaIndex);
    lv_obj_t* persona_list = lv_dropdown_get_list(guider_ui.screen_system_setting_ddlist_persona);
    lv_obj_set_style_text_font(persona_list, &lv_customer_font_Siyuan_Regular_14, 0);

    lv_slider_set_value(guider_ui.screen_system_setting_slider_speak_speed,
                        static_cast<int32_t>(Settings::getCurrentSpeakSpeedRatio() * 10), LV_ANIM_OFF);
    lv_slider_set_value(guider_ui.screen_system_setting_slider_speak_volume,
                        static_cast<int32_t>(Settings::getCurrentSpeakVolumeRatio() * 100), LV_ANIM_OFF);
    lv_slider_set_value(guider_ui.screen_system_setting_slider_screen_brightness, Settings::getScreenBrightness(),
                        LV_ANIM_ON);
}

void LvglDisplay::disableBtn(const String& title, const uint32_t color)
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        lv_obj_remove_flag(guider_ui.screen_main_btn_speak, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_color(guider_ui.screen_main_btn_speak, lv_color_hex(color),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(guider_ui.screen_main_btn_speak_label, title.c_str());
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::enableBtn(const String& title, const uint32_t color)
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        lv_obj_add_flag(guider_ui.screen_main_btn_speak, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_color(guider_ui.screen_main_btn_speak, lv_color_hex(color),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(guider_ui.screen_main_btn_speak_label, title.c_str());
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

static uint32_t my_tick()
{
    return millis();
}


void LvglDisplay::begin()
{
    analogWrite(8, static_cast<int>(Settings::getScreenBrightness() * 2.55)); // 设置屏幕亮度
    lv_init();
    lv_tick_set_cb(my_tick);
    ts.begin();
    lv_display_t* disp;
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);

    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    xTaskCreate([](void* ptr)
    {
        while (true)
        {
            if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
            {
                lv_timer_handler();
                xSemaphoreGiveRecursive(lvglUpdateLock);
            }
            vTaskDelay(5);
        }
    }, "lvgl-updater", 8 * 1024, nullptr, 1, nullptr);
}

// 更新首页聊天列表
void LvglDisplay::updateChatText(const MessageRole messageRole, const bool newLine, const std::string& text)
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        if (!newLine && last_message != nullptr)
        {
            lv_label_set_text(last_message, text.c_str());
            lv_obj_scroll_to_y(guider_ui.screen_main_list_message_history, LV_COORD_MAX, LV_ANIM_ON);
            xSemaphoreGiveRecursive(lvglUpdateLock);
            return;
        }
        last_message = lv_list_add_text(guider_ui.screen_main_list_message_history, text.c_str());
        lv_label_set_long_mode(last_message, LV_LABEL_LONG_WRAP);
        current_message_number++;
        lv_obj_set_style_text_font(last_message, &lv_customer_font_Siyuan_Regular_14, 0);
        lv_obj_set_style_text_align(last_message, LV_TEXT_ALIGN_LEFT, 0);
        lv_obj_set_style_pad_top(last_message, 20, 0);
        lv_obj_set_style_bg_opa(last_message, 0, 0);
        if (messageRole == Robot)
        {
            lv_obj_set_style_text_color(last_message, lv_color_make(50, 50, 50), 0);
        }
        else
        {
            lv_obj_set_style_text_color(last_message, lv_color_make(0, 0, 0), 0);
        }
        if (current_message_number > 20)
        {
            lv_obj_t* first_message = lv_obj_get_child(guider_ui.screen_main_list_message_history, 0);
            if (first_message != nullptr)
            {
                lv_obj_del(first_message);
                current_message_number--;
            }
        }
        lv_obj_scroll_to_y(guider_ui.screen_main_list_message_history, LV_COORD_MAX, LV_ANIM_ON);
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateState(const std::string& state)
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        lv_label_set_text(guider_ui.screen_main_label_global_state, state.c_str());
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateTime(const std::string& time)
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        lv_label_set_text(guider_ui.screen_main_label_current_time, time.c_str());
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateWifiState(bool success)
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        if (success)
        {
            lv_img_set_src(guider_ui.screen_main_img_wifi_state, &_wifi_RGB565A8_20x20);
        }
        else
        {
            lv_img_set_src(guider_ui.screen_main_img_wifi_state, &_no_wifi_RGB565A8_20x20);
        }
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

// 点击了列表中的某一个wifi后，弹出对话框，输入wifi密码
static void click_wifi_item_event_callback(lv_event_t* e)
{
    void* user_data = lv_event_get_user_data(e);
    if (user_data != nullptr)
    {
        guider_ui.screen_networking_settings_clicked_wifi_ssid = (char*)user_data;
        lv_textarea_set_text(guider_ui.screen_networking_setting_ta_wifi_password, "");
        lv_obj_clear_flag(guider_ui.screen_networking_setting_cont_wifi_password_dialog, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_networking_setting_cont_mask, LV_OBJ_FLAG_HIDDEN);
    }
}

// 渲染wifi列表，添加每一条wifi信息
void add_wifi_item(const WifiInfo& wifi)
{
    lv_obj_t* wifi_item = lv_list_add_btn(guider_ui.screen_networking_setting_list_wlan, LV_SYMBOL_WIFI,
                                          wifi._ssid.c_str());
    lv_obj_set_style_text_font(wifi_item, &lv_customer_font_Siyuan_Regular_14, 0);
    if (wifi._ssid.compareTo(Settings::getWifiInfo().first.c_str()) == 0)
    {
        lv_obj_set_style_text_color(wifi_item, lv_color_make(0, 128, 0), 0);
    }
    char* ssid_copy = strdup(wifi._ssid.c_str());
    if (ssid_copy != nullptr)
    {
        lv_obj_add_event_cb(wifi_item, click_wifi_item_event_callback, LV_EVENT_CLICKED, ssid_copy);
    }
}

void LvglDisplay::loadWifiList(lv_timer_t* timer)
{
    refreshImageAngle -= 100;
    if (refreshImageAngle <= 0) refreshImageAngle = 3600;
    lv_img_set_angle(guider_ui.screen_networking_setting_img_refresh, refreshImageAngle);
    if (scanningWifi)
    {
        const int scanResult = WiFi.scanComplete();
        if (scanResult >= 0)
        {
            refreshImageAngle = 3600;
            for (int i = 0; i < scanResult; i++)
            {
                add_wifi_item(WifiInfo(WiFi.SSID(i), WiFi.RSSI(i), WiFi.encryptionType(i) != WIFI_AUTH_OPEN));
            }
            lv_timer_delete(timer);
            scanningWifi = false;
        }
    }
    else
    {
        scanningWifi = true;
        WiFi.scanNetworks(true);
    }
}

void LvglDisplay::playSpeakAnim()
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        lv_obj_remove_flag(guider_ui.screen_main_animimg_1, LV_OBJ_FLAG_HIDDEN);
        lv_animimg_start(guider_ui.screen_main_animimg_1);
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::stopSpeakAnim()
{
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE)
    {
        lv_obj_add_flag(guider_ui.screen_main_animimg_1, LV_OBJ_FLAG_HIDDEN);
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}
