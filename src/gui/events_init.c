/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "lvgl_interface.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void screen_main_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_GESTURE:
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
            switch (dir)
            {
            case LV_DIR_LEFT:
                {
                    lv_indev_wait_release(lv_indev_active());
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_settings, guider_ui.screen_settings_del,
                                          &guider_ui.screen_main_del, setup_scr_screen_settings, LV_SCR_LOAD_ANIM_NONE,
                                          200, 200, false, false);
                    break;
                }
            default:
                break;
            }
            break;
        }
    default:
        break;
    }
}

static void screen_main_imgbtn_mic_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            on_btn_speak_clicked();
            break;
        }
    case LV_EVENT_PRESSED:
        {
            on_btn_speak_pressed();
            break;
        }
    case LV_EVENT_RELEASED:
        {
            on_btn_speak_released();
        }
    default:
        break;
    }
}

void events_init_screen_main(lv_ui* ui)
{
    lv_obj_add_event_cb(ui->screen_main, screen_main_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_main_btn_speak, screen_main_imgbtn_mic_event_handler, LV_EVENT_ALL, ui);
}

static void screen_settings_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_GESTURE:
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
            switch (dir)
            {
            case LV_DIR_RIGHT:
                {
                    lv_indev_wait_release(lv_indev_active());
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_main, guider_ui.screen_main_del,
                                          &guider_ui.screen_settings_del, setup_scr_screen_main,
                                          LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
                    break;
                }
            default:
                break;
            }
            break;
        }
    default:
        break;
    }
}

static void screen_settings_btn_networking_setting_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_networking_setting,
                                  guider_ui.screen_networking_setting_del, &guider_ui.screen_settings_del,
                                  setup_scr_screen_networking_setting, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false,
                                  false);
            break;
        }
    default:
        break;
    }
}

static void screen_settings_btn_system_setting_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_system_setting, guider_ui.screen_system_setting_del,
                                  &guider_ui.screen_settings_del, setup_scr_screen_system_setting,
                                  LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, false);
            break;
        }
    default:
        break;
    }
}

static void screen_settings_btn_reset_setting_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            break;
        }
    default:
        break;
    }
}

static void screen_settings_btn_1_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            break;
        }
    default:
        break;
    }
}

void events_init_screen_settings(lv_ui* ui)
{
    lv_obj_add_event_cb(ui->screen_settings, screen_settings_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_settings_btn_networking_setting,
                        screen_settings_btn_networking_setting_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_settings_btn_system_setting, screen_settings_btn_system_setting_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_settings_btn_reset_setting, screen_settings_btn_reset_setting_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_settings_btn_1, screen_settings_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void scan_wifi_timer_cb(lv_timer_t* timer)
{
    load_wifi_list(timer);
}

static void screen_networking_setting_img_refresh_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            lv_timer_create(scan_wifi_timer_cb, 50, NULL);
            break;
        }
    default:
        break;
    }
}

static void screen_networking_setting_btn_back_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_settings, guider_ui.screen_settings_del,
                                  &guider_ui.screen_networking_setting_del, setup_scr_screen_settings,
                                  LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, true);
            break;
        }
    default:
        break;
    }
}

static void screen_networking_setting_btn_cancel_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            lv_obj_add_flag(guider_ui.screen_networking_setting_cont_wifi_password_dialog, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_networking_setting_cont_mask, LV_OBJ_FLAG_HIDDEN);
            guider_ui.screen_networking_settings_clicked_wifi_ssid = NULL;
            break;
        }
    default:
        break;
    }
}

static void screen_networking_setting_cont_mask_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            lv_obj_add_flag(guider_ui.screen_networking_setting_cont_wifi_password_dialog, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(guider_ui.screen_networking_setting_cont_mask, LV_OBJ_FLAG_HIDDEN);
            guider_ui.screen_networking_settings_clicked_wifi_ssid = NULL;
            break;
        }
    default:
        break;
    }
}

static void connect_wifi_timer_cb(lv_timer_t* timer)
{
    connect_wifi(timer, guider_ui.screen_networking_settings_clicked_wifi_ssid,
        guider_ui.screen_networking_settings_clicked_wifi_password);
}

static void screen_networking_setting_btn_confirm_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            guider_ui.screen_networking_settings_clicked_wifi_password = lv_textarea_get_text(guider_ui.screen_networking_setting_ta_wifi_password);
            lv_obj_add_flag(guider_ui.screen_networking_setting_cont_wifi_password_dialog, LV_OBJ_FLAG_HIDDEN);
            lv_timer_create(connect_wifi_timer_cb, 1000 , NULL);
            break;
        }
    default:
        break;
    }
}

void events_init_screen_networking_setting(lv_ui* ui)
{
    lv_obj_add_event_cb(ui->screen_networking_setting_img_refresh, screen_networking_setting_img_refresh_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_networking_setting_btn_back, screen_networking_setting_btn_back_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_networking_setting_btn_cancel, screen_networking_setting_btn_cancel_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_networking_setting_btn_confirm, screen_networking_setting_btn_confirm_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_networking_setting_cont_mask, screen_networking_setting_cont_mask_event_handler,
                        LV_EVENT_ALL, ui);
}

static void screen_system_setting_slider_speak_volume_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        {
            set_volume_ratio(lv_slider_get_value(lv_event_get_target(e)) / 100.0);
            break;
        }
    default:
        break;
    }
}

static void screen_system_setting_ddlist_voice_type_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        {
            char buffer[50];
            lv_dropdown_get_selected_str(guider_ui.screen_system_setting_ddlist_voice_type, buffer, sizeof(buffer));
            set_current_voice(buffer);
            break;
        }
    default:
        break;
    }
}

static void screen_system_setting_ddlist_persona_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        {
            char buffer[50];
            lv_dropdown_get_selected_str(guider_ui.screen_system_setting_ddlist_persona, buffer, sizeof(buffer));
            set_current_persona(buffer);
            break;
        }
    default:
        break;
    }
}

static void screen_system_setting_slider_screen_brightness_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        {
            set_screen_brightness(lv_slider_get_value(lv_event_get_target(e)));
            break;
        }
    default:
        break;
    }
}

static void screen_system_setting_btn_back_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_settings, guider_ui.screen_settings_del,
                                  &guider_ui.screen_system_setting_del, setup_scr_screen_settings,
                                  LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, true);
            break;
        }
    default:
        break;
    }
}

static void screen_system_setting_slider_speak_speed_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        {
            set_speak_speed(lv_slider_get_value(lv_event_get_target(e)) / 10.0);
            break;
        }
    default:
        break;
    }
}

void events_init_screen_system_setting(lv_ui* ui)
{
    lv_obj_add_event_cb(ui->screen_system_setting_slider_speak_volume,
                        screen_system_setting_slider_speak_volume_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_system_setting_ddlist_voice_type,
                        screen_system_setting_ddlist_voice_type_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_system_setting_ddlist_persona, screen_system_setting_ddlist_persona_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_system_setting_slider_screen_brightness,
                        screen_system_setting_slider_screen_brightness_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_system_setting_btn_back, screen_system_setting_btn_back_event_handler, LV_EVENT_ALL,
                        ui);
    lv_obj_add_event_cb(ui->screen_system_setting_slider_speak_speed,
                        screen_system_setting_slider_speak_speed_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui* ui)
{
}
