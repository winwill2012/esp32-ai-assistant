#include <LLMAgent.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "SPIFFS.h"

#define HOST "openspeech.bytedance.com"
#define APP_ID "8988564775"
#define ACCESS_TOKEN "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94"

/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */
DoubaoTTS ttsClient(I2S_NUM_0, 16000, "BV700_streaming", APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v1/tts/ws_binary", 16, 17, 18);

DoubaoSTT sttClient(I2S_NUM_1, APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v2/asr", 39, 38, 37);

LLMAgent agent("https://api.coze.cn/v3/chat", "7468218438402818082",
               "pat_vM6yCGCIl7FRLJoUbncQ8ZxFl3TKjviXMI50Sq45RSJzhahbB2AhlLRS1vVRiUEq");

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


    //    ttsClient.begin();
    // sttClient.begin();
    // Serial.println(esp_get_free_heap_size());
    // Serial.printf("DMA free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DMA));
    // Serial.printf("Default free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    // Serial.printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    //    ttsClient.synth(
    //            "今天是 2 月 11 日，昆明晴转多云，最低温度 8℃ ，最高温度 19℃，西南风 3-4 级转小于 3 级。空气质量优，湿度适宜，阳光正好，很适合外出游玩、晒太阳，尽情享受惬意时光。");
    // SPIFFS.begin(true);
}

//// 音频缓冲区大小
const size_t bufferSize = 1024;
uint8_t buffer[bufferSize];
size_t bytesRead;

void loop() {
    if (Serial.available()) {
        Serial.readStringUntil('\n');
        AgentResponse *response = agent.chat("心情不是很好，帮我把灯光颜色调暗一些");
        if (response == nullptr) {
            Serial.println("调用LLM Agent失败");
        } else {
            Serial.printf("cmd = %s content = %s response = %s emotion=%s\n",
                          response->cmd.c_str(), response->content.c_str(), response->emotion.c_str(),
                          response->response.c_str());
        }
        //        while (true) {
        //            esp_err_t err = i2s_read(I2S_NUM_1, buffer, bufferSize, &bytesRead, portMAX_DELAY);
        //            if (err == ESP_OK) {
        //                Serial.printf("Read %d bytes of audio data\n", bytesRead);
        //                sttClient.stt(buffer, bytesRead, false);
        //            } else {
        //                Serial.printf("Failed reading audio data: %d\n", err);
        //            }
        //        }
        // File file = SPIFFS.open("/test.MP3", FILE_READ);
        // if (!file) {
        //     Serial.println("打开文件失败");
        //     return;
        // } else {
        //     Serial.println("打开文件成功");
        // }
        // uint8_t buff[1024];
        // size_t total = 0;
        // size_t read;
        // while (file.available() > 0) {
        //     read = file.read(buff, 1024);
        //     sttClient.recognize(buff, read, false);
        //     total += read;
        // }
        // Serial.printf("一共成功读取%d字节数据\n", total);
        // sttClient.recognize(buff, 0, true);
    }
}
