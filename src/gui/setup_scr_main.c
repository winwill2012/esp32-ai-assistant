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
    lv_obj_set_size(ui->main, 320, 480);
    lv_obj_set_scrollbar_mode(ui->main, LV_SCROLLBAR_MODE_OFF);

    //Write style for main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->main, lv_color_hex(0x1a2a38), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->main, 175, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_time
    ui->main_time = lv_label_create(ui->main);
    lv_obj_set_pos(ui->main_time, 0, 5);
    lv_obj_set_size(ui->main_time, 40, 15);
    lv_label_set_text(ui->main_time, "19:00\n");
    lv_label_set_long_mode(ui->main_time, LV_LABEL_LONG_WRAP);

    //Write style for main_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_time, &lv_font_Antonio_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_wifi
    ui->main_wifi = lv_image_create(ui->main);
    lv_obj_set_pos(ui->main_wifi, 301, 3);
    lv_obj_set_size(ui->main_wifi, 18, 18);
    lv_obj_add_flag(ui->main_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->main_wifi, &_WIFI_RGB565A8_18x18);
    lv_image_set_pivot(ui->main_wifi, 50,50);
    lv_image_set_rotation(ui->main_wifi, 0);

    //Write style for main_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->main_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->main_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_imgbtn_1
    ui->main_imgbtn_1 = lv_imagebutton_create(ui->main);
    lv_obj_set_pos(ui->main_imgbtn_1, 132, 400);
    lv_obj_set_size(ui->main_imgbtn_1, 50, 50);
    lv_obj_add_flag(ui->main_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imagebutton_set_src(ui->main_imgbtn_1, LV_IMAGEBUTTON_STATE_RELEASED, &_dial_RGB565A8_50x50, NULL, NULL);
    ui->main_imgbtn_1_label = lv_label_create(ui->main_imgbtn_1);
    lv_label_set_text(ui->main_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->main_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_imgbtn_1, 0, LV_STATE_DEFAULT);

    //Write style for main_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->main_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for main_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->main_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->main_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->main_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->main_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->main_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->main_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for main_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_image_recolor_opa(ui->main_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_image_opa(ui->main_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->main_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->main_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->main_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->main_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for main_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->main_imgbtn_1, 0, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->main_imgbtn_1, 255, LV_PART_MAIN|LV_IMAGEBUTTON_STATE_RELEASED);

    //Write codes main_question
    ui->main_question = lv_label_create(ui->main);
    lv_obj_set_pos(ui->main_question, 20, 47);
    lv_obj_set_size(ui->main_question, 280, 150);
    lv_label_set_text(ui->main_question, "你好啊");
    lv_label_set_long_mode(ui->main_question, LV_LABEL_LONG_WRAP);

    //Write style for main_question, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_question, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_question, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_question, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_question, &lv_font_SourceHanSansCN_Medium_2_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_question, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_question, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_question, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_question, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_question, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_question, lv_color_hex(0x607282), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_question, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_question, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_question, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_question, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_question, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_question, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_answer
    ui->main_answer = lv_label_create(ui->main);
    lv_obj_set_pos(ui->main_answer, 20, 226);
    lv_obj_set_size(ui->main_answer, 280, 150);
    lv_label_set_text(ui->main_answer, "在线取色器选择一张本地图片号,可以直接点击图片进行取色(手机平板,请使用我们的触屏版工具，也可以直接点击“列出所有颜色”按钮,自动列出图片上的所有颜色");
    lv_label_set_long_mode(ui->main_answer, LV_LABEL_LONG_WRAP);

    //Write style for main_answer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_answer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_answer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_answer, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_answer, &lv_font_SourceHanSansCN_Medium_2_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_answer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_answer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_answer, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_answer, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_answer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_answer, lv_color_hex(0x76797b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_answer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_answer, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_answer, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_answer, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_answer, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_answer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main.


    //Update current screen layout.
    lv_obj_update_layout(ui->main);

}
