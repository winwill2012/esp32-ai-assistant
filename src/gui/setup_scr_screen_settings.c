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



void setup_scr_screen_settings(lv_ui *ui)
{
    //Write codes screen_settings
    ui->screen_settings = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_settings, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_settings, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_settings, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_settings, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_label_settings_title
    ui->screen_settings_label_settings_title = lv_label_create(ui->screen_settings);
    lv_obj_set_pos(ui->screen_settings_label_settings_title, 83, 29);
    lv_obj_set_size(ui->screen_settings_label_settings_title, 72, 18);
    lv_label_set_text(ui->screen_settings_label_settings_title, "设置");
    lv_label_set_long_mode(ui->screen_settings_label_settings_title, LV_LABEL_LONG_WRAP);

    //Write style for screen_settings_label_settings_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_settings_label_settings_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_settings_label_settings_title, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_settings_label_settings_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_settings_label_settings_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_label_settings_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_btn_networking_setting
    ui->screen_settings_btn_networking_setting = lv_button_create(ui->screen_settings);
    lv_obj_set_pos(ui->screen_settings_btn_networking_setting, 23, 69);
    lv_obj_set_size(ui->screen_settings_btn_networking_setting, 194, 45);
    ui->screen_settings_btn_networking_setting_label = lv_label_create(ui->screen_settings_btn_networking_setting);
    lv_label_set_text(ui->screen_settings_btn_networking_setting_label, "" LV_SYMBOL_WIFI " WiFi设置");
    lv_label_set_long_mode(ui->screen_settings_btn_networking_setting_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_settings_btn_networking_setting_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_settings_btn_networking_setting, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_settings_btn_networking_setting_label, LV_PCT(100));

    //Write style for screen_settings_btn_networking_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_settings_btn_networking_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_settings_btn_networking_setting, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_settings_btn_networking_setting, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_settings_btn_networking_setting, lv_color_hex(0x93acc1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_settings_btn_networking_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_settings_btn_networking_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_settings_btn_networking_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_btn_networking_setting, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_btn_networking_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_settings_btn_networking_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_settings_btn_networking_setting, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_settings_btn_networking_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_settings_btn_networking_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_btn_system_setting
    ui->screen_settings_btn_system_setting = lv_button_create(ui->screen_settings);
    lv_obj_set_pos(ui->screen_settings_btn_system_setting, 23, 147);
    lv_obj_set_size(ui->screen_settings_btn_system_setting, 194, 45);
    ui->screen_settings_btn_system_setting_label = lv_label_create(ui->screen_settings_btn_system_setting);
    lv_label_set_text(ui->screen_settings_btn_system_setting_label, "" LV_SYMBOL_SETTINGS " 系统设置");
    lv_label_set_long_mode(ui->screen_settings_btn_system_setting_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_settings_btn_system_setting_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_settings_btn_system_setting, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_settings_btn_system_setting_label, LV_PCT(100));

    //Write style for screen_settings_btn_system_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_settings_btn_system_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_settings_btn_system_setting, lv_color_hex(0x91b0c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_settings_btn_system_setting, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_settings_btn_system_setting, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_settings_btn_system_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_settings_btn_system_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_settings_btn_system_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_btn_system_setting, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_btn_system_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_settings_btn_system_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_settings_btn_system_setting, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_settings_btn_system_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_settings_btn_system_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_btn_reset_setting
    ui->screen_settings_btn_reset_setting = lv_button_create(ui->screen_settings);
    lv_obj_set_pos(ui->screen_settings_btn_reset_setting, 23, 225);
    lv_obj_set_size(ui->screen_settings_btn_reset_setting, 194, 45);
    ui->screen_settings_btn_reset_setting_label = lv_label_create(ui->screen_settings_btn_reset_setting);
    lv_label_set_text(ui->screen_settings_btn_reset_setting_label, "" LV_SYMBOL_REFRESH " 恢复出厂设置");
    lv_label_set_long_mode(ui->screen_settings_btn_reset_setting_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_settings_btn_reset_setting_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_settings_btn_reset_setting, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_settings_btn_reset_setting_label, LV_PCT(100));

    //Write style for screen_settings_btn_reset_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_settings_btn_reset_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_settings_btn_reset_setting, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_settings_btn_reset_setting, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_settings_btn_reset_setting, lv_color_hex(0xfdb9c3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_settings_btn_reset_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_settings_btn_reset_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_settings_btn_reset_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_btn_reset_setting, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_btn_reset_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_settings_btn_reset_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_settings_btn_reset_setting, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_settings_btn_reset_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_settings_btn_reset_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_cont_1
    ui->screen_settings_cont_1 = lv_obj_create(ui->screen_settings);
    lv_obj_set_pos(ui->screen_settings_cont_1, 5, 127);
    lv_obj_set_size(ui->screen_settings_cont_1, 230, 66);
    lv_obj_set_scrollbar_mode(ui->screen_settings_cont_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_settings_cont_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_settings_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_settings_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_settings_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_settings_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_settings_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_cont_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_settings_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_settings_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_settings_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_label_1
    ui->screen_settings_label_1 = lv_label_create(ui->screen_settings_cont_1);
    lv_obj_set_pos(ui->screen_settings_label_1, 4, 7);
    lv_obj_set_size(ui->screen_settings_label_1, 220, 15);
    lv_label_set_text(ui->screen_settings_label_1, "" LV_SYMBOL_BELL " 恢复出厂设置成功 ");
    lv_label_set_long_mode(ui->screen_settings_label_1, LV_LABEL_LONG_WRAP);

    //Write style for screen_settings_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_settings_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_settings_label_1, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_settings_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_settings_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_settings_btn_1
    ui->screen_settings_btn_1 = lv_button_create(ui->screen_settings_cont_1);
    lv_obj_set_pos(ui->screen_settings_btn_1, 1, 34);
    lv_obj_set_size(ui->screen_settings_btn_1, 222, 20);
    ui->screen_settings_btn_1_label = lv_label_create(ui->screen_settings_btn_1);
    lv_label_set_text(ui->screen_settings_btn_1_label, "确定");
    lv_label_set_long_mode(ui->screen_settings_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_settings_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_settings_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_settings_btn_1_label, LV_PCT(100));

    //Write style for screen_settings_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_settings_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_settings_btn_1, lv_color_hex(0x26B08C), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_settings_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_settings_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_settings_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_settings_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_settings_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_settings_btn_1, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_settings_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_settings_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_settings.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_settings);

    //Init events for screen.
    events_init_screen_settings(ui);
}
