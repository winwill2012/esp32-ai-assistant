#include <LLMAgent.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "Recording.h"

AsyncWebServer server(80);

#define HOST "openspeech.bytedance.com"
#define APP_ID "8988564775"
#define ACCESS_TOKEN "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94"

/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */
//DoubaoTTS ttsClient(I2S_NUM_0, 16000, "BV700_streaming", APP_ID, ACCESS_TOKEN,
//                    HOST, 443, "/api/v1/tts/ws_binary", 16, 17, 18);

DoubaoSTT sttClient(I2S_NUM_1, APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v2/asr", 39, 38, 37);

//LLMAgent agent("https://api.coze.cn/v3/chat", "7468218438402818082",
//               "pat_vM6yCGCIl7FRLJoUbncQ8ZxFl3TKjviXMI50Sq45RSJzhahbB2AhlLRS1vVRiUEq");
//
//RecordingManager recordingManager(sttClient);

[[noreturn]] void websocketLoopTask(void *ptr) {
    while (true) {
        sttClient.loop();
//        ttsClient.loop();
        vTaskDelay(1);
    }
}

void setup() {
    Serial.begin(115200);
    WiFiClass::mode(WIFI_MODE_STA);
    WiFi.begin("Xiaomi_E15A", "19910226");
//    WiFi.begin("SmartHome", "9jismart");
    while (!WiFi.isConnected()) {
        Serial.print(".");
        vTaskDelay(1000);
    }
    Serial.print("\nConnect WiFi success\nIP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("连接网络成功");
    Serial.printf("Default free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("  Psram free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    sttClient.begin();
//    ttsClient.begin();
    xTaskCreate(websocketLoopTask, "websocketLoopTask", 4096, nullptr, 1, nullptr);
//    ttsClient.synth(
//            "今天是 2 月 11 日，昆明晴转多云，最低温度 8℃ ，最高温度 19℃，西南风 3-4 级转小于 3 级。空气质量优，湿度适宜，阳光正好，很适合外出游玩、晒太阳，尽情享受惬意时光。");
    SPIFFS.begin(true);
}

void loop() {
    if (Serial.available()) {
        Serial.readStringUntil('\n');
        File file = SPIFFS.open("/test.pcm", FILE_READ);
        uint8_t buffer[4096];
        bool firstPacket = true;
        size_t size;
        while (file.available()) {
            size = file.read(buffer, 4096);
            sttClient.recognize(buffer, size, firstPacket, false);
            if (firstPacket) {
                firstPacket = false;
            }
        }
        sttClient.recognize(buffer, 0, firstPacket, true);
        Serial.println("数据包发送完毕");
        file.close();
    }
}
