#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "CosyVoiceTTS.h"

#define I2S_DOUT 16
#define I2S_BCLK 17
#define I2S_LRC 18
#define ALIYUN_SK "sk-08e0459170574c449f6b0b20442c896c"
#define ALIYUN_WS_HOST "dashscope.aliyuncs.com"
#define COSY_VOICE_URL "/api-ws/v1/inference"
CosyVoiceTTS ttsClient(I2S_NUM_0, 16000, "longwan");

void setup() {
    Serial.begin(115200);
    WiFiClass::mode(WIFI_MODE_STA);
    WiFi.begin("SmartHome", "9jismart");
    while (!WiFi.isConnected()) {
        Serial.print(".");
        vTaskDelay(1000);
    }
    Serial.print("\nConnect WiFi success\nIP address: ");
    Serial.println(WiFi.localIP());
    ttsClient.begin(ALIYUN_SK, ALIYUN_WS_HOST, 443, COSY_VOICE_URL
                    , I2S_DOUT, I2S_BCLK, I2S_LRC);
}

void loop() {
    if (Serial.available()) {
        Serial.readStringUntil('\n');
        ttsClient.tts("这是消息" + String(micros()));
    }
}
