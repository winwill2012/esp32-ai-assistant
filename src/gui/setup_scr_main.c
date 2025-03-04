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
    lv_obj_set_style_bg_grad_dir(ui->main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_robot
    ui->main_robot = lv_animimg_create(ui->main);
    lv_animimg_set_src(ui->main_robot, (const void **) main_robot_imgs, 8);
    lv_animimg_set_duration(ui->main_robot, 200*8);
    lv_animimg_set_repeat_count(ui->main_robot, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(ui->main_robot);
    lv_obj_set_pos(ui->main_robot, 10, 100);
    lv_obj_set_size(ui->main_robot, 300, 300);

    //Write codes main_wifi
    ui->main_wifi = lv_img_create(ui->main);
    lv_obj_add_flag(ui->main_wifi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_wifi, &_WIFI_alpha_30x30);
    lv_img_set_pivot(ui->main_wifi, 50,50);
    lv_img_set_angle(ui->main_wifi, 0);
    lv_obj_set_pos(ui->main_wifi, 280, 0);
    lv_obj_set_size(ui->main_wifi, 30, 30);

    //Write style for main_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_wifi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_time
    ui->main_time = lv_label_create(ui->main);
    lv_label_set_text(ui->main_time, "20:01");
    lv_label_set_long_mode(ui->main_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_time, 10, 5);
    lv_obj_set_size(ui->main_time, 35, 19);

    //Write style for main_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_time, &lv_font_Antonio_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
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

    //The custom code of main.


    //Update current screen layout.
    lv_obj_update_layout(ui->main);

}
