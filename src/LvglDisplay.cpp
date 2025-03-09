#include "LvglDisplay.h"

#define TFT_WIDTH   320
#define TFT_HEIGHT   480
#define I2C_SDA 10
#define I2C_SCL 13
#define RST_N_PIN 9
#define INT_N_PIN 12
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10)

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[DRAW_BUF_SIZE];
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
        Serial.printf("点击: %d, %d\n", data->point.x, data->point.y);
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

lv_ui guider_ui;
lv_style_t *LvglDisplay::message_style_robot = (lv_style_t *) malloc(sizeof(lv_style_t));
lv_style_t *LvglDisplay::message_style_user = (lv_style_t *) malloc(sizeof(lv_style_t));

void LvglDisplay::begin() {
    lv_init();
    tft.begin();
    ts.begin();

    lv_disp_draw_buf_init(&draw_buf, buf1, nullptr, DRAW_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = true;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    lv_style_init(message_style_robot);
    lv_style_init(message_style_user);

    lv_style_set_text_font(message_style_robot, &lv_customer_font_Siyuan_ExtraLight_14);
    lv_style_set_text_font(message_style_user, &lv_customer_font_Siyuan_ExtraLight_14);

    lv_style_set_text_align(message_style_robot, LV_TEXT_ALIGN_LEFT);
    lv_style_set_text_align(message_style_user, LV_TEXT_ALIGN_RIGHT);

    lv_style_set_text_color(message_style_robot, lv_color_make(50, 50, 50));
    lv_style_set_text_color(message_style_user, lv_color_make(0, 0, 0));

    lv_style_set_bg_opa(message_style_robot, 0);
    lv_style_set_bg_opa(message_style_user, 0);

    xTaskCreate([](void *ptr) {
        while (true) {
            lv_timer_handler();
            vTaskDelay(5);
        }
    }, "lvgl", 4096, nullptr, 1, nullptr);
}

void LvglDisplay::updateChatText(MessageRole messageRole, const std::string &text) {
    lv_obj_t *message = lv_list_add_text(guider_ui.home_page_message_list, text.c_str());
    _lv_obj_t *label = lv_obj_get_child(message, 0);
    if (label != nullptr) {
        lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    }
    if (messageRole == Robot) {
        lv_img_set_src(guider_ui.home_page_header_icon, &_robot_alpha_26x26);
        lv_obj_add_style(message, message_style_robot, 0);
    } else {
        lv_img_set_src(guider_ui.home_page_header_icon, &_user_alpha_26x26);
        lv_obj_add_style(message, message_style_user, 0);
    }
}

void LvglDisplay::updateState(const std::string &state) {
    lv_label_set_text(guider_ui.home_page_header_state, state.c_str());
}

void LvglDisplay::updateTime(const std::string &time) {
    lv_label_set_text(guider_ui.home_page_header_time, time.c_str());
}



