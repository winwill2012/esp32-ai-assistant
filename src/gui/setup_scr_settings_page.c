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



void setup_scr_settings_page(lv_ui *ui)
{
    //Write codes settings_page
    ui->settings_page = lv_obj_create(NULL);
    lv_obj_set_size(ui->settings_page, 320, 480);
    lv_obj_set_scrollbar_mode(ui->settings_page, LV_SCROLLBAR_MODE_OFF);

    //Write style for settings_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_page, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_page_cont_1
    ui->settings_page_cont_1 = lv_obj_create(ui->settings_page);
    lv_obj_set_pos(ui->settings_page_cont_1, 10, 63);
    lv_obj_set_size(ui->settings_page_cont_1, 300, 353);
    lv_obj_set_scrollbar_mode(ui->settings_page_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for settings_page_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_page_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->settings_page_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->settings_page_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->settings_page_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_page_cont_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_page_cont_1, 58, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_page_cont_1, lv_color_hex(0xfcfdea), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_page_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_page_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_page_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_page_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_page_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_page_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_page_label_setting_title
    ui->settings_page_label_setting_title = lv_label_create(ui->settings_page);
    lv_label_set_text(ui->settings_page_label_setting_title, "" LV_SYMBOL_SETTINGS " 系统设置");
    lv_label_set_long_mode(ui->settings_page_label_setting_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->settings_page_label_setting_title, 33, 15);
    lv_obj_set_size(ui->settings_page_label_setting_title, 95, 22);

    //Write style for settings_page_label_setting_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_page_label_setting_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_page_label_setting_title, &lv_customer_font_Siyuan_Heiti_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_page_label_setting_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_page_label_setting_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_page_label_setting_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_page_imgbtn_back
    ui->settings_page_imgbtn_back = lv_imgbtn_create(ui->settings_page);
    lv_obj_add_flag(ui->settings_page_imgbtn_back, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->settings_page_imgbtn_back, LV_IMGBTN_STATE_RELEASED, NULL, &_retrun_alpha_33x33, NULL);
    ui->settings_page_imgbtn_back_label = lv_label_create(ui->settings_page_imgbtn_back);
    lv_label_set_text(ui->settings_page_imgbtn_back_label, "");
    lv_label_set_long_mode(ui->settings_page_imgbtn_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->settings_page_imgbtn_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->settings_page_imgbtn_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->settings_page_imgbtn_back, 0, 7);
    lv_obj_set_size(ui->settings_page_imgbtn_back, 33, 33);

    //Write style for settings_page_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->settings_page_imgbtn_back, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_page_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_page_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_page_imgbtn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->settings_page_imgbtn_back, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for settings_page_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->settings_page_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->settings_page_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->settings_page_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->settings_page_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for settings_page_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->settings_page_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->settings_page_imgbtn_back, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->settings_page_imgbtn_back, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->settings_page_imgbtn_back, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for settings_page_imgbtn_back, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->settings_page_imgbtn_back, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->settings_page_imgbtn_back, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes settings_page_btn_network_setting
    ui->settings_page_btn_network_setting = lv_btn_create(ui->settings_page);
    ui->settings_page_btn_network_setting_label = lv_label_create(ui->settings_page_btn_network_setting);
    lv_label_set_text(ui->settings_page_btn_network_setting_label, "" LV_SYMBOL_WIFI "网络设置 ");
    lv_label_set_long_mode(ui->settings_page_btn_network_setting_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->settings_page_btn_network_setting_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->settings_page_btn_network_setting, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->settings_page_btn_network_setting_label, LV_PCT(100));
    lv_obj_set_pos(ui->settings_page_btn_network_setting, 26, 138);
    lv_obj_set_size(ui->settings_page_btn_network_setting, 266, 75);

    //Write style for settings_page_btn_network_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_page_btn_network_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_page_btn_network_setting, lv_color_hex(0x4a96d6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_page_btn_network_setting, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->settings_page_btn_network_setting, lv_color_hex(0x3e5a71), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->settings_page_btn_network_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->settings_page_btn_network_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->settings_page_btn_network_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_page_btn_network_setting, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_page_btn_network_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_page_btn_network_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_page_btn_network_setting, &lv_customer_font_Siyuan_Heiti_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_page_btn_network_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_page_btn_network_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes settings_page_btn_voice_setting
    ui->settings_page_btn_voice_setting = lv_btn_create(ui->settings_page);
    ui->settings_page_btn_voice_setting_label = lv_label_create(ui->settings_page_btn_voice_setting);
    lv_label_set_text(ui->settings_page_btn_voice_setting_label, "" LV_SYMBOL_VOLUME_MAX "语音设置 ");
    lv_label_set_long_mode(ui->settings_page_btn_voice_setting_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->settings_page_btn_voice_setting_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->settings_page_btn_voice_setting, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->settings_page_btn_voice_setting_label, LV_PCT(100));
    lv_obj_set_pos(ui->settings_page_btn_voice_setting, 26, 249);
    lv_obj_set_size(ui->settings_page_btn_voice_setting, 266, 75);

    //Write style for settings_page_btn_voice_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->settings_page_btn_voice_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->settings_page_btn_voice_setting, lv_color_hex(0x171e24), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->settings_page_btn_voice_setting, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->settings_page_btn_voice_setting, lv_color_hex(0x6dcbc7), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->settings_page_btn_voice_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->settings_page_btn_voice_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->settings_page_btn_voice_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->settings_page_btn_voice_setting, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->settings_page_btn_voice_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->settings_page_btn_voice_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->settings_page_btn_voice_setting, &lv_customer_font_Siyuan_Heiti_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->settings_page_btn_voice_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->settings_page_btn_voice_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of settings_page.


    //Update current screen layout.
    lv_obj_update_layout(ui->settings_page);

    //Init events for screen.
    events_init_settings_page(ui);
}
