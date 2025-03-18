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
#include "lvgl_interface.h"


void setup_scr_network_setting(lv_ui *ui) {
    //Write codes network_setting
    ui->network_setting = lv_obj_create(NULL);
    lv_obj_set_size(ui->network_setting, 320, 480);
    lv_obj_set_scrollbar_mode(ui->network_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for network_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->network_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->network_setting, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->network_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

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
    lv_obj_set_style_text_color(ui->network_setting_imgbtn_back, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->network_setting_imgbtn_back, &lv_font_montserratMedium_16,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->network_setting_imgbtn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->network_setting_imgbtn_back, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->network_setting_imgbtn_back, lv_color_hex(0xFF33FF),
                                LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->network_setting_imgbtn_back, &lv_font_montserratMedium_16,
                               LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->network_setting_imgbtn_back, lv_color_hex(0xFF33FF),
                                LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->network_setting_imgbtn_back, &lv_font_montserratMedium_16,
                               LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    //Write style for network_setting_imgbtn_back, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->network_setting_imgbtn_back, 0, LV_PART_MAIN | LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->network_setting_imgbtn_back, 255, LV_PART_MAIN | LV_IMGBTN_STATE_RELEASED);

    //Write codes network_setting_label_title
    ui->network_setting_label_title = lv_label_create(ui->network_setting);
    lv_label_set_text(ui->network_setting_label_title, "" LV_SYMBOL_WIFI " 网络设置 ");
    lv_label_set_long_mode(ui->network_setting_label_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->network_setting_label_title, 33, 15);
    lv_obj_set_size(ui->network_setting_label_title, 100, 22);

    //Write style for network_setting_label_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->network_setting_label_title, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->network_setting_label_title, &lv_customer_font_Siyuan_Heiti_18,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->network_setting_label_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->network_setting_label_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->network_setting_label_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes network_setting_list_1
    ui->network_setting_wifi_list = lv_list_create(ui->network_setting);
    lv_obj_set_pos(ui->network_setting_wifi_list, 10, 85);
    lv_obj_set_size(ui->network_setting_wifi_list, 300, 369);
    lv_obj_set_scrollbar_mode(ui->network_setting_wifi_list, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_network_setting_list_1_main_main_default
    static lv_style_t style_network_setting_list_1_main_main_default;
    ui_init_style(&style_network_setting_list_1_main_main_default);

    lv_style_set_pad_top(&style_network_setting_list_1_main_main_default, 5);
    lv_style_set_pad_left(&style_network_setting_list_1_main_main_default, 5);
    lv_style_set_pad_right(&style_network_setting_list_1_main_main_default, 5);
    lv_style_set_pad_bottom(&style_network_setting_list_1_main_main_default, 5);
    lv_style_set_bg_opa(&style_network_setting_list_1_main_main_default, 58);
    lv_style_set_bg_color(&style_network_setting_list_1_main_main_default, lv_color_hex(0xfcfdea));
    lv_style_set_bg_grad_dir(&style_network_setting_list_1_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_network_setting_list_1_main_main_default, 1);
    lv_style_set_border_opa(&style_network_setting_list_1_main_main_default, 255);
    lv_style_set_border_color(&style_network_setting_list_1_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_network_setting_list_1_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_network_setting_list_1_main_main_default, 5);
    lv_style_set_shadow_width(&style_network_setting_list_1_main_main_default, 0);
    lv_obj_add_style(ui->network_setting_wifi_list, &style_network_setting_list_1_main_main_default,
                     LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_network_setting_list_1_main_scrollbar_default
    static lv_style_t style_network_setting_list_1_main_scrollbar_default;
    ui_init_style(&style_network_setting_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_network_setting_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_network_setting_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_network_setting_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_network_setting_list_1_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->network_setting_wifi_list, &style_network_setting_list_1_main_scrollbar_default,
                     LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_network_setting_list_1_extra_btns_main_default
    static lv_style_t style_network_setting_list_1_extra_btns_main_default;
    ui_init_style(&style_network_setting_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_network_setting_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_network_setting_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_network_setting_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_network_setting_list_1_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_network_setting_list_1_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_network_setting_list_1_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_network_setting_list_1_extra_btns_main_default, &lv_customer_font_Siyuan_Regular_16);
    lv_style_set_text_opa(&style_network_setting_list_1_extra_btns_main_default, 255);
    lv_style_set_radius(&style_network_setting_list_1_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_network_setting_list_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_network_setting_list_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_network_setting_list_1_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_network_setting_list_1_extra_texts_main_default
    static lv_style_t style_network_setting_list_1_extra_texts_main_default;
    ui_init_style(&style_network_setting_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_network_setting_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_network_setting_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_network_setting_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_network_setting_list_1_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_network_setting_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_network_setting_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_network_setting_list_1_extra_texts_main_default, &lv_customer_font_Siyuan_Regular_16);
    lv_style_set_text_opa(&style_network_setting_list_1_extra_texts_main_default, 255);
    lv_style_set_radius(&style_network_setting_list_1_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_network_setting_list_1_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_network_setting_list_1_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_network_setting_list_1_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_network_setting_list_1_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes network_setting_label_1
    ui->network_setting_label_1 = lv_label_create(ui->network_setting);
    lv_label_set_text(ui->network_setting_label_1, "选取附近的WLAN");
    lv_label_set_long_mode(ui->network_setting_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->network_setting_label_1, 33, 55);
    lv_obj_set_size(ui->network_setting_label_1, 147, 18);

    //Write style for network_setting_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->network_setting_label_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->network_setting_label_1, &lv_customer_font_Siyuan_yuanti_18,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->network_setting_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->network_setting_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->network_setting_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes network_setting_animimg_refresh
    ui->network_setting_animimg_refresh = lv_animimg_create(ui->network_setting);
    lv_animimg_set_src(ui->network_setting_animimg_refresh, (const void **) network_setting_animimg_refresh_imgs, 3);
    lv_animimg_set_duration(ui->network_setting_animimg_refresh, 500 * 3);
    lv_animimg_set_repeat_count(ui->network_setting_animimg_refresh, LV_ANIM_REPEAT_INFINITE);
    lv_img_set_src(ui->network_setting_animimg_refresh, network_setting_animimg_refresh_imgs[0]);
    lv_obj_set_pos(ui->network_setting_animimg_refresh, 235, 47);
    lv_obj_set_size(ui->network_setting_animimg_refresh, 25, 25);
    lv_obj_add_flag(ui->network_setting_animimg_refresh, LV_OBJ_FLAG_CLICKABLE);

    //The custom code of network_setting.
    load_wifi_list(false);

    //Update current screen layout.
    lv_obj_update_layout(ui->network_setting);

    //Init events for screen.
    events_init_network_setting(ui);
}
