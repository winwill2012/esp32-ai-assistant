#include <LLMAgent.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
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
DoubaoTTS ttsClient(I2S_NUM_0, 16000, "BV700_streaming", APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v1/tts/ws_binary", 38, 39, 40);

LLMAgent llmAgent(ttsClient, "https://api.coze.cn/v3/chat?conversation_id=", "7468218438402818082",
                  "pat_vM6yCGCIl7FRLJoUbncQ8ZxFl3TKjviXMI50Sq45RSJzhahbB2AhlLRS1vVRiUEq");

DoubaoSTT sttClient(llmAgent, I2S_NUM_1, APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v2/asr", 1, 42, 2);

RecordingManager recordingManager(sttClient);

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

    recordingManager.beginRecording();
}

void loop() {
}
