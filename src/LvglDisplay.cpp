#include "LvglDisplay.h"
#include "Settings.h"
#include <FT6336.h>
#include <gui/events_init.h>
#include <gui/gui_guider.h>
#include "lvgl_interface.h"

#define TFT_WIDTH   320
#define TFT_HEIGHT   480
#define I2C_SDA 10
#define I2C_SCL 13
#define RST_N_PIN 9
#define INT_N_PIN 12
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT/10)

static lv_disp_draw_buf_t draw_buf;

FT6336 ts(I2C_SDA, I2C_SCL, INT_N_PIN, RST_N_PIN, TFT_WIDTH, TFT_HEIGHT);
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data) {
    ts.read();
    if (ts.isTouched) {
        data->point.x = static_cast<lv_coord_t>(ts.points[0].x);
        data->point.y = static_cast<lv_coord_t>(ts.points[0].y);
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

lv_ui guider_ui;
lv_obj_t *LvglDisplay::last_message;
int LvglDisplay::current_message_number = 0;
SemaphoreHandle_t LvglDisplay::lvglUpdateLock = xSemaphoreCreateRecursiveMutex();

// 这个函数是在lvgl线程中调用的，无需加锁
void LvglDisplay::loadSystemSettingData() {
    const std::map<std::string, std::string> &voiceMap = Settings::getVoiceMap();
    const std::map<std::string, std::string> &personaMap = Settings::getPersonaMap();
    std::string voiceList;
    std::string personaList;
    uint16_t selectedVoiceIndex = 0;
    uint16_t selectedPersonaIndex = 0;
    uint16_t i = 0, j = 0;
    for (const auto &item: voiceMap) {
        voiceList += (item.first + "\n");
        if (Settings::getCurrentVoice().compareTo(item.first.c_str()) == 0) {
            selectedVoiceIndex = i;
        }
        i++;
    }
    voiceList.pop_back();
    for (const auto &item: personaMap) {
        personaList += (item.first + "\n");
        if (Settings::getCurrentPersona().compareTo(item.first.c_str()) == 0) {
            selectedPersonaIndex = j;
        }
        j++;
    }
    personaList.pop_back();
    lv_dropdown_set_options(guider_ui.system_setting_voice_type, voiceList.c_str());
    lv_dropdown_set_symbol(guider_ui.system_setting_voice_type, LV_SYMBOL_DOWN);
    lv_dropdown_set_selected(guider_ui.system_setting_voice_type, selectedVoiceIndex);

    lv_dropdown_set_options(guider_ui.system_setting_persona, personaList.c_str());
    lv_dropdown_set_symbol(guider_ui.system_setting_persona, LV_SYMBOL_DOWN);
    lv_dropdown_set_selected(guider_ui.system_setting_persona, selectedPersonaIndex);

    lv_dropdown_set_options(guider_ui.system_setting_environment_noise, "安静\n一般\n嘈杂");
    lv_dropdown_set_symbol(guider_ui.system_setting_environment_noise, LV_SYMBOL_DOWN);
    if (Settings::getRecordingRmsThreshold() == ENV_QUIET) {
        lv_dropdown_set_selected(guider_ui.system_setting_environment_noise, 0);
    } else if (Settings::getRecordingRmsThreshold() == ENV_GENERAL) {
        lv_dropdown_set_selected(guider_ui.system_setting_environment_noise, 1);
    } else {
        lv_dropdown_set_selected(guider_ui.system_setting_environment_noise, 2);
    }
    lv_spinbox_set_value(guider_ui.system_setting_speed,
                         static_cast<int32_t>(Settings::getCurrentSpeakSpeedRatio() * 10));
    lv_spinbox_set_value(guider_ui.system_setting_recording_pause, Settings::getSpeakPauseDuration() / 100);
    lv_slider_set_value(guider_ui.system_setting_slider_volume,
                        static_cast<int32_t>(Settings::getCurrentSpeakVolumeRatio() * 100), LV_ANIM_OFF);
    lv_slider_set_value(guider_ui.system_setting_slider_brightness, Settings::getScreenBrightness(), LV_ANIM_ON);
}

void LvglDisplay::begin() {
    lv_init();
    tft.begin();
    ts.begin();

    static auto *buf1 = static_cast<lv_color_t *>(ps_malloc(DRAW_BUF_SIZE * sizeof(lv_color_t)));
    if (buf1 == nullptr) {
        log_e("Lvgl display buffer malloc failed!");
        ESP.restart();
    }
    lv_disp_draw_buf_init(&draw_buf, buf1, nullptr, DRAW_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = false;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    xTaskCreate([](void *ptr) {
        while (true) {
            if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
                lv_timer_handler();
                xSemaphoreGiveRecursive(lvglUpdateLock);
            }
            vTaskDelay(5);
        }
    }, "lvgl-updater", 4096, nullptr, 1, nullptr);
}

// 更新首页聊天列表
void LvglDisplay::updateChatText(const MessageRole messageRole, const bool newLine, const std::string &text) {
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
        if (!newLine && last_message != nullptr) {
            lv_label_set_text(last_message, text.c_str());
            lv_obj_scroll_to_y(guider_ui.home_page_message_list, LV_COORD_MAX, LV_ANIM_ON);
            xSemaphoreGiveRecursive(lvglUpdateLock);
            return;
        }
        last_message = lv_list_add_text(guider_ui.home_page_message_list, text.c_str());
        lv_label_set_long_mode(last_message, LV_LABEL_LONG_WRAP);
        current_message_number++;
        lv_obj_set_style_text_font(last_message, &lv_customer_font_Siyuan_Regular_16, 0);
        lv_obj_set_style_text_align(last_message, LV_TEXT_ALIGN_LEFT, 0);
        lv_obj_set_style_pad_top(last_message, 20, 0);
        lv_obj_set_style_bg_opa(last_message, 0, 0);
        if (messageRole == Robot) {
            lv_obj_set_style_text_color(last_message, lv_color_make(50, 50, 50), 0);
        } else {
            lv_obj_set_style_text_color(last_message, lv_color_make(0, 0, 0), 0);
        }
        if (current_message_number > 20) {
            lv_obj_t *first_message = lv_obj_get_child(guider_ui.home_page_message_list, 0);
            if (first_message != nullptr) {
                lv_obj_del(first_message);
                current_message_number--;
            }
        }
        lv_obj_scroll_to_y(guider_ui.home_page_message_list, LV_COORD_MAX, LV_ANIM_ON);
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateState(const std::string &state) {
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
        lv_label_set_text(guider_ui.home_page_header_state, state.c_str());
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateTime(const std::string &time) {
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
        lv_label_set_text(guider_ui.home_page_header_time, time.c_str());
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateWifiState(bool success) {
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
        if (success) {
            lv_obj_add_flag(guider_ui.home_page_header_wifi_no, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_clear_flag(guider_ui.home_page_header_wifi_no, LV_OBJ_FLAG_HIDDEN);
        }
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}

void LvglDisplay::updateRecordingButtonImage(const void *img) {
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
        lv_imgbtn_set_src(guider_ui.home_page_imgbtn_recording, LV_IMGBTN_STATE_RELEASED,
                          NULL, img, NULL);
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}


// 点击了列表中的某一个wifi后，弹出对话框，输入wifi密码
static void click_wifi_item_event_callback(lv_event_t *e) {
    void *user_data = lv_event_get_user_data(e);
    if (user_data != nullptr) {
        guider_ui.clicked_wifi_ssid = (char *) user_data;
        lv_label_set_text(guider_ui.network_setting_connect_wifi_window_title, (char *) user_data);
        lv_textarea_set_text(guider_ui.network_setting_wifi_password_textarea, "");
        lv_obj_clear_flag(guider_ui.network_setting_overlay, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.network_setting_connect_wifi_window, LV_OBJ_FLAG_HIDDEN);
    }
}

// 渲染wifi列表，添加每一条wifi信息
void add_wifi_item(const WifiInfo &wifi) {
    lv_obj_t *wifi_item = lv_list_add_btn(guider_ui.network_setting_wifi_list, LV_SYMBOL_WIFI, wifi._ssid.c_str());
    lv_obj_set_style_text_font(wifi_item, &lv_customer_font_Siyuan_Regular_16, 0);
    if (wifi._ssid.compareTo(Settings::getWifiInfo().first.c_str()) == 0) {
        lv_obj_set_style_text_color(wifi_item, lv_color_make(0, 128, 0), 0);
    }
    char *ssid_copy = strdup(wifi._ssid.c_str());
    if (ssid_copy != nullptr) {
        lv_obj_add_event_cb(wifi_item, click_wifi_item_event_callback, LV_EVENT_CLICKED, ssid_copy);
    }
}

void LvglDisplay::loadWifiList(const bool forceRefresh) {
    const std::vector<WifiInfo> &list = Settings::getWifiList(forceRefresh);
    for (const auto &wifi: list) {
        if (forceRefresh) {
            // 强制刷新的时候，是点击了UI上的刷新按钮，那里会创建一个新的task来加载wifi，
            // 所以本段逻辑不在lv_timer_handler中执行，需要加锁
            if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
                add_wifi_item(wifi);
                // wifi列表加载完毕，停止播放动画
                lv_anim_del(guider_ui.network_setting_animimg_refresh, nullptr);
                xSemaphoreGiveRecursive(lvglUpdateLock);
            }
        } else {
            add_wifi_item(wifi);
        }
    }
}

void LvglDisplay::updateRecordingState(bool active) {
    if (xSemaphoreTakeRecursive(lvglUpdateLock, portMAX_DELAY) == pdTRUE) {
        if (active) {
            lv_obj_set_style_bg_color(guider_ui.home_page_recording_state, lv_color_make(0, 255, 0), 0);
        } else {
            lv_obj_set_style_bg_color(guider_ui.home_page_recording_state, lv_color_make(153, 153, 153), 0);
        }
        xSemaphoreGiveRecursive(lvglUpdateLock);
    }
}
