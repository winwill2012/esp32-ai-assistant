#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "CosyVoiceTTS.h"

#define I2S_DOUT 16
#define I2S_BCLK 17
#define I2S_LRC 18

CosyVoiceTTS ttsClient(I2S_NUM_0, 16000, "BV001_streaming", "8988564775", "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94",
                       "openspeech.bytedance.com", 443, "/api/v1/tts/ws_binary", I2S_DOUT, I2S_BCLK, I2S_LRC);

void setup() {
    Serial.begin(115200);
    WiFiClass::mode(WIFI_MODE_STA);
    WiFi.begin("Xiaomi_E15A", "19910226");
    while (!WiFi.isConnected()) {
        Serial.print(".");
        vTaskDelay(1000);
    }
    Serial.print("\nConnect WiFi success\nIP address: ");
    Serial.println(WiFi.localIP());
    ttsClient.begin();
}

void loop() {
    if (Serial.available()) {
        Serial.readStringUntil('\n');
        ttsClient.synth("这是消息" + String(micros()));
    }
}
