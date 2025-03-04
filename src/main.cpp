#include <CozeLLMAgent.h>
#include <Settings.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "Recording.h"
#include "GlobalState.h"
#include "Utils.h"
//#include <lvgl.h>
//#include "FT6336.h"
//#include "gui/gui_guider.h"
//#include "gui/events_init.h"

#define HOST "openspeech.bytedance.com"
#define APP_ID "8988564775"
#define ACCESS_TOKEN "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94"

//#define TFT_HOR_RES   320
//#define TFT_VER_RES   480
//#define I2C_SDA 12
//#define I2C_SCL 13
//#define RST_N_PIN 10
//#define INT_N_PIN 9
//#define TFT_ROTATION  LV_DISPLAY_ROTATION_0
//#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
//
//uint32_t draw_buf[DRAW_BUF_SIZE / 4];
//FT6336 ts(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN, TFT_HOR_RES, TFT_VER_RES);

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

//static uint32_t my_tick(void) {
//    return millis();
//}
//
//void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
//    ts.read();
//    if (ts.isTouched) {
//        data->point.x = ts.points[0].x;
//        data->point.y = ts.points[0].y;
//        data->state = LV_INDEV_STATE_PR;
//    } else {
//        data->state = LV_INDEV_STATE_REL;
//    }
//}

//lv_ui guider_ui;

void setup() {
    Serial.begin(115200);
    Settings::begin();
    //    lv_init();
    //    lv_tick_set_cb(my_tick);
    //    ts.begin();
    //
    //    lv_display_t *disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    //    lv_display_set_rotation(disp, TFT_ROTATION);
    //
    //    lv_indev_t *indev = lv_indev_create();
    //    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    //    lv_indev_set_read_cb(indev, my_touchpad_read);

    //    Serial.println("开始渲染LVGL界面");
    //    setup_ui(&guider_ui);
    //    events_init(&guider_ui);

    Serial.println("开始连接wifi");
    WiFiClass::mode(WIFI_MODE_STA);
    // WiFi.begin("Xiaomi_E15A", "19910226");
    WiFi.begin("SmartHome", "9jismart");
    while (!WiFi.isConnected()) {
        Serial.print(".");
        vTaskDelay(1000);
    }
    Serial.println("连接网络成功");
    Serial.printf("Default free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("  PSRAM free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

    // recordingManager.begin();
}

void loop() {
    //    lv_timer_handler(); /* let the GUI do its work */
    //    delay(5); /* let this time pass */
    const std::vector<WifiInfo> list = Settings::getWifiList();
    Serial.println("WiFi列表如下: ");
    for (const auto &wifiInfo: list) {
        Serial.printf("[%s] [%d] [%d]\n", wifiInfo._ssid.c_str(), wifiInfo._rssi, wifiInfo._encrypted);
    }
    Serial.println("WiFi扫描结束");
}
