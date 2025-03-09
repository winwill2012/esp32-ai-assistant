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



void setup_scr_network_setting(lv_ui *ui)
{
    //Write codes network_setting
    ui->network_setting = lv_obj_create(NULL);
    lv_obj_set_size(ui->network_setting, 320, 480);
    lv_obj_set_scrollbar_mode(ui->network_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for network_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->network_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->network_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->network_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes network_setting_imgbtn_back
    ui->network_setting_imgbtn_back = lv_imgbtn_create(ui->network_setting);
    lv_obj_add_flag(ui->network_setting_imgbtn_back, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->network_setting_imgbtn_back, LV_IMGBTN_STATE_RELEASED, NULL, &_retrun_alpha_33x33, NULL);
    ui->network_setting_imgbtn_back_label = lv_label_create(ui->network_setting_imgbtn_back);
    lv_label_set_text(ui->network_setting_imgbtn_back_label, "");
    lv_label_set_long_mode(ui->network_setting_imgbtn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->network_setting_imgbtn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->network_setting_imgbtn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->network_setting_imgbtn_back, 0, 6);
    lv_obj_set_size(ui->network_setting_imgbtn_back, 33, 33);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->network_setting_imgbtn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->network_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->network_setting_imgbtn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->network_setting_imgbtn_back, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->network_setting_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->network_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->network_setting_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->network_setting_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes network_setting_label_title
    ui->network_setting_label_title = lv_label_create(ui->network_setting);
    lv_label_set_text(ui->network_setting_label_title, "网络设置");
    lv_label_set_long_mode(ui->network_setting_label_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->network_setting_label_title, 33, 15);
    lv_obj_set_size(ui->network_setting_label_title, 88, 22);

    //Write style for network_setting_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->network_setting_label_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->network_setting_label_title, &lv_customer_font_Siyuan_Heiti_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->network_setting_label_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->network_setting_label_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->network_setting_label_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of network_setting.


    //Update current screen layout.
    lv_obj_update_layout(ui->network_setting);

    //Init events for screen.
    events_init_network_setting(ui);
}
