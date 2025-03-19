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
#include "lvgl_interface.h"
#include "custom.h"



void setup_scr_system_setting(lv_ui *ui)
{
    //Write codes system_setting
    ui->system_setting = lv_obj_create(NULL);
    lv_obj_set_size(ui->system_setting, 320, 480);
    lv_obj_set_scrollbar_mode(ui->system_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for system_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_imgbtn_back
    ui->system_setting_imgbtn_back = lv_imgbtn_create(ui->system_setting);
    lv_obj_add_flag(ui->system_setting_imgbtn_back, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->system_setting_imgbtn_back, LV_IMGBTN_STATE_RELEASED, NULL, &_retrun_alpha_30x30, NULL);
    ui->system_setting_imgbtn_back_label = lv_label_create(ui->system_setting_imgbtn_back);
    lv_label_set_text(ui->system_setting_imgbtn_back_label, "");
    lv_label_set_long_mode(ui->system_setting_imgbtn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_setting_imgbtn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_setting_imgbtn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->system_setting_imgbtn_back, 0, 40);
    lv_obj_set_size(ui->system_setting_imgbtn_back, 30, 30);

    //Write style for system_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_setting_imgbtn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_imgbtn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->system_setting_imgbtn_back, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for system_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->system_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->system_setting_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->system_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->system_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for system_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->system_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->system_setting_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->system_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->system_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for system_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->system_setting_imgbtn_back, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->system_setting_imgbtn_back, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes system_setting_label_title
    ui->system_setting_label_title = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_title, "" LV_SYMBOL_SETTINGS " 系统设置  ");
    lv_label_set_long_mode(ui->system_setting_label_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_title, 33, 46);
    lv_obj_set_size(ui->system_setting_label_title, 97, 17);

    //Write style for system_setting_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_title, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_title, &lv_customer_font_Siyuan_Heiti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_speed
    ui->system_setting_speed = lv_spinbox_create(ui->system_setting);
    lv_obj_set_pos(ui->system_setting_speed, 176, 167);
    lv_obj_set_width(ui->system_setting_speed, 86);
    lv_obj_set_height(ui->system_setting_speed, 42);
    lv_spinbox_set_digit_format(ui->system_setting_speed, 2, 1);
    lv_spinbox_set_range(ui->system_setting_speed, -99, 99);
    lv_coord_t system_setting_speed_h = lv_obj_get_height(ui->system_setting_speed);
    ui->system_setting_speed_btn_plus = lv_btn_create(ui->system_setting);
    lv_obj_set_size(ui->system_setting_speed_btn_plus, system_setting_speed_h, system_setting_speed_h);
    lv_obj_align_to(ui->system_setting_speed_btn_plus, ui->system_setting_speed, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->system_setting_speed_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->system_setting_speed_btn_plus, lv_system_setting_speed_increment_event_cb, LV_EVENT_ALL,
                        NULL);
    ui->system_setting_speed_btn_minus = lv_btn_create(ui->system_setting);
    lv_obj_set_size(ui->system_setting_speed_btn_minus, system_setting_speed_h, system_setting_speed_h);
    lv_obj_align_to(ui->system_setting_speed_btn_minus, ui->system_setting_speed, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->system_setting_speed_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->system_setting_speed_btn_minus, lv_system_setting_speed_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->system_setting_speed, 176, 167);

    //Write style for system_setting_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting_speed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_speed, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_setting_speed, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_setting_speed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_setting_speed, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_setting_speed, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_speed, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_speed, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_speed, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_speed, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_speed, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_speed, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_speed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_speed, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_speed, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_speed, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for system_setting_speed, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_setting_speed, lv_color_hex(0xffffff), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_speed, &lv_font_montserratMedium_16, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_speed, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_speed, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_speed, lv_color_hex(0x2195f6), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_speed, LV_GRAD_DIR_NONE, LV_PART_CURSOR | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_speed_extra_btns_main_default
    static lv_style_t style_system_setting_speed_extra_btns_main_default;
    ui_init_style(&style_system_setting_speed_extra_btns_main_default);

    lv_style_set_text_color(&style_system_setting_speed_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_system_setting_speed_extra_btns_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_system_setting_speed_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_system_setting_speed_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_system_setting_speed_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_system_setting_speed_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_system_setting_speed_extra_btns_main_default, 0);
    lv_style_set_radius(&style_system_setting_speed_extra_btns_main_default, 7);
    lv_style_set_shadow_width(&style_system_setting_speed_extra_btns_main_default, 0);
    lv_obj_add_style(ui->system_setting_speed_btn_plus, &style_system_setting_speed_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->system_setting_speed_btn_minus, &style_system_setting_speed_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_voice_type
    ui->system_setting_voice_type = lv_dropdown_create(ui->system_setting);
    lv_obj_set_pos(ui->system_setting_voice_type, 129, 236);
    lv_obj_set_size(ui->system_setting_voice_type, 180, 33);

    //Write style for system_setting_voice_type, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_setting_voice_type, lv_color_hex(0x0D3055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_voice_type, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *voice_type_list = lv_dropdown_get_list(ui->system_setting_voice_type);
    lv_obj_set_style_max_height(voice_type_list, 350, 0);
    lv_obj_set_style_text_font(voice_type_list, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_voice_type, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_setting_voice_type, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_setting_voice_type, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_setting_voice_type, lv_color_hex(0xe1e6ee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_setting_voice_type, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_voice_type, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_voice_type, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_voice_type, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_voice_type, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_voice_type, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_voice_type, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_voice_type, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_voice_type, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_system_setting_voice_type_extra_list_selected_checked
    static lv_style_t style_system_setting_voice_type_extra_list_selected_checked;
    ui_init_style(&style_system_setting_voice_type_extra_list_selected_checked);

    lv_style_set_border_width(&style_system_setting_voice_type_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_system_setting_voice_type_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_system_setting_voice_type_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_setting_voice_type_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_setting_voice_type_extra_list_selected_checked, 4);
    lv_style_set_bg_opa(&style_system_setting_voice_type_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_system_setting_voice_type_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_system_setting_voice_type_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_voice_type), &style_system_setting_voice_type_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_voice_type_extra_list_main_default
    static lv_style_t style_system_setting_voice_type_extra_list_main_default;
    ui_init_style(&style_system_setting_voice_type_extra_list_main_default);

    lv_style_set_max_height(&style_system_setting_voice_type_extra_list_main_default, 90);
    lv_style_set_text_color(&style_system_setting_voice_type_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_system_setting_voice_type_extra_list_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_system_setting_voice_type_extra_list_main_default, 255);
    lv_style_set_border_width(&style_system_setting_voice_type_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_system_setting_voice_type_extra_list_main_default, 255);
    lv_style_set_border_color(&style_system_setting_voice_type_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_setting_voice_type_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_setting_voice_type_extra_list_main_default, 4);
    lv_style_set_bg_opa(&style_system_setting_voice_type_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_system_setting_voice_type_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_system_setting_voice_type_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_voice_type), &style_system_setting_voice_type_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_voice_type_extra_list_scrollbar_default
    static lv_style_t style_system_setting_voice_type_extra_list_scrollbar_default;
    ui_init_style(&style_system_setting_voice_type_extra_list_scrollbar_default);

    lv_style_set_radius(&style_system_setting_voice_type_extra_list_scrollbar_default, 4);
    lv_style_set_bg_opa(&style_system_setting_voice_type_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_system_setting_voice_type_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_system_setting_voice_type_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_voice_type), &style_system_setting_voice_type_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes system_setting_persona
    ui->system_setting_persona = lv_dropdown_create(ui->system_setting);
    lv_obj_set_pos(ui->system_setting_persona, 129, 296);
    lv_obj_set_size(ui->system_setting_persona, 180, 33);

    //Write style for system_setting_persona, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_setting_persona, lv_color_hex(0x0D3055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_persona, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *persona_list = lv_dropdown_get_list(ui->system_setting_persona);
    lv_obj_set_style_max_height(persona_list, 350, 0);
    lv_obj_set_style_text_font(persona_list, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_persona, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_setting_persona, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_setting_persona, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_setting_persona, lv_color_hex(0xe1e6ee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_setting_persona, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_persona, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_persona, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_persona, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_persona, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_persona, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_persona, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_persona, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_persona, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_system_setting_persona_extra_list_selected_checked
    static lv_style_t style_system_setting_persona_extra_list_selected_checked;
    ui_init_style(&style_system_setting_persona_extra_list_selected_checked);

    lv_style_set_border_width(&style_system_setting_persona_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_system_setting_persona_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_system_setting_persona_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_setting_persona_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_setting_persona_extra_list_selected_checked, 4);
    lv_style_set_bg_opa(&style_system_setting_persona_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_system_setting_persona_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_system_setting_persona_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_persona), &style_system_setting_persona_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_persona_extra_list_main_default
    static lv_style_t style_system_setting_persona_extra_list_main_default;
    ui_init_style(&style_system_setting_persona_extra_list_main_default);

    lv_style_set_max_height(&style_system_setting_persona_extra_list_main_default, 90);
    lv_style_set_text_color(&style_system_setting_persona_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_system_setting_persona_extra_list_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_system_setting_persona_extra_list_main_default, 255);
    lv_style_set_border_width(&style_system_setting_persona_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_system_setting_persona_extra_list_main_default, 255);
    lv_style_set_border_color(&style_system_setting_persona_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_setting_persona_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_setting_persona_extra_list_main_default, 4);
    lv_style_set_bg_opa(&style_system_setting_persona_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_system_setting_persona_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_system_setting_persona_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_persona), &style_system_setting_persona_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_persona_extra_list_scrollbar_default
    static lv_style_t style_system_setting_persona_extra_list_scrollbar_default;
    ui_init_style(&style_system_setting_persona_extra_list_scrollbar_default);

    lv_style_set_radius(&style_system_setting_persona_extra_list_scrollbar_default, 4);
    lv_style_set_bg_opa(&style_system_setting_persona_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_system_setting_persona_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_system_setting_persona_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_persona), &style_system_setting_persona_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes system_setting_slider_volume
    ui->system_setting_slider_volume = lv_slider_create(ui->system_setting);
    lv_obj_set_style_anim_time(ui->system_setting_slider_volume, 1000, 0);
    lv_bar_set_mode(ui->system_setting_slider_volume, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->system_setting_slider_volume, 0, 100);
    lv_bar_set_value(ui->system_setting_slider_volume, 80, LV_ANIM_ON);
    lv_obj_set_pos(ui->system_setting_slider_volume, 129, 128);
    lv_obj_set_size(ui->system_setting_slider_volume, 180, 12);

    //Write style for system_setting_slider_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting_slider_volume, 93, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_slider_volume, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_slider_volume, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_slider_volume, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_slider_volume, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for system_setting_slider_volume, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting_slider_volume, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_slider_volume, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_slider_volume, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_slider_volume, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Write codes system_setting_label_1
    ui->system_setting_label_1 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_1, "音       量");
    lv_label_set_long_mode(ui->system_setting_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_1, 9, 121);
    lv_obj_set_size(ui->system_setting_label_1, 95, 25);

    //Write style for system_setting_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_1, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_1, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_label_2
    ui->system_setting_label_2 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_2, "语       速");
    lv_label_set_long_mode(ui->system_setting_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_2, 9, 175);
    lv_obj_set_size(ui->system_setting_label_2, 95, 25);

    //Write style for system_setting_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_2, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_2, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_label_3
    ui->system_setting_label_3 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_3, "性格特点");
    lv_label_set_long_mode(ui->system_setting_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_3, 9, 300);
    lv_obj_set_size(ui->system_setting_label_3, 95, 24);

    //Write style for system_setting_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_3, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_3, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_label_4
    ui->system_setting_label_4 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_4, "声音音色");
    lv_label_set_long_mode(ui->system_setting_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_4, 9, 240);
    lv_obj_set_size(ui->system_setting_label_4, 95, 25);

    //Write style for system_setting_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_4, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_4, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_label_5
    ui->system_setting_label_5 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_5, "环境噪音");
    lv_label_set_long_mode(ui->system_setting_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_5, 9, 360);
    lv_obj_set_size(ui->system_setting_label_5, 95, 24);

    //Write style for system_setting_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_5, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_5, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_label_6
    ui->system_setting_label_6 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_6, "说话停顿(s)\n");
    lv_label_set_long_mode(ui->system_setting_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_6, 9, 425);
    lv_obj_set_size(ui->system_setting_label_6, 95, 24);

    //Write style for system_setting_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_6, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_6, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_backgroud_noise
    ui->system_setting_environment_noise = lv_dropdown_create(ui->system_setting);
    lv_dropdown_set_options(ui->system_setting_environment_noise, "安静\n正常\n嘈杂");
    lv_obj_set_pos(ui->system_setting_environment_noise, 129, 356);
    lv_obj_set_size(ui->system_setting_environment_noise, 180, 33);

    //Write style for system_setting_backgroud_noise, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_setting_environment_noise, lv_color_hex(0x0D3055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_environment_noise, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *environment_noise_list = lv_dropdown_get_list(ui->system_setting_environment_noise);
    lv_obj_set_style_max_height(environment_noise_list, 350, 0);
    lv_obj_set_style_text_font(environment_noise_list, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_environment_noise, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_setting_environment_noise, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_setting_environment_noise, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_setting_environment_noise, lv_color_hex(0xe1e6ee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_setting_environment_noise, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_environment_noise, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_environment_noise, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_environment_noise, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_environment_noise, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_environment_noise, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_environment_noise, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_environment_noise, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_environment_noise, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_system_setting_backgroud_noise_extra_list_selected_checked
    static lv_style_t style_system_setting_backgroud_noise_extra_list_selected_checked;
    ui_init_style(&style_system_setting_backgroud_noise_extra_list_selected_checked);

    lv_style_set_border_width(&style_system_setting_backgroud_noise_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_system_setting_backgroud_noise_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_system_setting_backgroud_noise_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_setting_backgroud_noise_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_setting_backgroud_noise_extra_list_selected_checked, 4);
    lv_style_set_bg_opa(&style_system_setting_backgroud_noise_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_system_setting_backgroud_noise_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_system_setting_backgroud_noise_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_environment_noise), &style_system_setting_backgroud_noise_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_backgroud_noise_extra_list_main_default
    static lv_style_t style_system_setting_backgroud_noise_extra_list_main_default;
    ui_init_style(&style_system_setting_backgroud_noise_extra_list_main_default);

    lv_style_set_max_height(&style_system_setting_backgroud_noise_extra_list_main_default, 90);
    lv_style_set_text_color(&style_system_setting_backgroud_noise_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_system_setting_backgroud_noise_extra_list_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_system_setting_backgroud_noise_extra_list_main_default, 255);
    lv_style_set_border_width(&style_system_setting_backgroud_noise_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_system_setting_backgroud_noise_extra_list_main_default, 255);
    lv_style_set_border_color(&style_system_setting_backgroud_noise_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_setting_backgroud_noise_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_setting_backgroud_noise_extra_list_main_default, 4);
    lv_style_set_bg_opa(&style_system_setting_backgroud_noise_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_system_setting_backgroud_noise_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_system_setting_backgroud_noise_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_environment_noise), &style_system_setting_backgroud_noise_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_backgroud_noise_extra_list_scrollbar_default
    static lv_style_t style_system_setting_backgroud_noise_extra_list_scrollbar_default;
    ui_init_style(&style_system_setting_backgroud_noise_extra_list_scrollbar_default);

    lv_style_set_radius(&style_system_setting_backgroud_noise_extra_list_scrollbar_default, 4);
    lv_style_set_bg_opa(&style_system_setting_backgroud_noise_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_system_setting_backgroud_noise_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_system_setting_backgroud_noise_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_setting_environment_noise), &style_system_setting_backgroud_noise_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write codes system_setting_recording_pause
    ui->system_setting_recording_pause = lv_spinbox_create(ui->system_setting);
    lv_obj_set_pos(ui->system_setting_recording_pause, 176, 416);
    lv_obj_set_width(ui->system_setting_recording_pause, 86);
    lv_obj_set_height(ui->system_setting_recording_pause, 42);
    lv_spinbox_set_digit_format(ui->system_setting_recording_pause, 2, 1);
    lv_spinbox_set_range(ui->system_setting_recording_pause, -99, 99);
    lv_coord_t system_setting_recording_pause_h = lv_obj_get_height(ui->system_setting_recording_pause);
    ui->system_setting_recording_pause_btn_plus = lv_btn_create(ui->system_setting);
    lv_obj_set_size(ui->system_setting_recording_pause_btn_plus, system_setting_recording_pause_h, system_setting_recording_pause_h);
    lv_obj_align_to(ui->system_setting_recording_pause_btn_plus, ui->system_setting_recording_pause, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->system_setting_recording_pause_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->system_setting_recording_pause_btn_plus, lv_system_setting_recording_pause_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->system_setting_recording_pause_btn_minus = lv_btn_create(ui->system_setting);
    lv_obj_set_size(ui->system_setting_recording_pause_btn_minus, system_setting_recording_pause_h, system_setting_recording_pause_h);
    lv_obj_align_to(ui->system_setting_recording_pause_btn_minus, ui->system_setting_recording_pause, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->system_setting_recording_pause_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->system_setting_recording_pause_btn_minus, lv_system_setting_recording_pause_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->system_setting_recording_pause, 176, 416);

    //Write style for system_setting_recording_pause, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting_recording_pause, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_recording_pause, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_recording_pause, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_setting_recording_pause, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_setting_recording_pause, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_setting_recording_pause, lv_color_hex(0x2F92DA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_setting_recording_pause, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_recording_pause, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_recording_pause, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_recording_pause, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_recording_pause, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_recording_pause, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_recording_pause, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_recording_pause, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_recording_pause, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_recording_pause, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_recording_pause, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for system_setting_recording_pause, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_setting_recording_pause, lv_color_hex(0xffffff), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_recording_pause, &lv_font_montserratMedium_16, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_recording_pause, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_recording_pause, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_recording_pause, lv_color_hex(0x2195f6), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_recording_pause, LV_GRAD_DIR_NONE, LV_PART_CURSOR | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_system_setting_recording_pause_extra_btns_main_default
    static lv_style_t style_system_setting_recording_pause_extra_btns_main_default;
    ui_init_style(&style_system_setting_recording_pause_extra_btns_main_default);

    lv_style_set_text_color(&style_system_setting_recording_pause_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_system_setting_recording_pause_extra_btns_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_system_setting_recording_pause_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_system_setting_recording_pause_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_system_setting_recording_pause_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_system_setting_recording_pause_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_system_setting_recording_pause_extra_btns_main_default, 0);
    lv_style_set_radius(&style_system_setting_recording_pause_extra_btns_main_default, 7);
    lv_style_set_shadow_width(&style_system_setting_recording_pause_extra_btns_main_default, 0);
    lv_obj_add_style(ui->system_setting_recording_pause_btn_plus, &style_system_setting_recording_pause_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->system_setting_recording_pause_btn_minus, &style_system_setting_recording_pause_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes system_setting_slider_brightness
    ui->system_setting_slider_brightness = lv_slider_create(ui->system_setting);
    lv_obj_set_style_anim_time(ui->system_setting_slider_brightness, 1000, 0);
    lv_bar_set_mode(ui->system_setting_slider_brightness, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->system_setting_slider_brightness, 20, 100);
    lv_bar_set_value(ui->system_setting_slider_brightness, 80, LV_ANIM_ON);
    lv_obj_set_pos(ui->system_setting_slider_brightness, 129, 89);
    lv_obj_set_size(ui->system_setting_slider_brightness, 180, 12);

    //Write style for system_setting_slider_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting_slider_brightness, 93, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_slider_brightness, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_slider_brightness, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_slider_brightness, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_slider_brightness, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for system_setting_slider_brightness, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_setting_slider_brightness, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_setting_slider_brightness, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_setting_slider_brightness, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_slider_brightness, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //Write codes system_setting_label_9
    ui->system_setting_label_9 = lv_label_create(ui->system_setting);
    lv_label_set_text(ui->system_setting_label_9, "屏幕亮度");
    lv_label_set_long_mode(ui->system_setting_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_setting_label_9, 9, 82);
    lv_obj_set_size(ui->system_setting_label_9, 95, 25);

    //Write style for system_setting_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_setting_label_9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_setting_label_9, &lv_customer_font_Siyuan_yuanti_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_setting_label_9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_setting_label_9, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_setting_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //The custom code of system_setting.
    load_system_setting_data();

    //Update current screen layout.
    lv_obj_update_layout(ui->system_setting);

    //Init events for screen.
    events_init_system_setting(ui);
}
