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



void setup_scr_speaker_setting(lv_ui *ui)
{
    //Write codes speaker_setting
    ui->speaker_setting = lv_obj_create(NULL);
    lv_obj_set_size(ui->speaker_setting, 320, 480);
    lv_obj_set_scrollbar_mode(ui->speaker_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for speaker_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->speaker_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes speaker_setting_imgbtn_back
    ui->speaker_setting_imgbtn_back = lv_imgbtn_create(ui->speaker_setting);
    lv_obj_add_flag(ui->speaker_setting_imgbtn_back, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->speaker_setting_imgbtn_back, LV_IMGBTN_STATE_RELEASED, NULL, &_retrun_alpha_33x33, NULL);
    ui->speaker_setting_imgbtn_back_label = lv_label_create(ui->speaker_setting_imgbtn_back);
    lv_label_set_text(ui->speaker_setting_imgbtn_back_label, "");
    lv_label_set_long_mode(ui->speaker_setting_imgbtn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->speaker_setting_imgbtn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->speaker_setting_imgbtn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->speaker_setting_imgbtn_back, 0, 7);
    lv_obj_set_size(ui->speaker_setting_imgbtn_back, 33, 33);

    //Write style for speaker_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->speaker_setting_imgbtn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->speaker_setting_imgbtn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->speaker_setting_imgbtn_back, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for speaker_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->speaker_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->speaker_setting_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->speaker_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->speaker_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for speaker_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->speaker_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->speaker_setting_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->speaker_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->speaker_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for speaker_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->speaker_setting_imgbtn_back, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->speaker_setting_imgbtn_back, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes speaker_setting_label_title
    ui->speaker_setting_label_title = lv_label_create(ui->speaker_setting);
    lv_label_set_text(ui->speaker_setting_label_title, "语音设置");
    lv_label_set_long_mode(ui->speaker_setting_label_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->speaker_setting_label_title, 33, 15);
    lv_obj_set_size(ui->speaker_setting_label_title, 88, 24);

    //Write style for speaker_setting_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->speaker_setting_label_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_label_title, &lv_customer_font_Siyuan_Heiti_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_label_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->speaker_setting_label_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes speaker_setting_spinbox_1
    ui->speaker_setting_spinbox_1 = lv_spinbox_create(ui->speaker_setting);
    lv_obj_set_pos(ui->speaker_setting_spinbox_1, 139, 175);
    lv_obj_set_width(ui->speaker_setting_spinbox_1, 119);
    lv_obj_set_height(ui->speaker_setting_spinbox_1, 42);
    lv_spinbox_set_digit_format(ui->speaker_setting_spinbox_1, 3, 1);
    lv_spinbox_set_range(ui->speaker_setting_spinbox_1, -999, 999);
    lv_coord_t speaker_setting_spinbox_1_h = lv_obj_get_height(ui->speaker_setting_spinbox_1);
    ui->speaker_setting_spinbox_1_btn_plus = lv_btn_create(ui->speaker_setting);
    lv_obj_set_size(ui->speaker_setting_spinbox_1_btn_plus, speaker_setting_spinbox_1_h, speaker_setting_spinbox_1_h);
    lv_obj_align_to(ui->speaker_setting_spinbox_1_btn_plus, ui->speaker_setting_spinbox_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->speaker_setting_spinbox_1_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->speaker_setting_spinbox_1_btn_plus, lv_speaker_setting_spinbox_1_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->speaker_setting_spinbox_1_btn_minus = lv_btn_create(ui->speaker_setting);
    lv_obj_set_size(ui->speaker_setting_spinbox_1_btn_minus, speaker_setting_spinbox_1_h, speaker_setting_spinbox_1_h);
    lv_obj_align_to(ui->speaker_setting_spinbox_1_btn_minus, ui->speaker_setting_spinbox_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->speaker_setting_spinbox_1_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->speaker_setting_spinbox_1_btn_minus, lv_speaker_setting_spinbox_1_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->speaker_setting_spinbox_1, 139, 175);

    //Write style for speaker_setting_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->speaker_setting_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->speaker_setting_spinbox_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->speaker_setting_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->speaker_setting_spinbox_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->speaker_setting_spinbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->speaker_setting_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->speaker_setting_spinbox_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_spinbox_1, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->speaker_setting_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_spinbox_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for speaker_setting_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->speaker_setting_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_spinbox_1, &lv_font_montserratMedium_16, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting_spinbox_1, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_speaker_setting_spinbox_1_extra_btns_main_default
    static lv_style_t style_speaker_setting_spinbox_1_extra_btns_main_default;
    ui_init_style(&style_speaker_setting_spinbox_1_extra_btns_main_default);

    lv_style_set_text_color(&style_speaker_setting_spinbox_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_speaker_setting_spinbox_1_extra_btns_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_speaker_setting_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_speaker_setting_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_speaker_setting_spinbox_1_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_speaker_setting_spinbox_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_speaker_setting_spinbox_1_extra_btns_main_default, 0);
    lv_style_set_radius(&style_speaker_setting_spinbox_1_extra_btns_main_default, 7);
    lv_style_set_shadow_width(&style_speaker_setting_spinbox_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->speaker_setting_spinbox_1_btn_plus, &style_speaker_setting_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->speaker_setting_spinbox_1_btn_minus, &style_speaker_setting_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes speaker_setting_ddlist_1
    ui->speaker_setting_ddlist_1 = lv_dropdown_create(ui->speaker_setting);
    lv_obj_set_pos(ui->speaker_setting_ddlist_1, 92, 260);
    lv_obj_set_size(ui->speaker_setting_ddlist_1, 213, 33);

    //Write style for speaker_setting_ddlist_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->speaker_setting_ddlist_1, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_ddlist_1, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->speaker_setting_ddlist_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->speaker_setting_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->speaker_setting_ddlist_1, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->speaker_setting_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_ddlist_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_ddlist_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting_ddlist_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting_ddlist_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_speaker_setting_ddlist_1_extra_list_selected_checked
    static lv_style_t style_speaker_setting_ddlist_1_extra_list_selected_checked;
    ui_init_style(&style_speaker_setting_ddlist_1_extra_list_selected_checked);

    lv_style_set_border_width(&style_speaker_setting_ddlist_1_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_speaker_setting_ddlist_1_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_speaker_setting_ddlist_1_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_speaker_setting_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_speaker_setting_ddlist_1_extra_list_selected_checked, 4);
    lv_style_set_bg_opa(&style_speaker_setting_ddlist_1_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_speaker_setting_ddlist_1_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_speaker_setting_ddlist_1_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->speaker_setting_ddlist_1), &style_speaker_setting_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_speaker_setting_ddlist_1_extra_list_main_default
    static lv_style_t style_speaker_setting_ddlist_1_extra_list_main_default;
    ui_init_style(&style_speaker_setting_ddlist_1_extra_list_main_default);

    lv_style_set_max_height(&style_speaker_setting_ddlist_1_extra_list_main_default, 90);
    lv_style_set_text_color(&style_speaker_setting_ddlist_1_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_speaker_setting_ddlist_1_extra_list_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_speaker_setting_ddlist_1_extra_list_main_default, 255);
    lv_style_set_border_width(&style_speaker_setting_ddlist_1_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_speaker_setting_ddlist_1_extra_list_main_default, 255);
    lv_style_set_border_color(&style_speaker_setting_ddlist_1_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_speaker_setting_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_speaker_setting_ddlist_1_extra_list_main_default, 4);
    lv_style_set_bg_opa(&style_speaker_setting_ddlist_1_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_speaker_setting_ddlist_1_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_speaker_setting_ddlist_1_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->speaker_setting_ddlist_1), &style_speaker_setting_ddlist_1_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_speaker_setting_ddlist_1_extra_list_scrollbar_default
    static lv_style_t style_speaker_setting_ddlist_1_extra_list_scrollbar_default;
    ui_init_style(&style_speaker_setting_ddlist_1_extra_list_scrollbar_default);

    lv_style_set_radius(&style_speaker_setting_ddlist_1_extra_list_scrollbar_default, 4);
    lv_style_set_bg_opa(&style_speaker_setting_ddlist_1_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_speaker_setting_ddlist_1_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_speaker_setting_ddlist_1_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->speaker_setting_ddlist_1), &style_speaker_setting_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes speaker_setting_ddlist_2
    ui->speaker_setting_ddlist_2 = lv_dropdown_create(ui->speaker_setting);
    lv_obj_set_pos(ui->speaker_setting_ddlist_2, 92, 336);
    lv_obj_set_size(ui->speaker_setting_ddlist_2, 213, 33);

    //Write style for speaker_setting_ddlist_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->speaker_setting_ddlist_2, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_ddlist_2, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_ddlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->speaker_setting_ddlist_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->speaker_setting_ddlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->speaker_setting_ddlist_2, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->speaker_setting_ddlist_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_ddlist_2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_ddlist_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_ddlist_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_ddlist_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_ddlist_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting_ddlist_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting_ddlist_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_ddlist_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_speaker_setting_ddlist_2_extra_list_selected_checked
    static lv_style_t style_speaker_setting_ddlist_2_extra_list_selected_checked;
    ui_init_style(&style_speaker_setting_ddlist_2_extra_list_selected_checked);

    lv_style_set_border_width(&style_speaker_setting_ddlist_2_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_speaker_setting_ddlist_2_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_speaker_setting_ddlist_2_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_speaker_setting_ddlist_2_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_speaker_setting_ddlist_2_extra_list_selected_checked, 4);
    lv_style_set_bg_opa(&style_speaker_setting_ddlist_2_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_speaker_setting_ddlist_2_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_speaker_setting_ddlist_2_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->speaker_setting_ddlist_2), &style_speaker_setting_ddlist_2_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_speaker_setting_ddlist_2_extra_list_main_default
    static lv_style_t style_speaker_setting_ddlist_2_extra_list_main_default;
    ui_init_style(&style_speaker_setting_ddlist_2_extra_list_main_default);

    lv_style_set_max_height(&style_speaker_setting_ddlist_2_extra_list_main_default, 90);
    lv_style_set_text_color(&style_speaker_setting_ddlist_2_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_speaker_setting_ddlist_2_extra_list_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_speaker_setting_ddlist_2_extra_list_main_default, 255);
    lv_style_set_border_width(&style_speaker_setting_ddlist_2_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_speaker_setting_ddlist_2_extra_list_main_default, 255);
    lv_style_set_border_color(&style_speaker_setting_ddlist_2_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_speaker_setting_ddlist_2_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_speaker_setting_ddlist_2_extra_list_main_default, 4);
    lv_style_set_bg_opa(&style_speaker_setting_ddlist_2_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_speaker_setting_ddlist_2_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_speaker_setting_ddlist_2_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->speaker_setting_ddlist_2), &style_speaker_setting_ddlist_2_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_speaker_setting_ddlist_2_extra_list_scrollbar_default
    static lv_style_t style_speaker_setting_ddlist_2_extra_list_scrollbar_default;
    ui_init_style(&style_speaker_setting_ddlist_2_extra_list_scrollbar_default);

    lv_style_set_radius(&style_speaker_setting_ddlist_2_extra_list_scrollbar_default, 4);
    lv_style_set_bg_opa(&style_speaker_setting_ddlist_2_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_speaker_setting_ddlist_2_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_speaker_setting_ddlist_2_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->speaker_setting_ddlist_2), &style_speaker_setting_ddlist_2_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes speaker_setting_bar_1
    ui->speaker_setting_bar_1 = lv_bar_create(ui->speaker_setting);
    lv_obj_set_style_anim_time(ui->speaker_setting_bar_1, 1000, 0);
    lv_bar_set_mode(ui->speaker_setting_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->speaker_setting_bar_1, 0, 100);
    lv_bar_set_value(ui->speaker_setting_bar_1, 80, LV_ANIM_OFF);
    lv_obj_set_pos(ui->speaker_setting_bar_1, 92, 120);
    lv_obj_set_size(ui->speaker_setting_bar_1, 213, 12);

    //Write style for speaker_setting_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->speaker_setting_bar_1, 93, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting_bar_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting_bar_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_bar_1, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for speaker_setting_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->speaker_setting_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->speaker_setting_bar_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->speaker_setting_bar_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_bar_1, 15, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes speaker_setting_label_1
    ui->speaker_setting_label_1 = lv_label_create(ui->speaker_setting);
    lv_label_set_text(ui->speaker_setting_label_1, "音量");
    lv_label_set_long_mode(ui->speaker_setting_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->speaker_setting_label_1, 12, 113);
    lv_obj_set_size(ui->speaker_setting_label_1, 53, 25);

    //Write style for speaker_setting_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->speaker_setting_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_label_1, &lv_customer_font_Siyuan_yuanti_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->speaker_setting_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes speaker_setting_label_2
    ui->speaker_setting_label_2 = lv_label_create(ui->speaker_setting);
    lv_label_set_text(ui->speaker_setting_label_2, "语速");
    lv_label_set_long_mode(ui->speaker_setting_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->speaker_setting_label_2, 12, 183);
    lv_obj_set_size(ui->speaker_setting_label_2, 53, 25);

    //Write style for speaker_setting_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->speaker_setting_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_label_2, &lv_customer_font_Siyuan_yuanti_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->speaker_setting_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes speaker_setting_label_3
    ui->speaker_setting_label_3 = lv_label_create(ui->speaker_setting);
    lv_label_set_text(ui->speaker_setting_label_3, "情绪");
    lv_label_set_long_mode(ui->speaker_setting_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->speaker_setting_label_3, 12, 340);
    lv_obj_set_size(ui->speaker_setting_label_3, 53, 25);

    //Write style for speaker_setting_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->speaker_setting_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_label_3, &lv_customer_font_Siyuan_yuanti_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->speaker_setting_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes speaker_setting_label_4
    ui->speaker_setting_label_4 = lv_label_create(ui->speaker_setting);
    lv_label_set_text(ui->speaker_setting_label_4, "音色");
    lv_label_set_long_mode(ui->speaker_setting_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->speaker_setting_label_4, 12, 264);
    lv_obj_set_size(ui->speaker_setting_label_4, 53, 25);

    //Write style for speaker_setting_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->speaker_setting_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->speaker_setting_label_4, &lv_customer_font_Siyuan_yuanti_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->speaker_setting_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->speaker_setting_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->speaker_setting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of speaker_setting.


    //Update current screen layout.
    lv_obj_update_layout(ui->speaker_setting);

    //Init events for screen.
    events_init_speaker_setting(ui);
}
