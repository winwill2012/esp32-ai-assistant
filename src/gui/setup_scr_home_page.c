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



void setup_scr_home_page(lv_ui *ui)
{
    //Write codes home_page
    ui->home_page = lv_obj_create(NULL);
    lv_obj_set_size(ui->home_page, 320, 480);
    lv_obj_set_scrollbar_mode(ui->home_page, LV_SCROLLBAR_MODE_AUTO);

    //Write style for home_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page, lv_color_hex(0xf1adad), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_page, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->home_page, lv_color_hex(0xded8d8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->home_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->home_page, 77, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_container_top
    ui->home_page_container_top = lv_obj_create(ui->home_page);
    lv_obj_set_pos(ui->home_page_container_top, 0, 0);
    lv_obj_set_size(ui->home_page_container_top, 320, 30);
    lv_obj_set_scrollbar_mode(ui->home_page_container_top, LV_SCROLLBAR_MODE_OFF);

    //Write style for home_page_container_top, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_container_top, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_container_top, lv_color_hex(0x4c4a4a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_page_container_top, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_container_top, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_header_wifi
    ui->home_page_header_wifi = lv_img_create(ui->home_page_container_top);
    lv_obj_add_flag(ui->home_page_header_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_page_header_wifi, &_WIFI_alpha_26x26);
    lv_img_set_pivot(ui->home_page_header_wifi, 50,50);
    lv_img_set_angle(ui->home_page_header_wifi, 0);
    lv_obj_set_pos(ui->home_page_header_wifi, 286, 1);
    lv_obj_set_size(ui->home_page_header_wifi, 26, 26);

    //Write style for home_page_header_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_page_header_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_page_header_wifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_page_header_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_page_header_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_page_header_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_header_time
    ui->home_page_header_time = lv_label_create(ui->home_page_container_top);
    lv_label_set_text(ui->home_page_header_time, "00:00");
    lv_label_set_long_mode(ui->home_page_header_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_page_header_time, 12, 5);
    lv_obj_set_size(ui->home_page_header_time, 44, 19);

    //Write style for home_page_header_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_header_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_header_time, &lv_customer_font_Siyuan_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_page_header_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_header_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_header_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_header_wifi_no
    ui->home_page_header_wifi_no = lv_line_create(ui->home_page_container_top);
    static lv_point_t home_page_header_wifi_no[] = {{2, 3},{24, 27},};
    lv_line_set_points(ui->home_page_header_wifi_no, home_page_header_wifi_no, 2);
    lv_obj_set_pos(ui->home_page_header_wifi_no, 286, 0);
    lv_obj_set_size(ui->home_page_header_wifi_no, 26, 26);

    //Write style for home_page_header_wifi_no, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->home_page_header_wifi_no, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->home_page_header_wifi_no, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->home_page_header_wifi_no, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->home_page_header_wifi_no, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_header_state
    ui->home_page_header_state = lv_label_create(ui->home_page_container_top);
    lv_label_set_text(ui->home_page_header_state, "正在聆听...");
    lv_label_set_long_mode(ui->home_page_header_state, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->home_page_header_state, 115, 7);
    lv_obj_set_size(ui->home_page_header_state, 90, 16);

    //Write style for home_page_header_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_header_state, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_header_state, &lv_customer_font_Siyuan_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_page_header_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_header_state, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_header_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_microphone
    ui->home_page_microphone = lv_img_create(ui->home_page);
    lv_obj_add_flag(ui->home_page_microphone, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->home_page_microphone, &_micphone_alpha_40x40);
    lv_img_set_pivot(ui->home_page_microphone, 50,50);
    lv_img_set_angle(ui->home_page_microphone, 0);
    lv_obj_set_pos(ui->home_page_microphone, 140, 420);
    lv_obj_set_size(ui->home_page_microphone, 40, 40);

    //Write style for home_page_microphone, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->home_page_microphone, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_page_microphone, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_page_microphone, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_page_microphone, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_line_stop_recording
    ui->home_page_line_stop_recording = lv_line_create(ui->home_page);
    static lv_point_t home_page_line_stop_recording[] = {{2, 3},{37, 42},};
    lv_line_set_points(ui->home_page_line_stop_recording, home_page_line_stop_recording, 2);
    lv_obj_set_pos(ui->home_page_line_stop_recording, 140, 420);
    lv_obj_set_size(ui->home_page_line_stop_recording, 40, 40);

    //Write style for home_page_line_stop_recording, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->home_page_line_stop_recording, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->home_page_line_stop_recording, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->home_page_line_stop_recording, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->home_page_line_stop_recording, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes home_page_message_list
    ui->home_page_message_list = lv_list_create(ui->home_page);
    lv_obj_set_pos(ui->home_page_message_list, 5, 75);
    lv_obj_set_size(ui->home_page_message_list, 306, 324);
    lv_obj_set_scrollbar_mode(ui->home_page_message_list, LV_SCROLLBAR_MODE_AUTO);

    //Write style state: LV_STATE_DEFAULT for &style_home_page_message_list_main_main_default
    static lv_style_t style_home_page_message_list_main_main_default;
    ui_init_style(&style_home_page_message_list_main_main_default);

    lv_style_set_pad_top(&style_home_page_message_list_main_main_default, 5);
    lv_style_set_pad_left(&style_home_page_message_list_main_main_default, 5);
    lv_style_set_pad_right(&style_home_page_message_list_main_main_default, 5);
    lv_style_set_pad_bottom(&style_home_page_message_list_main_main_default, 5);
    lv_style_set_bg_opa(&style_home_page_message_list_main_main_default, 0);
    lv_style_set_border_width(&style_home_page_message_list_main_main_default, 0);
    lv_style_set_radius(&style_home_page_message_list_main_main_default, 4);
    lv_style_set_shadow_width(&style_home_page_message_list_main_main_default, 0);
    lv_obj_add_style(ui->home_page_message_list, &style_home_page_message_list_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_home_page_message_list_main_scrollbar_default
    static lv_style_t style_home_page_message_list_main_scrollbar_default;
    ui_init_style(&style_home_page_message_list_main_scrollbar_default);

    lv_style_set_radius(&style_home_page_message_list_main_scrollbar_default, 4);
    lv_style_set_bg_opa(&style_home_page_message_list_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_home_page_message_list_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_home_page_message_list_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->home_page_message_list, &style_home_page_message_list_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_home_page_message_list_extra_btns_main_default
    static lv_style_t style_home_page_message_list_extra_btns_main_default;
    ui_init_style(&style_home_page_message_list_extra_btns_main_default);

    lv_style_set_pad_top(&style_home_page_message_list_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_home_page_message_list_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_home_page_message_list_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_home_page_message_list_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_home_page_message_list_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_home_page_message_list_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_home_page_message_list_extra_btns_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_home_page_message_list_extra_btns_main_default, 255);
    lv_style_set_radius(&style_home_page_message_list_extra_btns_main_default, 4);
    lv_style_set_bg_opa(&style_home_page_message_list_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_home_page_message_list_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_home_page_message_list_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_home_page_message_list_extra_texts_main_default
    static lv_style_t style_home_page_message_list_extra_texts_main_default;
    ui_init_style(&style_home_page_message_list_extra_texts_main_default);

    lv_style_set_pad_top(&style_home_page_message_list_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_home_page_message_list_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_home_page_message_list_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_home_page_message_list_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_home_page_message_list_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_home_page_message_list_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_home_page_message_list_extra_texts_main_default, &lv_font_montserratMedium_16);
    lv_style_set_text_opa(&style_home_page_message_list_extra_texts_main_default, 255);
    lv_style_set_radius(&style_home_page_message_list_extra_texts_main_default, 4);
    lv_style_set_transform_width(&style_home_page_message_list_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_home_page_message_list_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_home_page_message_list_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_home_page_message_list_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes home_page_btn_settings
    ui->home_page_btn_settings = lv_btn_create(ui->home_page);
    ui->home_page_btn_settings_label = lv_label_create(ui->home_page_btn_settings);
    lv_label_set_text(ui->home_page_btn_settings_label, "系统设置");
    lv_label_set_long_mode(ui->home_page_btn_settings_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->home_page_btn_settings_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->home_page_btn_settings, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->home_page_btn_settings_label, LV_PCT(100));
    lv_obj_set_pos(ui->home_page_btn_settings, 121, 39);
    lv_obj_set_size(ui->home_page_btn_settings, 74, 30);

    //Write style for home_page_btn_settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->home_page_btn_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_btn_settings, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->home_page_btn_settings, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_page_btn_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->home_page_btn_settings, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_btn_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_btn_settings, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_btn_settings, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->home_page_btn_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_btn_settings, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of home_page.


    //Update current screen layout.
    lv_obj_update_layout(ui->home_page);

    //Init events for screen.
    events_init_home_page(ui);
}
