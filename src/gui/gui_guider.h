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

typedef struct {

    lv_obj_t *home_page;
    bool home_page_del;
    lv_obj_t *home_page_container_top;
    lv_obj_t *home_page_header_wifi;
    lv_obj_t *home_page_header_time;
    lv_obj_t *home_page_header_wifi_no;
    lv_obj_t *home_page_header_state;
    lv_obj_t *home_page_header_icon;
    lv_obj_t *home_page_microphone;
    lv_obj_t *home_page_line_stop_recording;
    lv_obj_t *home_page_message_list;
    lv_obj_t *home_page_btn_settings;
    lv_obj_t *home_page_btn_settings_label;
    lv_obj_t *settings_page;
    bool settings_page_del;
    lv_obj_t *settings_page_label_setting_title;
    lv_obj_t *settings_page_imgbtn_back;
    lv_obj_t *settings_page_imgbtn_back_label;
    lv_obj_t *settings_page_btn_2;
    lv_obj_t *settings_page_btn_2_label;
    lv_obj_t *settings_page_btn_3;
    lv_obj_t *settings_page_btn_3_label;
    lv_obj_t *network_setting;
    bool network_setting_del;
    lv_obj_t *network_setting_imgbtn_back;
    lv_obj_t *network_setting_imgbtn_back_label;
    lv_obj_t *network_setting_label_title;
    lv_obj_t *speaker_setting;
    bool speaker_setting_del;
    lv_obj_t *speaker_setting_imgbtn_back;
    lv_obj_t *speaker_setting_imgbtn_back_label;
    lv_obj_t *speaker_setting_label_title;
    lv_obj_t *speaker_setting_spinbox_1;
    lv_obj_t *speaker_setting_spinbox_1_btn_plus;
    lv_obj_t *speaker_setting_spinbox_1_btn_minus;
    lv_obj_t *speaker_setting_ddlist_1;
    lv_obj_t *speaker_setting_ddlist_2;
    lv_obj_t *speaker_setting_bar_1;
    lv_obj_t *speaker_setting_label_1;
    lv_obj_t *speaker_setting_label_2;
    lv_obj_t *speaker_setting_label_3;
    lv_obj_t *speaker_setting_label_4;
} lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui *ui);

void ui_init_style(lv_style_t *style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t **new_scr, bool new_scr_del, bool *old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void *var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value,
                  lv_anim_path_cb_t path_cb,
                  uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb,
                  lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_home_page(lv_ui *ui);

void setup_scr_settings_page(lv_ui *ui);

void setup_scr_network_setting(lv_ui *ui);

void setup_scr_speaker_setting(lv_ui *ui);

LV_IMG_DECLARE(_WIFI_alpha_26x26);
LV_IMG_DECLARE(_robot_alpha_26x26);
LV_IMG_DECLARE(_user_alpha_26x26);
LV_IMG_DECLARE(_micphone_alpha_40x40);
LV_IMG_DECLARE(_retrun_alpha_33x33);
LV_IMG_DECLARE(_retrun_alpha_33x33);
LV_IMG_DECLARE(_retrun_alpha_33x33);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_21)
LV_FONT_DECLARE(lv_customer_font_Siyuan_Regular_16)
LV_FONT_DECLARE(lv_customer_font_Siyuan_Regular_14)
LV_FONT_DECLARE(lv_customer_font_Siyuan_yuanti_14)
LV_FONT_DECLARE(lv_customer_font_Siyuan_Heiti_18)
LV_FONT_DECLARE(lv_customer_font_Siyuan_Heiti_28)
LV_FONT_DECLARE(lv_customer_font_Siyuan_ExtraLight_14)
LV_FONT_DECLARE(lv_customer_font_Siyuan_yuanti_22)


#ifdef __cplusplus
}
#endif
#endif
