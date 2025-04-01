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



void setup_scr_screen_main(lv_ui *ui)
{
    //Write codes screen_main
    ui->screen_main = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_main, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_main, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_container_header
    ui->screen_main_container_header = lv_obj_create(lv_layer_top());
    lv_obj_set_pos(ui->screen_main_container_header, 0, 0);
    lv_obj_set_size(ui->screen_main_container_header, 240, 25);
    lv_obj_set_scrollbar_mode(ui->screen_main_container_header, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_main_container_header, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_container_header, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_container_header, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_container_header, 182, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_main_container_header, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_main_container_header, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_container_header, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_container_header, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_container_header, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_container_header, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_container_header, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_img_wifi_state
    ui->screen_main_img_wifi_state = lv_image_create(ui->screen_main_container_header);
    lv_obj_set_pos(ui->screen_main_img_wifi_state, 214, 2);
    lv_obj_set_size(ui->screen_main_img_wifi_state, 20, 20);
    lv_obj_add_flag(ui->screen_main_img_wifi_state, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_main_img_wifi_state, &_no_wifi_RGB565A8_20x20);
    lv_image_set_pivot(ui->screen_main_img_wifi_state, 50,50);
    lv_image_set_rotation(ui->screen_main_img_wifi_state, 0);

    //Write style for screen_main_img_wifi_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_img_wifi_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_main_img_wifi_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_current_time
    ui->screen_main_label_current_time = lv_label_create(ui->screen_main_container_header);
    lv_obj_set_pos(ui->screen_main_label_current_time, 2, 4);
    lv_obj_set_size(ui->screen_main_label_current_time, 48, 16);
    lv_label_set_text(ui->screen_main_label_current_time, "18:00");
    lv_label_set_long_mode(ui->screen_main_label_current_time, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_current_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_current_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_current_time, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_current_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_current_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_current_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_btn_recording_state
    ui->screen_main_btn_recording_state = lv_button_create(ui->screen_main_container_header);
    lv_obj_set_pos(ui->screen_main_btn_recording_state, 76, 7);
    lv_obj_set_size(ui->screen_main_btn_recording_state, 10, 10);
    ui->screen_main_btn_recording_state_label = lv_label_create(ui->screen_main_btn_recording_state);
    lv_label_set_text(ui->screen_main_btn_recording_state_label, "");
    lv_label_set_long_mode(ui->screen_main_btn_recording_state_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_main_btn_recording_state_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_main_btn_recording_state, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_main_btn_recording_state_label, LV_PCT(100));

    //Write style for screen_main_btn_recording_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_main_btn_recording_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_main_btn_recording_state, lv_color_hex(0xcfd1d3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_main_btn_recording_state, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_main_btn_recording_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_btn_recording_state, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_btn_recording_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_btn_recording_state, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_btn_recording_state, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_btn_recording_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_btn_recording_state, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_label_global_state
    ui->screen_main_label_global_state = lv_label_create(ui->screen_main_container_header);
    lv_obj_set_pos(ui->screen_main_label_global_state, 92, 4);
    lv_obj_set_size(ui->screen_main_label_global_state, 70, 15);
    lv_label_set_text(ui->screen_main_label_global_state, "正在聆听");
    lv_label_set_long_mode(ui->screen_main_label_global_state, LV_LABEL_LONG_WRAP);

    //Write style for screen_main_label_global_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_main_label_global_state, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_label_global_state, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_label_global_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_label_global_state, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_label_global_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_main_list_message_history
    ui->screen_main_list_message_history = lv_list_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_list_message_history, 0, 25);
    lv_obj_set_size(ui->screen_main_list_message_history, 235, 250);
    lv_obj_set_scrollbar_mode(ui->screen_main_list_message_history, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_screen_main_list_message_history_main_main_default
    static lv_style_t style_screen_main_list_message_history_main_main_default;
    ui_init_style(&style_screen_main_list_message_history_main_main_default);

    lv_style_set_pad_top(&style_screen_main_list_message_history_main_main_default, 5);
    lv_style_set_pad_left(&style_screen_main_list_message_history_main_main_default, 5);
    lv_style_set_pad_right(&style_screen_main_list_message_history_main_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_main_list_message_history_main_main_default, 5);
    lv_style_set_bg_opa(&style_screen_main_list_message_history_main_main_default, 255);
    lv_style_set_bg_color(&style_screen_main_list_message_history_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_main_list_message_history_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_main_list_message_history_main_main_default, 0);
    lv_style_set_radius(&style_screen_main_list_message_history_main_main_default, 3);
    lv_style_set_shadow_width(&style_screen_main_list_message_history_main_main_default, 0);
    lv_obj_add_style(ui->screen_main_list_message_history, &style_screen_main_list_message_history_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_main_list_message_history_main_scrollbar_default
    static lv_style_t style_screen_main_list_message_history_main_scrollbar_default;
    ui_init_style(&style_screen_main_list_message_history_main_scrollbar_default);

    lv_style_set_radius(&style_screen_main_list_message_history_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_main_list_message_history_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_main_list_message_history_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_main_list_message_history_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_main_list_message_history, &style_screen_main_list_message_history_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_main_list_message_history_extra_btns_main_default
    static lv_style_t style_screen_main_list_message_history_extra_btns_main_default;
    ui_init_style(&style_screen_main_list_message_history_extra_btns_main_default);

    lv_style_set_pad_top(&style_screen_main_list_message_history_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_screen_main_list_message_history_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_screen_main_list_message_history_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_main_list_message_history_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_screen_main_list_message_history_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_screen_main_list_message_history_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_main_list_message_history_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_main_list_message_history_extra_btns_main_default, 255);
    lv_style_set_radius(&style_screen_main_list_message_history_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_screen_main_list_message_history_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_main_list_message_history_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_main_list_message_history_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_screen_main_list_message_history_extra_texts_main_default
    static lv_style_t style_screen_main_list_message_history_extra_texts_main_default;
    ui_init_style(&style_screen_main_list_message_history_extra_texts_main_default);

    lv_style_set_pad_top(&style_screen_main_list_message_history_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_screen_main_list_message_history_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_screen_main_list_message_history_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_main_list_message_history_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_screen_main_list_message_history_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_screen_main_list_message_history_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_main_list_message_history_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_main_list_message_history_extra_texts_main_default, 255);
    lv_style_set_radius(&style_screen_main_list_message_history_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_screen_main_list_message_history_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_screen_main_list_message_history_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_screen_main_list_message_history_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_main_list_message_history_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes screen_main_imgbtn_mic
    ui->screen_main_imgbtn_mic = lv_imagebutton_create(ui->screen_main);
    lv_obj_set_pos(ui->screen_main_imgbtn_mic, 107, 286);
    lv_obj_set_size(ui->screen_main_imgbtn_mic, 25, 25);
    lv_obj_add_flag(ui->screen_main_imgbtn_mic, LV_OBJ_FLAG_CHECKABLE);
    lv_imagebutton_set_src(ui->screen_main_imgbtn_mic, LV_IMAGEBUTTON_STATE_RELEASED, &_mic_off_RGB565A8_25x25, NULL, NULL);
    ui->screen_main_imgbtn_mic_label = lv_label_create(ui->screen_main_imgbtn_mic);
    lv_label_set_text(ui->screen_main_imgbtn_mic_label, "");
    lv_label_set_long_mode(ui->screen_main_imgbtn_mic_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_main_imgbtn_mic_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_main_imgbtn_mic, 0, LV_STATE_DEFAULT);

    //Write style for screen_main_imgbtn_mic, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_main_imgbtn_mic, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_main_imgbtn_mic, &lv_customer_font_Siyuan_yuanti_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_main_imgbtn_mic, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_main_imgbtn_mic, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_main_imgbtn_mic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_main_imgbtn_mic, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_imgbtn_mic, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->screen_main_imgbtn_mic, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_main_imgbtn_mic, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_main_imgbtn_mic, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_main_imgbtn_mic, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_main_imgbtn_mic, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_main_imgbtn_mic, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_imgbtn_mic, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_image_opa(ui->screen_main_imgbtn_mic, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_main_imgbtn_mic, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_main_imgbtn_mic, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_main_imgbtn_mic, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_main_imgbtn_mic, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_main_imgbtn_mic, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->screen_main_imgbtn_mic, 0, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->screen_main_imgbtn_mic, 255, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);

    //The custom code of screen_main.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_main);

    //Init events for screen.
    events_init_screen_main(ui);
}
