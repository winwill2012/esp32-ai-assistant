#include <LLMAgent.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include <AsyncTCP.h>
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

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

    ttsClient.begin();
    sttClient.begin();

    Serial.printf("Default free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("  Psram free size =  %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
//    ttsClient.synth(
//            "今天是 2 月 11 日，昆明晴转多云，最低温度 8℃ ，最高温度 19℃，西南风 3-4 级转小于 3 级。空气质量优，湿度适宜，阳光正好，很适合外出游玩、晒太阳，尽情享受惬意时光。");
    SPIFFS.begin(true);
    // 处理文件请求
    server.on("/recording.wav", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/recording.wav", "audio/wav");
    });

    // 启动服务器
    server.begin();
    Serial.println("HTTP server started");
}

const size_t bufferSize = 4096;
uint8_t buffer[bufferSize];
size_t bytesRead;

void loop() {
    if (Serial.available()) {
        Serial.readStringUntil('\n');
        uint32_t beginTime = millis();
        bool firstPacket = true;
        while (true) {
            File file = SPIFFS.open("/recording.wav", FILE_WRITE);
            esp_err_t err = i2s_read(I2S_NUM_1, buffer, bufferSize, &bytesRead, portMAX_DELAY);
            if (err == ESP_OK) {
                Serial.printf("Read %d bytes of audio data\n", bytesRead);
                file.write(buffer, bytesRead);
                for (int i = 0; i < 50; i++) {
                    Serial.printf("%0x ", buffer[i]);
                }
                Serial.println();
                if (millis() - beginTime > 10000) {
                    sttClient.recognize(buffer, bytesRead, firstPacket, true);
                    file.close();
                    break;
                } else {
                    sttClient.recognize(buffer, bytesRead, firstPacket, false);
                    if (firstPacket) {
                        firstPacket = false;
                    }
                }
            } else {
                Serial.printf("Failed reading audio data: %d\n", err);
            }
        }
    }
}
