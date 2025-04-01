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
#include "lvgl_interface.h"


void setup_scr_screen_system_setting(lv_ui *ui)
{
    //Write codes screen_system_setting
    ui->screen_system_setting = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_system_setting, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_system_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_system_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_speaker_setting_title
    ui->screen_system_setting_label_speaker_setting_title = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_speaker_setting_title, 32, 30);
    lv_obj_set_size(ui->screen_system_setting_label_speaker_setting_title, 109, 18);
    lv_label_set_text(ui->screen_system_setting_label_speaker_setting_title, " " LV_SYMBOL_SETTINGS " 系统设置");
    lv_label_set_long_mode(ui->screen_system_setting_label_speaker_setting_title, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_speaker_setting_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_label_speaker_setting_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_speaker_setting_title, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_speaker_setting_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_speaker_setting_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_speaker_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_speak_volume
    ui->screen_system_setting_label_speak_volume = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_speak_volume, 6, 102);
    lv_obj_set_size(ui->screen_system_setting_label_speak_volume, 58, 14);
    lv_label_set_text(ui->screen_system_setting_label_speak_volume, "音量");
    lv_label_set_long_mode(ui->screen_system_setting_label_speak_volume, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_speak_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_label_speak_volume, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_speak_volume, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_speak_volume, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_speak_volume, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_slider_speak_volume
    ui->screen_system_setting_slider_speak_volume = lv_slider_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_slider_speak_volume, 73, 105);
    lv_obj_set_size(ui->screen_system_setting_slider_speak_volume, 160, 5);
    lv_slider_set_range(ui->screen_system_setting_slider_speak_volume, 0, 100);
    lv_slider_set_mode(ui->screen_system_setting_slider_speak_volume, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_system_setting_slider_speak_volume, 50, LV_ANIM_OFF);

    //Write style for screen_system_setting_slider_speak_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_speak_volume, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_speak_volume, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_speak_volume, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_speak_volume, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_slider_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_system_setting_slider_speak_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_system_setting_slider_speak_volume, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_speak_volume, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_speak_volume, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_speak_volume, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_speak_volume, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_system_setting_slider_speak_volume, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_speak_volume, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_speak_volume, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_speak_volume, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_speak_volume, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_speak_speed
    ui->screen_system_setting_label_speak_speed = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_speak_speed, 6, 145);
    lv_obj_set_size(ui->screen_system_setting_label_speak_speed, 58, 14);
    lv_label_set_text(ui->screen_system_setting_label_speak_speed, "语速");
    lv_label_set_long_mode(ui->screen_system_setting_label_speak_speed, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_speak_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_label_speak_speed, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_speak_speed, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_speak_speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_speak_speed, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_voice_type
    ui->screen_system_setting_label_voice_type = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_voice_type, 6, 188);
    lv_obj_set_size(ui->screen_system_setting_label_voice_type, 58, 14);
    lv_label_set_text(ui->screen_system_setting_label_voice_type, "音色");
    lv_label_set_long_mode(ui->screen_system_setting_label_voice_type, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_voice_type, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_system_setting_label_voice_type, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_voice_type, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_voice_type, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_ddlist_voice_type
    ui->screen_system_setting_ddlist_voice_type = lv_dropdown_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_ddlist_voice_type, 73, 182);
    lv_obj_set_size(ui->screen_system_setting_ddlist_voice_type, 160, 25);
    lv_dropdown_set_options(ui->screen_system_setting_ddlist_voice_type, "");

    //Write style for screen_system_setting_ddlist_voice_type, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_system_setting_ddlist_voice_type, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_ddlist_voice_type, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_ddlist_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_ddlist_voice_type, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_system_setting_ddlist_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_system_setting_ddlist_voice_type, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_system_setting_ddlist_voice_type, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_ddlist_voice_type, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_ddlist_voice_type, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_ddlist_voice_type, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_ddlist_voice_type, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_ddlist_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_ddlist_voice_type, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_ddlist_voice_type, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_ddlist_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked
    static lv_style_t style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked;
    ui_init_style(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked);

    lv_style_set_border_width(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_system_setting_ddlist_voice_type), &style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style for screen_system_setting_ddlist_voice_type, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_system_setting_ddlist_voice_type, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_ddlist_voice_type, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_ddlist_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_ddlist_voice_type, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_system_setting_ddlist_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_system_setting_ddlist_voice_type, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_system_setting_ddlist_voice_type, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_ddlist_voice_type, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_ddlist_voice_type, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_ddlist_voice_type, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_ddlist_voice_type, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_ddlist_voice_type, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_ddlist_voice_type, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_ddlist_voice_type, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_ddlist_voice_type, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default
    static lv_style_t style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default;
    ui_init_style(&style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default);

    lv_style_set_radius(&style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_system_setting_ddlist_voice_type), &style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_ddlist_persona
    ui->screen_system_setting_ddlist_persona = lv_dropdown_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_ddlist_persona, 73, 225);
    lv_obj_set_size(ui->screen_system_setting_ddlist_persona, 160, 25);
    lv_dropdown_set_options(ui->screen_system_setting_ddlist_persona, "");

    //Write style for screen_system_setting_ddlist_persona, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_system_setting_ddlist_persona, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_ddlist_persona, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_ddlist_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_ddlist_persona, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_system_setting_ddlist_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_system_setting_ddlist_persona, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_system_setting_ddlist_persona, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_ddlist_persona, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_ddlist_persona, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_ddlist_persona, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_ddlist_persona, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_ddlist_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_ddlist_persona, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_ddlist_persona, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_ddlist_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_system_setting_ddlist_persona_extra_list_selected_checked
    static lv_style_t style_screen_system_setting_ddlist_persona_extra_list_selected_checked;
    ui_init_style(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked);

    lv_style_set_border_width(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_screen_system_setting_ddlist_persona_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_system_setting_ddlist_persona), &style_screen_system_setting_ddlist_persona_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style for screen_system_setting_ddlist_persona, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_system_setting_ddlist_persona, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_ddlist_persona, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_ddlist_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_ddlist_persona, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_system_setting_ddlist_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_system_setting_ddlist_persona, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_system_setting_ddlist_persona, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_ddlist_persona, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_ddlist_persona, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_ddlist_persona, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_ddlist_persona, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_ddlist_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_ddlist_persona, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_ddlist_persona, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_ddlist_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default
    static lv_style_t style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default;
    ui_init_style(&style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default);

    lv_style_set_radius(&style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_system_setting_ddlist_persona), &style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_ddlist_environment_noise
    ui->screen_system_setting_ddlist_environment_noise = lv_dropdown_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_ddlist_environment_noise, 73, 268);
    lv_obj_set_size(ui->screen_system_setting_ddlist_environment_noise, 160, 25);
    lv_dropdown_set_options(ui->screen_system_setting_ddlist_environment_noise, "");

    //Write style for screen_system_setting_ddlist_environment_noise, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_system_setting_ddlist_environment_noise, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_system_setting_ddlist_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_system_setting_ddlist_environment_noise, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_system_setting_ddlist_environment_noise, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_ddlist_environment_noise, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_ddlist_environment_noise, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_ddlist_environment_noise, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_ddlist_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_ddlist_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_ddlist_environment_noise, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_ddlist_environment_noise, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_ddlist_environment_noise, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_ddlist_environment_noise, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_ddlist_environment_noise, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_ddlist_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked
    static lv_style_t style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked;
    ui_init_style(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked);

    lv_style_set_border_width(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_system_setting_ddlist_environment_noise), &style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style for screen_system_setting_ddlist_environment_noise, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_system_setting_ddlist_environment_noise, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_ddlist_environment_noise, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_ddlist_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_ddlist_environment_noise, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_system_setting_ddlist_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_system_setting_ddlist_environment_noise, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_system_setting_ddlist_environment_noise, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_ddlist_environment_noise, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_ddlist_environment_noise, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_ddlist_environment_noise, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_ddlist_environment_noise, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_ddlist_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_ddlist_environment_noise, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_ddlist_environment_noise, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_ddlist_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default
    static lv_style_t style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default;
    ui_init_style(&style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default);

    lv_style_set_radius(&style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_system_setting_ddlist_environment_noise), &style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_persona
    ui->screen_system_setting_label_persona = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_persona, 6, 231);
    lv_obj_set_size(ui->screen_system_setting_label_persona, 58, 14);
    lv_label_set_text(ui->screen_system_setting_label_persona, "人设");
    lv_label_set_long_mode(ui->screen_system_setting_label_persona, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_persona, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_label_persona, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_persona, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_persona, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_persona, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_persona, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_environment_noise
    ui->screen_system_setting_label_environment_noise = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_environment_noise, 6, 274);
    lv_obj_set_size(ui->screen_system_setting_label_environment_noise, 58, 14);
    lv_label_set_text(ui->screen_system_setting_label_environment_noise, "环境噪音");
    lv_label_set_long_mode(ui->screen_system_setting_label_environment_noise, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_environment_noise, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_label_environment_noise, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_environment_noise, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_environment_noise, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_environment_noise, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_environment_noise, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_slider_screen_brightness
    ui->screen_system_setting_slider_screen_brightness = lv_slider_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_slider_screen_brightness, 73, 63);
    lv_obj_set_size(ui->screen_system_setting_slider_screen_brightness, 160, 5);
    lv_slider_set_range(ui->screen_system_setting_slider_screen_brightness, 30, 100);
    lv_slider_set_mode(ui->screen_system_setting_slider_screen_brightness, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_system_setting_slider_screen_brightness, 80, LV_ANIM_OFF);

    //Write style for screen_system_setting_slider_screen_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_system_setting_slider_screen_brightness, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_screen_brightness, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_screen_brightness, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_screen_brightness, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_slider_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_system_setting_slider_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_system_setting_slider_screen_brightness, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_screen_brightness, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_screen_brightness, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_screen_brightness, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_screen_brightness, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_system_setting_slider_screen_brightness, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_screen_brightness, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_screen_brightness, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_screen_brightness, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_screen_brightness, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_label_screen_brightness
    ui->screen_system_setting_label_screen_brightness = lv_label_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_label_screen_brightness, 6, 58);
    lv_obj_set_size(ui->screen_system_setting_label_screen_brightness, 58, 14);
    lv_label_set_text(ui->screen_system_setting_label_screen_brightness, "屏幕亮度");
    lv_label_set_long_mode(ui->screen_system_setting_label_screen_brightness, LV_LABEL_LONG_WRAP);

    //Write style for screen_system_setting_label_screen_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_label_screen_brightness, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_label_screen_brightness, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_label_screen_brightness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_label_screen_brightness, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_system_setting_label_screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_btn_back
    ui->screen_system_setting_btn_back = lv_button_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_btn_back, 8, 30);
    lv_obj_set_size(ui->screen_system_setting_btn_back, 20, 20);
    ui->screen_system_setting_btn_back_label = lv_label_create(ui->screen_system_setting_btn_back);
    lv_label_set_text(ui->screen_system_setting_btn_back_label, "" LV_SYMBOL_LEFT " ");
    lv_label_set_long_mode(ui->screen_system_setting_btn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_system_setting_btn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_system_setting_btn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_system_setting_btn_back_label, LV_PCT(100));

    //Write style for screen_system_setting_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_system_setting_btn_back, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_system_setting_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_system_setting_btn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_system_setting_btn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_system_setting_btn_back, &lv_customer_font_Siyuan_Heiti_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_system_setting_btn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_system_setting_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_system_setting_slider_speak_speed
    ui->screen_system_setting_slider_speak_speed = lv_slider_create(ui->screen_system_setting);
    lv_obj_set_pos(ui->screen_system_setting_slider_speak_speed, 73, 149);
    lv_obj_set_size(ui->screen_system_setting_slider_speak_speed, 160, 5);
    lv_slider_set_range(ui->screen_system_setting_slider_speak_speed, 8, 20); // 0.8 ~ 2
    lv_slider_set_mode(ui->screen_system_setting_slider_speak_speed, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_system_setting_slider_speak_speed, 10, LV_ANIM_OFF);

    //Write style for screen_system_setting_slider_speak_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_speak_speed, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_speak_speed, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_speak_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_speak_speed, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_system_setting_slider_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_system_setting_slider_speak_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_system_setting_slider_speak_speed, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_speak_speed, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_speak_speed, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_speak_speed, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_speak_speed, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_system_setting_slider_speak_speed, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_system_setting_slider_speak_speed, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_system_setting_slider_speak_speed, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_system_setting_slider_speak_speed, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_system_setting_slider_speak_speed, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //The custom code of screen_system_setting.
    load_system_setting_data();

    //Update current screen layout.
    lv_obj_update_layout(ui->screen_system_setting);

    //Init events for screen.
    events_init_screen_system_setting(ui);
}
