/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_customer_fonts/guider_customer_fonts.h"

typedef struct {

    lv_obj_t *screen_main;
    bool screen_main_del;
    lv_obj_t *screen_main_container_header;
    lv_obj_t *screen_main_img_wifi_state;
    lv_obj_t *screen_main_label_current_time;
    lv_obj_t *screen_main_btn_recording_state;
    lv_obj_t *screen_main_btn_recording_state_label;
    lv_obj_t *screen_main_label_global_state;
    lv_obj_t *screen_main_list_message_history;
    lv_obj_t *screen_main_imgbtn_mic;
    lv_obj_t *screen_main_imgbtn_mic_label;
    lv_obj_t *screen_settings;
    bool screen_settings_del;
    lv_obj_t *screen_settings_label_settings_title;
    lv_obj_t *screen_settings_btn_networking_setting;
    lv_obj_t *screen_settings_btn_networking_setting_label;
    lv_obj_t *screen_settings_btn_system_setting;
    lv_obj_t *screen_settings_btn_system_setting_label;
    lv_obj_t *screen_settings_btn_reset_setting;
    lv_obj_t *screen_settings_btn_reset_setting_label;
    lv_obj_t *screen_settings_cont_1;
    lv_obj_t *screen_settings_label_1;
    lv_obj_t *screen_settings_btn_1;
    lv_obj_t *screen_settings_btn_1_label;
    lv_obj_t *screen_networking_setting;
    bool screen_networking_setting_del;
    lv_obj_t *screen_networking_setting_label_networking_setting_title;
    lv_obj_t *screen_networking_setting_list_wlan;
    lv_obj_t *screen_networking_setting_label_tips;
    lv_obj_t *screen_networking_setting_img_refresh;
    lv_anim_t screen_networking_setting_anim;
    lv_obj_t *screen_networking_setting_btn_back;
    lv_obj_t *screen_networking_setting_btn_back_label;
    lv_obj_t *screen_networking_setting_cont_mask;
    lv_obj_t *screen_networking_setting_cont_wifi_password_dialog;
    lv_obj_t *screen_networking_setting_btn_cancel;
    lv_obj_t *screen_networking_setting_btn_cancel_label;
    lv_obj_t *screen_networking_setting_btn_confirm;
    lv_obj_t *screen_networking_setting_btn_confirm_label;
    lv_obj_t *screen_networking_setting_label_title;
    lv_obj_t *screen_networking_setting_ta_wifi_password;
    char *screen_networking_settings_clicked_wifi_ssid;
    lv_obj_t *screen_system_setting;
    bool screen_system_setting_del;
    lv_obj_t *screen_system_setting_label_speaker_setting_title;
    lv_obj_t *screen_system_setting_label_speak_volume;
    lv_obj_t *screen_system_setting_slider_speak_volume;
    lv_obj_t *screen_system_setting_label_speak_speed;
    lv_obj_t *screen_system_setting_label_voice_type;
    lv_obj_t *screen_system_setting_ddlist_voice_type;
    lv_obj_t *screen_system_setting_ddlist_persona;
    lv_obj_t *screen_system_setting_ddlist_environment_noise;
    lv_obj_t *screen_system_setting_label_persona;
    lv_obj_t *screen_system_setting_label_environment_noise;
    lv_obj_t *screen_system_setting_slider_screen_brightness;
    lv_obj_t *screen_system_setting_label_screen_brightness;
    lv_obj_t *screen_system_setting_btn_back;
    lv_obj_t *screen_system_setting_btn_back_label;
    lv_obj_t *screen_system_setting_slider_speak_speed;
    lv_obj_t *g_kb_top_layer;
} lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui *ui);

void ui_init_style(lv_style_t *style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t **new_scr, bool new_scr_del, bool *old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean,
                           bool auto_del);

void ui_animation(void *var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value,
                  lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb,
                  lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_main(lv_ui *ui);

void setup_scr_screen_settings(lv_ui *ui);

void setup_scr_screen_networking_setting(lv_ui *ui);

void setup_scr_screen_system_setting(lv_ui *ui);

LV_IMAGE_DECLARE(_wifi_RGB565A8_20x20);
LV_IMAGE_DECLARE(_no_wifi_RGB565A8_20x20);
LV_IMAGE_DECLARE(_stop_RGB565A8_25x25);
LV_IMAGE_DECLARE(_mic_on_RGB565A8_25x25);
LV_IMAGE_DECLARE(_mic_off_RGB565A8_25x25);
LV_IMAGE_DECLARE(_refresh_RGB565A8_20x20);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_Siyuan_Regular_16)
LV_FONT_DECLARE(lv_font_Siyuan_Regular_12)


#ifdef __cplusplus
}
#endif
#endif
