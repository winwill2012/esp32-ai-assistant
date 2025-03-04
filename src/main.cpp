#include <CozeLLMAgent.h>
#include <Settings.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "Recording.h"
#include <lvgl.h>
#include "FT6336.h"
#include "gui/gui_guider.h"
#include "gui/events_init.h"
#include "../lib/TFT_eSPI/TFT_eSPI.h"

#define HOST "openspeech.bytedance.com"
#define APP_ID "8988564775"
#define ACCESS_TOKEN "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94"

#define TFT_WIDTH   320
#define TFT_HEIGHT   480
#define I2C_SDA 12
#define I2C_SCL 13
#define RST_N_PIN 10
#define INT_N_PIN 9
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10)

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[DRAW_BUF_SIZE];

FT6336 ts(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN, TFT_WIDTH, TFT_HEIGHT);
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */
DoubaoTTS ttsClient(I2S_NUM_0, 16000, APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v1/tts/ws_binary", 38, 39, 40);

CozeLLMAgent llmAgent(ttsClient, "https://api.coze.cn/v3/chat?conversation_id=", "7468218438402818082",
                      "pat_vM6yCGCIl7FRLJoUbncQ8ZxFl3TKjviXMI50Sq45RSJzhahbB2AhlLRS1vVRiUEq");

DoubaoSTT sttClient(llmAgent, I2S_NUM_1, APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v2/asr", 1, 42, 2);

RecordingManager recordingManager(sttClient);

void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *) &color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_drv_t *indev, lv_indev_data_t *data) {
    ts.read();
    if (ts.isTouched) {
        data->point.x = ts.points[0].x;
        data->point.y = ts.points[0].y;
        data->state = LV_INDEV_STATE_PR;
        Serial.printf("点击: %d, %d\n", data->point.x, data->point.y);
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

lv_ui guider_ui;

void setup() {
    Serial.begin(115200);
    Settings::begin();

    lv_init();
    tft.begin();
    ts.begin();

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, DRAW_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    Serial.println("开始渲染LVGL");
    setup_ui(&guider_ui);
    events_init(&guider_ui);

    WiFiClass::mode(WIFI_MODE_STA);
    WiFi.begin("Xiaomi_E15A", "19910226");
    while (!WiFi.isConnected()) {
        Serial.print(".");
        vTaskDelay(1000);
    }
    Serial.println("连接网络成功");
    Serial.printf("Default free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("  PSRAM free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    xTaskCreate([](void *ptr) {
        while (true) {
            lv_timer_handler();
            vTaskDelay(5);
        }
    }, "lvgl", 4096, nullptr, 1, nullptr);
    recordingManager.begin();
}

void loop() {
}
