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
#include "lvgl_interface.h"
#include "lvgl.h"
#include "Arduino.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void home_page_microphone_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            break;
        }
        default:
            break;
    }
}

static void home_page_btn_settings_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            ui_load_scr_animation(&guider_ui, &guider_ui.settings_page, guider_ui.settings_page_del,
                                  &guider_ui.home_page_del, setup_scr_settings_page, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200,
                                  false, false);
            break;
        }
        default:
            break;
    }
}

void events_init_home_page(lv_ui *ui) {
    lv_obj_add_event_cb(ui->home_page_microphone, home_page_microphone_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_page_btn_settings, home_page_btn_settings_event_handler, LV_EVENT_ALL, ui);
}

static void settings_page_imgbtn_back_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            ui_load_scr_animation(&guider_ui, &guider_ui.home_page, guider_ui.home_page_del,
                                  &guider_ui.settings_page_del, setup_scr_home_page, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200,
                                  true, true);
            break;
        }
        default:
            break;
    }
}

static void settings_page_btn_network_setting_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            ui_load_scr_animation(&guider_ui, &guider_ui.network_setting, guider_ui.network_setting_del,
                                  &guider_ui.settings_page_del, setup_scr_network_setting, LV_SCR_LOAD_ANIM_MOVE_LEFT,
                                  200, 200, false, false);
            break;
        }
        default:
            break;
    }
}

static void settings_page_btn_voice_setting_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            ui_load_scr_animation(&guider_ui, &guider_ui.speaker_setting, guider_ui.speaker_setting_del,
                                  &guider_ui.settings_page_del, setup_scr_speaker_setting, LV_SCR_LOAD_ANIM_MOVE_LEFT,
                                  200, 200, false, false);
            break;
        }
        default:
            break;
    }
}

void events_init_settings_page(lv_ui *ui) {
    lv_obj_add_event_cb(ui->settings_page_imgbtn_back, settings_page_imgbtn_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_page_btn_network_setting, settings_page_btn_network_setting_event_handler,
                        LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->settings_page_btn_voice_setting, settings_page_btn_voice_setting_event_handler,
                        LV_EVENT_ALL, ui);
}

static void network_setting_imgbtn_back_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            ui_load_scr_animation(&guider_ui, &guider_ui.settings_page, guider_ui.settings_page_del,
                                  &guider_ui.network_setting_del, setup_scr_settings_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT,
                                  200, 200, true, true);
            break;
        }
        default:
            break;
    }
}

static void load_wifi_list_task(void *arg) {
    load_wifi_list((bool *) arg);
    vTaskDelete(NULL);
}

static void network_setting_animimg_refresh_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            lv_animimg_start(lv_event_get_target(e));
            xTaskCreate(load_wifi_list_task, "loadWifiTask", 4096, (void *) true, 0, NULL);
            break;
        }
        default:
            break;
    }
}

void events_init_network_setting(lv_ui *ui) {
    lv_obj_add_event_cb(ui->network_setting_imgbtn_back, network_setting_imgbtn_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->network_setting_animimg_refresh, network_setting_animimg_refresh_event_handler,
                        LV_EVENT_ALL, ui);
}

static void speaker_setting_imgbtn_back_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {
            ui_load_scr_animation(&guider_ui, &guider_ui.settings_page, guider_ui.settings_page_del,
                                  &guider_ui.speaker_setting_del, setup_scr_settings_page, LV_SCR_LOAD_ANIM_MOVE_RIGHT,
                                  200, 200, true, true);
            break;
        }
        default:
            break;
    }
}

static void voice_type_dropdown_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        char selected_voice[64];
        lv_dropdown_get_selected_str(obj, selected_voice, sizeof(selected_voice));
        set_current_voice(selected_voice);
    }
}

static void persona_dropdown_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        char selected_person[64];
        lv_dropdown_get_selected_str(obj, selected_person, sizeof(selected_person));
        set_current_persona(selected_person);
    }
}

static void environment_noise_dropdown_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        char selected_noise[64];
        lv_dropdown_get_selected_str(obj, selected_noise, sizeof(selected_noise));
        set_environment_noise(selected_noise);
    }
}

static void speak_speed_event_cb(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) {
        int value = lv_spinbox_get_value(lv_event_get_target(e));
        set_speak_speed((float) value / 10);
    }
}

static void speak_pause_duration_event_cb(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) {
        int value = lv_spinbox_get_value(lv_event_get_target(e));
        set_speak_pause_duration(value * 100);
    }
}

static void speak_volume_event_cb(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) {
        const int32_t value = lv_slider_get_value(lv_event_get_target(e));
        set_volume_ratio((float) (value / 100.0));
    }
}

void events_init_speaker_setting(lv_ui *ui) {
    lv_obj_add_event_cb(ui->speaker_setting_imgbtn_back, speaker_setting_imgbtn_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->speaker_setting_voice_type, voice_type_dropdown_event_cb, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->speaker_setting_persona, persona_dropdown_event_cb, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->speaker_setting_environment_noise, environment_noise_dropdown_event_cb, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->speaker_setting_speed, speak_speed_event_cb, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->speaker_setting_recording_pause, speak_pause_duration_event_cb, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->speaker_setting_volume, speak_volume_event_cb, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui) {
}
