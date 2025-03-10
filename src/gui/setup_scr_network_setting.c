/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include <esp_wifi_types.h>
#include "esp_wifi.h"
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


// 定义全局变量
lv_obj_t *loading_anim;
lv_obj_t *wifi_list;
uint16_t wifi_count = 0;
wifi_ap_record_t ap_info[20];

static void connect_wifi_callback (lv_event_t * e) {

}

// 处理列表项点击事件
static void list_item_click_event_cb(lv_event_t *e)
{
    // lv_obj_t *obj = lv_event_get_target(e);
    // int index = lv_list_get_btn_index(wifi_list, obj);

    // 创建输入框
    lv_obj_t *kb = lv_keyboard_create(lv_scr_act());
    lv_obj_t *ta = lv_textarea_create(lv_scr_act());
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_width(ta, lv_pct(50));
    lv_obj_align(ta, LV_ALIGN_CENTER, 0, -50);
    lv_keyboard_set_textarea(kb, ta);

    // 创建确定按钮
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_width(btn, lv_pct(20));
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 50);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "确定");

    lv_obj_add_event_cb(btn, connect_wifi_callback, LV_EVENT_CLICKED, e->user_data);
}

// 扫描 WiFi 网络
static void scan_wifi()
{
    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_records(&wifi_count, ap_info);
}

// 创建加载动画
static void create_loading_anim(lv_obj_t *parent)
{
    loading_anim = lv_spinner_create(parent, 1000, 60);
    lv_obj_set_size(loading_anim, 50, 50);
    lv_obj_align(loading_anim, LV_ALIGN_CENTER, 0, 0);
}

// 移除加载动画
static void remove_loading_anim()
{
    lv_obj_del(loading_anim);
}

// 创建 WiFi 列表
static void create_wifi_list(lv_obj_t *parent)
{
    wifi_list = lv_list_create(parent);
    lv_obj_set_size(wifi_list, lv_pct(100), lv_pct(80));
    lv_obj_align(wifi_list, LV_ALIGN_BOTTOM_MID, 0, 0);

    for (int i = 0; i < wifi_count; i++) {
        lv_obj_t *btn = lv_list_add_text(wifi_list, ap_info[i].ssid);
        lv_obj_add_event_cb(btn, list_item_click_event_cb, LV_EVENT_CLICKED, ap_info[i].ssid);
    }
}

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
    // 创建加载动画
    create_loading_anim(ui->network_setting);

    // 扫描 WiFi 网络
    scan_wifi();

    // 移除加载动画
    remove_loading_anim();

    // 创建 WiFi 列表
    create_wifi_list(ui->network_setting);

    //Update current screen layout.
    lv_obj_update_layout(ui->network_setting);

    //Init events for screen.
    events_init_network_setting(ui);
}
