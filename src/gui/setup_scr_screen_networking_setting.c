/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_networking_setting(lv_ui *ui)
{
    //Write codes screen_networking_setting
    ui->screen_networking_setting = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_networking_setting, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_networking_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_networking_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_networking_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_label_networking_setting_title
    ui->screen_networking_setting_label_networking_setting_title = lv_label_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_label_networking_setting_title, 32, 30);
    lv_obj_set_size(ui->screen_networking_setting_label_networking_setting_title, 109, 18);
    lv_label_set_text(ui->screen_networking_setting_label_networking_setting_title, "" LV_SYMBOL_WIFI " WiFi设置 ");
    lv_label_set_long_mode(ui->screen_networking_setting_label_networking_setting_title, LV_LABEL_LONG_WRAP);

    //Write style for screen_networking_setting_label_networking_setting_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_label_networking_setting_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_label_networking_setting_title, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_label_networking_setting_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_label_networking_setting_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_label_networking_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_list_wlan
    ui->screen_networking_setting_list_wlan = lv_list_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_list_wlan, 5, 96);
    lv_obj_set_size(ui->screen_networking_setting_list_wlan, 230, 214);
    lv_obj_set_scrollbar_mode(ui->screen_networking_setting_list_wlan, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_screen_networking_setting_list_wlan_main_main_default
    static lv_style_t style_screen_networking_setting_list_wlan_main_main_default;
    ui_init_style(&style_screen_networking_setting_list_wlan_main_main_default);

    lv_style_set_pad_top(&style_screen_networking_setting_list_wlan_main_main_default, 5);
    lv_style_set_pad_left(&style_screen_networking_setting_list_wlan_main_main_default, 5);
    lv_style_set_pad_right(&style_screen_networking_setting_list_wlan_main_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_networking_setting_list_wlan_main_main_default, 5);
    lv_style_set_bg_opa(&style_screen_networking_setting_list_wlan_main_main_default, 255);
    lv_style_set_bg_color(&style_screen_networking_setting_list_wlan_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_networking_setting_list_wlan_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_networking_setting_list_wlan_main_main_default, 1);
    lv_style_set_border_opa(&style_screen_networking_setting_list_wlan_main_main_default, 255);
    lv_style_set_border_color(&style_screen_networking_setting_list_wlan_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_networking_setting_list_wlan_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_networking_setting_list_wlan_main_main_default, 3);
    lv_style_set_shadow_width(&style_screen_networking_setting_list_wlan_main_main_default, 0);
    lv_obj_add_style(ui->screen_networking_setting_list_wlan, &style_screen_networking_setting_list_wlan_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_networking_setting_list_wlan_main_scrollbar_default
    static lv_style_t style_screen_networking_setting_list_wlan_main_scrollbar_default;
    ui_init_style(&style_screen_networking_setting_list_wlan_main_scrollbar_default);

    lv_style_set_radius(&style_screen_networking_setting_list_wlan_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_networking_setting_list_wlan_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_networking_setting_list_wlan_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_networking_setting_list_wlan_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_networking_setting_list_wlan, &style_screen_networking_setting_list_wlan_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_networking_setting_list_wlan_extra_btns_main_default
    static lv_style_t style_screen_networking_setting_list_wlan_extra_btns_main_default;
    ui_init_style(&style_screen_networking_setting_list_wlan_extra_btns_main_default);

    lv_style_set_pad_top(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_screen_networking_setting_list_wlan_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_networking_setting_list_wlan_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 255);
    lv_style_set_radius(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_screen_networking_setting_list_wlan_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_networking_setting_list_wlan_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_networking_setting_list_wlan_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_screen_networking_setting_list_wlan_extra_texts_main_default
    static lv_style_t style_screen_networking_setting_list_wlan_extra_texts_main_default;
    ui_init_style(&style_screen_networking_setting_list_wlan_extra_texts_main_default);

    lv_style_set_pad_top(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_screen_networking_setting_list_wlan_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_networking_setting_list_wlan_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 255);
    lv_style_set_radius(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_screen_networking_setting_list_wlan_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_screen_networking_setting_list_wlan_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_networking_setting_list_wlan_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes screen_networking_setting_label_tips
    ui->screen_networking_setting_label_tips = lv_label_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_label_tips, 9, 71);
    lv_obj_set_size(ui->screen_networking_setting_label_tips, 120, 15);
    lv_label_set_text(ui->screen_networking_setting_label_tips, "连接附近的WLAN");
    lv_label_set_long_mode(ui->screen_networking_setting_label_tips, LV_LABEL_LONG_WRAP);

    //Write style for screen_networking_setting_label_tips, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_label_tips, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_label_tips, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_label_tips, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_label_tips, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_label_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_btn_refresh
    ui->screen_networking_setting_btn_refresh = lv_button_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_btn_refresh, 163, 68);
    lv_obj_set_size(ui->screen_networking_setting_btn_refresh, 20, 20);
    ui->screen_networking_setting_btn_refresh_label = lv_label_create(ui->screen_networking_setting_btn_refresh);
    lv_label_set_text(ui->screen_networking_setting_btn_refresh_label, "" LV_SYMBOL_REFRESH "");
    lv_label_set_long_mode(ui->screen_networking_setting_btn_refresh_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_networking_setting_btn_refresh_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_networking_setting_btn_refresh, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_networking_setting_btn_refresh_label, LV_PCT(100));

    //Write style for screen_networking_setting_btn_refresh, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_btn_refresh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting_btn_refresh, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting_btn_refresh, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_networking_setting_btn_refresh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_btn_refresh, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_btn_refresh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_btn_refresh, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_btn_refresh, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_btn_refresh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_btn_refresh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_btn_back
    ui->screen_networking_setting_btn_back = lv_button_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_btn_back, 8, 30);
    lv_obj_set_size(ui->screen_networking_setting_btn_back, 20, 20);
    ui->screen_networking_setting_btn_back_label = lv_label_create(ui->screen_networking_setting_btn_back);
    lv_label_set_text(ui->screen_networking_setting_btn_back_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->screen_networking_setting_btn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_networking_setting_btn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_networking_setting_btn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_networking_setting_btn_back_label, LV_PCT(100));

    //Write style for screen_networking_setting_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_networking_setting_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_btn_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_btn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_btn_back, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_cont_mask
    ui->screen_networking_setting_cont_mask = lv_obj_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_cont_mask, 0, 0);
    lv_obj_set_size(ui->screen_networking_setting_cont_mask, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_networking_setting_cont_mask, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_networking_setting_cont_mask, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_networking_setting_cont_mask, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_networking_setting_cont_mask, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_networking_setting_cont_mask, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_networking_setting_cont_mask, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_networking_setting_cont_mask, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_cont_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_cont_wifi_password_dialog
    ui->screen_networking_setting_cont_wifi_password_dialog = lv_obj_create(ui->screen_networking_setting);
    lv_obj_set_pos(ui->screen_networking_setting_cont_wifi_password_dialog, 5, 60);
    lv_obj_set_size(ui->screen_networking_setting_cont_wifi_password_dialog, 230, 102);
    lv_obj_set_scrollbar_mode(ui->screen_networking_setting_cont_wifi_password_dialog, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_networking_setting_cont_wifi_password_dialog, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_networking_setting_cont_wifi_password_dialog, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_networking_setting_cont_wifi_password_dialog, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_networking_setting_cont_wifi_password_dialog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_networking_setting_cont_wifi_password_dialog, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_networking_setting_cont_wifi_password_dialog, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_cont_wifi_password_dialog, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_cont_wifi_password_dialog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting_cont_wifi_password_dialog, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting_cont_wifi_password_dialog, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_networking_setting_cont_wifi_password_dialog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_networking_setting_cont_wifi_password_dialog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_networking_setting_cont_wifi_password_dialog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_networking_setting_cont_wifi_password_dialog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_cont_wifi_password_dialog, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_btn_cancel
    ui->screen_networking_setting_btn_cancel = lv_button_create(ui->screen_networking_setting_cont_wifi_password_dialog);
    lv_obj_set_pos(ui->screen_networking_setting_btn_cancel, 123, 64);
    lv_obj_set_size(ui->screen_networking_setting_btn_cancel, 100, 30);
    ui->screen_networking_setting_btn_cancel_label = lv_label_create(ui->screen_networking_setting_btn_cancel);
    lv_label_set_text(ui->screen_networking_setting_btn_cancel_label, "取消");
    lv_label_set_long_mode(ui->screen_networking_setting_btn_cancel_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_networking_setting_btn_cancel_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_networking_setting_btn_cancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_networking_setting_btn_cancel_label, LV_PCT(100));

    //Write style for screen_networking_setting_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting_btn_cancel, lv_color_hex(0xff0027), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting_btn_cancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_networking_setting_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_btn_cancel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_btn_cancel, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_btn_confirm
    ui->screen_networking_setting_btn_confirm = lv_button_create(ui->screen_networking_setting_cont_wifi_password_dialog);
    lv_obj_set_pos(ui->screen_networking_setting_btn_confirm, 4, 64);
    lv_obj_set_size(ui->screen_networking_setting_btn_confirm, 100, 30);
    ui->screen_networking_setting_btn_confirm_label = lv_label_create(ui->screen_networking_setting_btn_confirm);
    lv_label_set_text(ui->screen_networking_setting_btn_confirm_label, "连接");
    lv_label_set_long_mode(ui->screen_networking_setting_btn_confirm_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_networking_setting_btn_confirm_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_networking_setting_btn_confirm, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_networking_setting_btn_confirm_label, LV_PCT(100));

    //Write style for screen_networking_setting_btn_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_btn_confirm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting_btn_confirm, lv_color_hex(0x26B08C), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting_btn_confirm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_networking_setting_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_btn_confirm, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_btn_confirm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_btn_confirm, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_btn_confirm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_btn_confirm, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_label_title
    ui->screen_networking_setting_label_title = lv_label_create(ui->screen_networking_setting_cont_wifi_password_dialog);
    lv_obj_set_pos(ui->screen_networking_setting_label_title, 4, 6);
    lv_obj_set_size(ui->screen_networking_setting_label_title, 219, 15);
    lv_label_set_text(ui->screen_networking_setting_label_title, "请输入WiFi密码");
    lv_label_set_long_mode(ui->screen_networking_setting_label_title, LV_LABEL_LONG_WRAP);

    //Write style for screen_networking_setting_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_networking_setting_label_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_label_title, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_label_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_label_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_networking_setting_ta_wifi_password
    ui->screen_networking_setting_ta_wifi_password = lv_textarea_create(ui->screen_networking_setting_cont_wifi_password_dialog);
    lv_obj_set_pos(ui->screen_networking_setting_ta_wifi_password, 0, 28);
    lv_obj_set_size(ui->screen_networking_setting_ta_wifi_password, 226, 30);
    lv_textarea_set_text(ui->screen_networking_setting_ta_wifi_password, "");
    lv_textarea_set_placeholder_text(ui->screen_networking_setting_ta_wifi_password, "");
    lv_textarea_set_password_bullet(ui->screen_networking_setting_ta_wifi_password, "*");
    lv_textarea_set_password_mode(ui->screen_networking_setting_ta_wifi_password, true);
    lv_textarea_set_one_line(ui->screen_networking_setting_ta_wifi_password, true);
    lv_textarea_set_accepted_chars(ui->screen_networking_setting_ta_wifi_password, "");
    lv_textarea_set_max_length(ui->screen_networking_setting_ta_wifi_password, 32);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->screen_networking_setting_ta_wifi_password, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    //Write style for screen_networking_setting_ta_wifi_password, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_networking_setting_ta_wifi_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_networking_setting_ta_wifi_password, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_networking_setting_ta_wifi_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_networking_setting_ta_wifi_password, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_networking_setting_ta_wifi_password, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_ta_wifi_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting_ta_wifi_password, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting_ta_wifi_password, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_networking_setting_ta_wifi_password, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_networking_setting_ta_wifi_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_networking_setting_ta_wifi_password, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_networking_setting_ta_wifi_password, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_networking_setting_ta_wifi_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_networking_setting_ta_wifi_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_networking_setting_ta_wifi_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_networking_setting_ta_wifi_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_ta_wifi_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_networking_setting_ta_wifi_password, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_networking_setting_ta_wifi_password, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_networking_setting_ta_wifi_password, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_networking_setting_ta_wifi_password, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_networking_setting_ta_wifi_password, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //The custom code of screen_networking_setting.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_networking_setting);

    //Init events for screen.
    events_init_screen_networking_setting(ui);
}
