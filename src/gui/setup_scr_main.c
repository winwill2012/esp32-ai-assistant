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



void setup_scr_main(lv_ui *ui)
{
    //Write codes main
    ui->main = lv_obj_create(NULL);
    lv_obj_set_size(ui->main, 240, 320);
    lv_obj_set_scrollbar_mode(ui->main, LV_SCROLLBAR_MODE_AUTO);

    //Write style for main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_wifi
    ui->main_wifi = lv_img_create(ui->main);
    lv_obj_add_flag(ui->main_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_wifi, &_WIFI_alpha_20x20);
    lv_img_set_pivot(ui->main_wifi, 50,50);
    lv_img_set_angle(ui->main_wifi, 0);
    lv_obj_set_pos(ui->main_wifi, 215, 0);
    lv_obj_set_size(ui->main_wifi, 20, 20);

    //Write style for main_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_1
    ui->main_label_1 = lv_label_create(ui->main);
    lv_label_set_text(ui->main_label_1, "20:00");
    lv_label_set_long_mode(ui->main_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_1, 30, 4);
    lv_obj_set_size(ui->main_label_1, 42, 15);

    //Write style for main_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_1, &lv_font_Antonio_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_animimg_1
    ui->main_animimg_1 = lv_animimg_create(ui->main);
    lv_animimg_set_src(ui->main_animimg_1, (const void **) main_animimg_1_imgs, 8);
    lv_animimg_set_duration(ui->main_animimg_1, 200*8);
    lv_animimg_set_repeat_count(ui->main_animimg_1, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(ui->main_animimg_1);
    lv_obj_set_pos(ui->main_animimg_1, 5, 215);
    lv_obj_set_size(ui->main_animimg_1, 100, 100);

    //Write codes main_chat_text
    ui->main_chat_text = lv_label_create(ui->main);
    lv_label_set_text(ui->main_chat_text, "");
    lv_label_set_long_mode(ui->main_chat_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_chat_text, 16, 71);
    lv_obj_set_size(ui->main_chat_text, 208, 141);

    //Write style for main_chat_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_chat_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_chat_text, &AlibabaPuHuiTi_Bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_chat_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_chat_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_chat_text, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_chat_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_chat_text, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_chat_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_setting_button
    ui->main_setting_button = lv_imgbtn_create(ui->main);
    lv_obj_add_flag(ui->main_setting_button, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->main_setting_button, LV_IMGBTN_STATE_RELEASED, NULL, &_settings_alpha_20x20, NULL);
    ui->main_setting_button_label = lv_label_create(ui->main_setting_button);
    lv_label_set_text(ui->main_setting_button_label, "");
    lv_label_set_long_mode(ui->main_setting_button_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_setting_button_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_setting_button, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->main_setting_button, 5, 0);
    lv_obj_set_size(ui->main_setting_button, 20, 20);

    //Write style for main_setting_button, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->main_setting_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_setting_button, &AlibabaPuHuiTi_Bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_setting_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_setting_button, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_setting_button, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_setting_button, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_setting_button, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_setting_button, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->main_setting_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->main_setting_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->main_setting_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->main_setting_button, &AlibabaPuHuiTi_Bold_14, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->main_setting_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->main_setting_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for main_setting_button, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->main_setting_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->main_setting_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->main_setting_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->main_setting_button, &AlibabaPuHuiTi_Bold_14, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->main_setting_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->main_setting_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for main_setting_button, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->main_setting_button, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->main_setting_button, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of main.


    //Update current screen layout.
    lv_obj_update_layout(ui->main);

    //Init events for screen.
    events_init_main(ui);
}
