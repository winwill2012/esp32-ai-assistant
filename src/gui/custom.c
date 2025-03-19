/*
 * Copyright 2023 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "lvgl_interface.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
void custom_init(lv_ui *ui) {
    /* Add your codes here */
}

void textarea_focus_event_cb(lv_event_t *e) {
    lv_obj_clear_flag(guider_ui.network_setting_keyboard, LV_OBJ_FLAG_HIDDEN);
}

void textarea_blur_event_cb(lv_event_t *e) {
    lv_obj_add_flag(guider_ui.network_setting_keyboard, LV_OBJ_FLAG_HIDDEN);
    guider_ui.input_wifi_password = strdup(lv_textarea_get_text(guider_ui.network_setting_wifi_password_textarea));
}

void confirm_btn_event_cb(lv_event_t *e) {
    connect_wifi(guider_ui.clicked_wifi_ssid, guider_ui.input_wifi_password);
}

void keyboard_ready_event_cb(lv_event_t *e) {
    guider_ui.input_wifi_password = strdup(lv_textarea_get_text(guider_ui.network_setting_wifi_password_textarea));
    lv_obj_add_flag(guider_ui.network_setting_keyboard, LV_OBJ_FLAG_HIDDEN);
}

void connect_wifi_window_blur_event_cb(lv_event_t *e) {
    lv_obj_add_flag(guider_ui.network_setting_connect_wifi_window, LV_OBJ_FLAG_HIDDEN);
}

void network_setting_custom_init(lv_ui *ui) {
    ui->network_setting_connect_wifi_window = lv_win_create(guider_ui.network_setting, 30);
    lv_obj_set_style_pad_all(ui->network_setting_connect_wifi_window, 0, 0);
    lv_obj_set_size(ui->network_setting_connect_wifi_window, lv_pct(100), 110);
    lv_obj_set_style_radius(ui->network_setting_connect_wifi_window, 5, 0);
    lv_obj_align(ui->network_setting_connect_wifi_window, LV_ALIGN_CENTER, 0, -60);
    ui->network_setting_connect_wifi_window_title = lv_win_add_title(ui->network_setting_connect_wifi_window, "");
    lv_obj_set_style_text_font(ui->network_setting_connect_wifi_window_title, &lv_customer_font_Siyuan_Regular_16, 0);

    ui->network_setting_wifi_password_textarea = lv_textarea_create(ui->network_setting_connect_wifi_window);
    lv_textarea_set_password_mode(ui->network_setting_wifi_password_textarea, true);
    lv_textarea_set_one_line(ui->network_setting_wifi_password_textarea, true);
    lv_obj_set_style_text_font(ui->network_setting_wifi_password_textarea, &lv_customer_font_Siyuan_Regular_16, 0);
    lv_textarea_set_placeholder_text(ui->network_setting_wifi_password_textarea, "请输入wifi密码");
    lv_obj_set_size(ui->network_setting_wifi_password_textarea, lv_pct(100), 40);
    lv_obj_align(ui->network_setting_wifi_password_textarea, LV_ALIGN_TOP_MID, 0, 30);
    // 输入框获取焦点事件  -> 加载键盘
    lv_obj_add_event_cb(ui->network_setting_wifi_password_textarea, textarea_focus_event_cb, LV_EVENT_FOCUSED, NULL);
    // 输入护框失去焦点事件 -> 隐藏键盘
    lv_obj_add_event_cb(ui->network_setting_wifi_password_textarea, textarea_blur_event_cb, LV_EVENT_DEFOCUSED,
                        NULL);

    ui->network_setting_keyboard = lv_keyboard_create(lv_layer_top());
    lv_obj_align(ui->network_setting_keyboard, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_keyboard_set_textarea(ui->network_setting_keyboard, ui->network_setting_wifi_password_textarea);
    lv_obj_add_event_cb(ui->network_setting_keyboard, keyboard_ready_event_cb, LV_EVENT_READY, 0);
    lv_obj_add_flag(ui->network_setting_keyboard, LV_OBJ_FLAG_HIDDEN);

    // 创建确认按钮
    ui->network_setting_confirm_btn = lv_btn_create(ui->network_setting_connect_wifi_window);
    lv_obj_set_size(ui->network_setting_confirm_btn, lv_pct(100), 40);
    lv_obj_t *confirm_label = lv_label_create(ui->network_setting_confirm_btn);
    lv_obj_set_style_text_align(confirm_label, LV_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(confirm_label, &lv_customer_font_Siyuan_Regular_16, 0);
    lv_label_set_text(confirm_label, "确  定");
    lv_obj_center(confirm_label);
    lv_obj_align(ui->network_setting_confirm_btn, LV_ALIGN_BOTTOM_MID, 0, -5);
    // 点击确认后的事件 -> 连接wifi
    lv_obj_add_event_cb(ui->network_setting_confirm_btn, confirm_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui->network_setting_connect_wifi_window, connect_wifi_window_blur_event_cb, LV_EVENT_DEFOCUSED,
                        NULL);
    lv_obj_add_flag(ui->network_setting_connect_wifi_window, LV_OBJ_FLAG_HIDDEN);
}