#include "LvglDisplay.h"

#include <FT6336.h>
#include <gui/events_init.h>
#include <gui/gui_guider.h>

#define TFT_WIDTH   320
#define TFT_HEIGHT   480
#define I2C_SDA 10
#define I2C_SCL 13
#define RST_N_PIN 9
#define INT_N_PIN 12
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT/10)

static lv_disp_draw_buf_t draw_buf;

FT6336 ts(I2C_SDA, I2C_SCL, INT_N_PIN, RST_N_PIN, TFT_WIDTH, TFT_HEIGHT);
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data) {
    ts.read();
    if (ts.isTouched) {
        data->point.x = static_cast<lv_coord_t>(ts.points[0].x);
        data->point.y = static_cast<lv_coord_t>(ts.points[0].y);
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

lv_ui guider_ui;
lv_style_t *LvglDisplay::message_style_robot = static_cast<lv_style_t *>(malloc(sizeof(lv_style_t)));
lv_style_t *LvglDisplay::message_style_user = static_cast<lv_style_t *>(malloc(sizeof(lv_style_t)));
lv_obj_t *LvglDisplay::last_message;
int LvglDisplay::current_message_number = 0;
SemaphoreHandle_t LvglDisplay::lvglMutex = xSemaphoreCreateMutex();

void LvglDisplay::initMessageStyle() {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        lv_style_init(message_style_robot);
        lv_style_init(message_style_user);

        lv_style_set_text_font(message_style_robot, &lv_customer_font_Siyuan_Regular_16);
        lv_style_set_text_font(message_style_user, &lv_customer_font_Siyuan_Regular_16);

        lv_style_set_text_align(message_style_robot, LV_TEXT_ALIGN_LEFT);
        lv_style_set_text_align(message_style_user, LV_TEXT_ALIGN_LEFT);

        lv_style_set_pad_top(message_style_robot, 20);
        lv_style_set_pad_top(message_style_user, 20);

        lv_style_set_text_color(message_style_robot, lv_color_make(100, 100, 100));
        lv_style_set_text_color(message_style_user, lv_color_make(0, 0, 0));

        lv_style_set_bg_opa(message_style_robot, 0);
        lv_style_set_bg_opa(message_style_user, 0);
        xSemaphoreGive(lvglMutex);
    }
}

void LvglDisplay::begin() {
    lv_init();
    tft.begin();
    ts.begin();

    static auto *buf1 = static_cast<lv_color_t *>(heap_caps_malloc(DRAW_BUF_SIZE * sizeof(lv_color_t),
                                                                   MALLOC_CAP_SPIRAM));
    if (buf1 == nullptr) {
        log_e("分配buf1内存失败");
    }
    lv_disp_draw_buf_init(&draw_buf, buf1, nullptr, DRAW_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = false;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    initMessageStyle();

    xTaskCreate([](void *ptr) {
        while (true) {
            if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
                lv_timer_handler();
                xSemaphoreGive(lvglMutex);
            }
            vTaskDelay(5);
        }
    }, "lvgl", 4096, nullptr, 1, nullptr);
}

// 更新首页聊天列表
void LvglDisplay::updateChatText(MessageRole messageRole, bool newLine, const std::string &text) {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        if (!newLine && last_message != nullptr) {
            lv_label_set_text(last_message, text.c_str());
            lv_obj_scroll_to_y(guider_ui.home_page_message_list, LV_COORD_MAX, LV_ANIM_ON);
            xSemaphoreGive(lvglMutex);
            return;
        }
        last_message = lv_list_add_text(guider_ui.home_page_message_list, text.c_str());
        lv_label_set_long_mode(last_message, LV_LABEL_LONG_WRAP);
        current_message_number++;
        if (messageRole == Robot) {
            lv_obj_add_style(last_message, message_style_robot, 0);
        } else {
            lv_obj_add_style(last_message, message_style_user, 0);
        }
        if (current_message_number > 20) {
            lv_obj_t *first_message = lv_obj_get_child(guider_ui.home_page_message_list, 0);
            if (first_message != nullptr) {
                lv_obj_del(first_message);
                current_message_number--;
            }
        }
        lv_obj_scroll_to_y(guider_ui.home_page_message_list, LV_COORD_MAX, LV_ANIM_ON);
        xSemaphoreGive(lvglMutex);
    }
}

void LvglDisplay::updateState(const std::string &state) {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        lv_label_set_text(guider_ui.home_page_header_state, state.c_str());
        xSemaphoreGive(lvglMutex);
    }
}

void LvglDisplay::updateTime(const std::string &time) {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        lv_label_set_text(guider_ui.home_page_header_time, time.c_str());
        xSemaphoreGive(lvglMutex);
    }
}

void LvglDisplay::updateWifiState(bool success) {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        if (success) {
            lv_obj_add_flag(guider_ui.home_page_header_wifi_no, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_clear_flag(guider_ui.home_page_header_wifi_no, LV_OBJ_FLAG_HIDDEN);
        }
        xSemaphoreGive(lvglMutex);
    }
}

void LvglDisplay::updateRecordingButtonState(bool recordingAllowed) {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        if (recordingAllowed) {
            lv_obj_add_flag(guider_ui.home_page_line_stop_recording, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_clear_flag(guider_ui.home_page_line_stop_recording, LV_OBJ_FLAG_HIDDEN);
        }
        xSemaphoreGive(lvglMutex);
    }
}

void LvglDisplay::updateRecordingButtonImage(bool isPlaying) {
    if (xSemaphoreTake(lvglMutex, portMAX_DELAY) == pdTRUE) {
        if (isPlaying) {
            lv_img_set_src(guider_ui.home_page_microphone, &_stop_alpha_40x40);
            lv_obj_add_flag(guider_ui.home_page_line_stop_recording, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_img_set_src(guider_ui.home_page_microphone, &_micphone_alpha_40x40);
        }
        xSemaphoreGive(lvglMutex);
    }
}
