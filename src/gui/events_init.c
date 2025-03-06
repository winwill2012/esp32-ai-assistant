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
#include <Arduino.h>

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void main_setting_button_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.settings, guider_ui.settings_del, &guider_ui.main_del, setup_scr_settings, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_main (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->main_setting_button, main_setting_button_event_handler, LV_EVENT_ALL, ui);
}

static void settings_network_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        uint16_t id = lv_dropdown_get_selected(guider_ui.settings_network);

        break;
    }
    default:
        break;
    }
}

static void settings_volume_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        break;
    }
    default:
        break;
    }
}

static void settings_voiceType_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        uint16_t id = lv_dropdown_get_selected(guider_ui.settings_voiceType);
        break;
    }
    default:
        break;
    }
}

static void settings_speed_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {

        break;
    }
    default:
        break;
    }
}

static void settings_setting_confirm_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.settings_del, setup_scr_main, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_settings (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->settings_network, settings_network_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_volume, settings_volume_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_voiceType, settings_voiceType_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_speed, settings_speed_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_setting_confirm, settings_setting_confirm_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
