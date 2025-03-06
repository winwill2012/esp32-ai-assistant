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



void setup_scr_settings(lv_ui *ui)
{
    //Write codes settings
    ui->settings = lv_obj_create(NULL);
    lv_obj_set_size(ui->settings, 240, 320);
    lv_obj_set_scrollbar_mode(ui->settings, LV_SCROLLBAR_MODE_OFF);

    //Write style for settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_label_1
    ui->settings_label_1 = lv_label_create(ui->settings);
    lv_label_set_text(ui->settings_label_1, "Settings");
    lv_label_set_long_mode(ui->settings_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->settings_label_1, 77, 5);
    lv_obj_set_size(ui->settings_label_1, 85, 17);

    //Write style for settings_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_network
    ui->settings_network = lv_dropdown_create(ui->settings);
    lv_dropdown_set_options(ui->settings_network, "list3");
    lv_obj_set_pos(ui->settings_network, 98, 45);
    lv_obj_set_size(ui->settings_network, 137, 36);

    //Write style for settings_network, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->settings_network, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_network, &AlibabaPuHuiTi_Bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_network, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->settings_network, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->settings_network, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->settings_network, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->settings_network, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_network, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_network, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_network, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_network, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_network, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_network, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_network, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_network, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_settings_network_extra_list_selected_checked
    static lv_style_t style_settings_network_extra_list_selected_checked;
    ui_init_style(&style_settings_network_extra_list_selected_checked);

    lv_style_set_border_width(&style_settings_network_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_settings_network_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_settings_network_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_settings_network_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_settings_network_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_settings_network_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_settings_network_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_settings_network_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->settings_network), &style_settings_network_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_settings_network_extra_list_main_default
    static lv_style_t style_settings_network_extra_list_main_default;
    ui_init_style(&style_settings_network_extra_list_main_default);

    lv_style_set_max_height(&style_settings_network_extra_list_main_default, 90);
    lv_style_set_text_color(&style_settings_network_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_settings_network_extra_list_main_default, &AlibabaPuHuiTi_Bold_14);
    lv_style_set_text_opa(&style_settings_network_extra_list_main_default, 255);
    lv_style_set_border_width(&style_settings_network_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_settings_network_extra_list_main_default, 255);
    lv_style_set_border_color(&style_settings_network_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_settings_network_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_settings_network_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_settings_network_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_settings_network_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_settings_network_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->settings_network), &style_settings_network_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_settings_network_extra_list_scrollbar_default
    static lv_style_t style_settings_network_extra_list_scrollbar_default;
    ui_init_style(&style_settings_network_extra_list_scrollbar_default);

    lv_style_set_radius(&style_settings_network_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_settings_network_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_settings_network_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_settings_network_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->settings_network), &style_settings_network_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes settings_label_2
    ui->settings_label_2 = lv_label_create(ui->settings);
    lv_label_set_text(ui->settings_label_2, "Network");
    lv_label_set_long_mode(ui->settings_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->settings_label_2, 1, 51);
    lv_obj_set_size(ui->settings_label_2, 85, 20);

    //Write style for settings_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_label_3
    ui->settings_label_3 = lv_label_create(ui->settings);
    lv_label_set_text(ui->settings_label_3, "Volume");
    lv_label_set_long_mode(ui->settings_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->settings_label_3, 1, 104);
    lv_obj_set_size(ui->settings_label_3, 85, 20);

    //Write style for settings_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_label_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_volume
    ui->settings_volume = lv_slider_create(ui->settings);
    lv_slider_set_range(ui->settings_volume, 0, 100);
    lv_slider_set_mode(ui->settings_volume, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->settings_volume, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->settings_volume, 101, 108);
    lv_obj_set_size(ui->settings_volume, 125, 7);

    //Write style for settings_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_volume, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_volume, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_volume, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_volume, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->settings_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for settings_volume, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_volume, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_volume, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_volume, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_volume, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for settings_volume, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_volume, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_volume, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_volume, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_volume, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes settings_label_4
    ui->settings_label_4 = lv_label_create(ui->settings);
    lv_label_set_text(ui->settings_label_4, "VoiceType");
    lv_label_set_long_mode(ui->settings_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->settings_label_4, 1, 157);
    lv_obj_set_size(ui->settings_label_4, 85, 20);

    //Write style for settings_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_label_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_voiceType
    ui->settings_voiceType = lv_dropdown_create(ui->settings);
    lv_dropdown_set_options(ui->settings_voiceType, "BV001_streaming\nBV002_streaming\nBV700_streaming\nBV007_streaming");
    lv_obj_set_pos(ui->settings_voiceType, 99, 149);
    lv_obj_set_size(ui->settings_voiceType, 135, 30);

    //Write style for settings_voiceType, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->settings_voiceType, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_voiceType, &AlibabaPuHuiTi_Bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_voiceType, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->settings_voiceType, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->settings_voiceType, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->settings_voiceType, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->settings_voiceType, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_voiceType, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_voiceType, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_voiceType, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_voiceType, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_voiceType, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_voiceType, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_voiceType, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_voiceType, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_settings_voiceType_extra_list_selected_checked
    static lv_style_t style_settings_voiceType_extra_list_selected_checked;
    ui_init_style(&style_settings_voiceType_extra_list_selected_checked);

    lv_style_set_border_width(&style_settings_voiceType_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_settings_voiceType_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_settings_voiceType_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_settings_voiceType_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_settings_voiceType_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_settings_voiceType_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_settings_voiceType_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_settings_voiceType_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->settings_voiceType), &style_settings_voiceType_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_settings_voiceType_extra_list_main_default
    static lv_style_t style_settings_voiceType_extra_list_main_default;
    ui_init_style(&style_settings_voiceType_extra_list_main_default);

    lv_style_set_max_height(&style_settings_voiceType_extra_list_main_default, 90);
    lv_style_set_text_color(&style_settings_voiceType_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_settings_voiceType_extra_list_main_default, &AlibabaPuHuiTi_Bold_14);
    lv_style_set_text_opa(&style_settings_voiceType_extra_list_main_default, 255);
    lv_style_set_border_width(&style_settings_voiceType_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_settings_voiceType_extra_list_main_default, 255);
    lv_style_set_border_color(&style_settings_voiceType_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_settings_voiceType_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_settings_voiceType_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_settings_voiceType_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_settings_voiceType_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_settings_voiceType_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->settings_voiceType), &style_settings_voiceType_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_settings_voiceType_extra_list_scrollbar_default
    static lv_style_t style_settings_voiceType_extra_list_scrollbar_default;
    ui_init_style(&style_settings_voiceType_extra_list_scrollbar_default);

    lv_style_set_radius(&style_settings_voiceType_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_settings_voiceType_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_settings_voiceType_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_settings_voiceType_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->settings_voiceType), &style_settings_voiceType_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes settings_label_5
    ui->settings_label_5 = lv_label_create(ui->settings);
    lv_label_set_text(ui->settings_label_5, "Speed");
    lv_label_set_long_mode(ui->settings_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->settings_label_5, 1, 210);
    lv_obj_set_size(ui->settings_label_5, 85, 20);

    //Write style for settings_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_label_5, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_speed
    ui->settings_speed = lv_slider_create(ui->settings);
    lv_slider_set_range(ui->settings_speed, 0, 100);
    lv_slider_set_mode(ui->settings_speed, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->settings_speed, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->settings_speed, 103, 215);
    lv_obj_set_size(ui->settings_speed, 123, 6);

    //Write style for settings_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_speed, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_speed, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_speed, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->settings_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for settings_speed, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_speed, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_speed, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_speed, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_speed, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for settings_speed, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_speed, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_speed, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_speed, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_speed, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes settings_setting_confirm
    ui->settings_setting_confirm = lv_btn_create(ui->settings);
    ui->settings_setting_confirm_label = lv_label_create(ui->settings_setting_confirm);
    lv_label_set_text(ui->settings_setting_confirm_label, "OK");
    lv_label_set_long_mode(ui->settings_setting_confirm_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->settings_setting_confirm_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->settings_setting_confirm, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->settings_setting_confirm_label, LV_PCT(100));
    lv_obj_set_pos(ui->settings_setting_confirm, 87, 269);
    lv_obj_set_size(ui->settings_setting_confirm, 65, 32);

    //Write style for settings_setting_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_setting_confirm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_setting_confirm, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_setting_confirm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->settings_setting_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_setting_confirm, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_setting_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_setting_confirm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_setting_confirm, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_setting_confirm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_setting_confirm, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of settings.


    //Update current screen layout.
    lv_obj_update_layout(ui->settings);

    //Init events for screen.
    events_init_settings(ui);
}
