#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "CosyVoiceTTS.h"

#define I2S_DOUT 16
#define I2S_BCLK 17
#define I2S_LRC 18

CosyVoiceTTS ttsClient(I2S_NUM_0, 16000, "longwan");

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin("Xiaomi_E15A", "19910226");
    while (!WiFi.isConnected()) {
        Serial.print(".");
        vTaskDelay(1000);
    }
    Serial.print("\n�����ɹ�\nIP��ַ: ");
    Serial.println(WiFi.localIP());
    ttsClient.begin("sk-08e0459170574c449f6b0b20442c896c", "dashscope.aliyuncs.com", 443,
                    "/api-ws/v1/inference", I2S_DOUT, I2S_BCLK, I2S_LRC);
}

void loop() {
    if (Serial.available()) {
        Serial.readStringUntil('\n');
        ttsClient.tts("��ð����������ר���ͷ�����ʲô�������ֱ�����Ұ�");
    }
}