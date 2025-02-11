#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "CosyVoiceTTS.h"

#define I2S_DOUT 16
#define I2S_BCLK 17
#define I2S_LRC 18

/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */
CosyVoiceTTS ttsClient(I2S_NUM_0, 16000, "BV001_streaming", "8988564775", "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94",
                       "openspeech.bytedance.com", 443, "/api/v1/tts/ws_binary", I2S_DOUT, I2S_BCLK, I2S_LRC);

void setup() {
    Serial.begin(115200);
    WiFiClass::mode(WIFI_MODE_STA);
    // WiFi.begin("Xiaomi_E15A", "19910226");
    WiFi.begin("SmartHome", "9jismart");
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
        // ttsClient.synth("这是消息" + String(micros()));
        ttsClient.synth("我与父亲不相见已二年余了，我最不能忘记的是他的背影。那年冬天，祖母死了，父亲的差使也交卸了，正是祸不单行的日子，我从北京到徐州，打算跟着父亲奔丧回家。到徐州见着父亲，看见满院狼藉的东西，又想起祖母，不禁簌簌地流下眼泪。父亲说，“事已如此，不必难过，好在天无绝人之路！”回家变卖典质，父亲还了亏空；又借钱办了丧事。这些日子，家中光景很是惨淡，一半为了丧事，一半为了父亲赋闲。丧事完毕，父亲要到南京谋事，我也要回北京念书，我们便同行。");
    }
}
