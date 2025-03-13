#include <CozeLLMAgent.h>
#include <Settings.h>
#include <utils.h>
#include <driver/i2s.h>
#include "Arduino.h"
#include "WiFi.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "Recording.h"
#include "LvglDisplay.h"
#include "TimeUpdater.h"
#include "AudioPlayer.h"
#include "GlobalState.h"

#define HOST "openspeech.bytedance.com"
#define APP_ID "8988564775"
#define ACCESS_TOKEN "dsWgV1rCvxiinw_H2clmJuAI-O1D8P94"
//
/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */
DoubaoTTS ttsClient(APP_ID, ACCESS_TOKEN, HOST, 443, "/api/v1/tts/ws_binary");

CozeLLMAgent llmAgent(ttsClient, "https://api.coze.cn/v3/chat?conversation_id=", "7468218438402818082",
                      "pat_A5RMsa9C3wavFPz9BiTHnQtm0G3AmYZkhSSZ5vkHANDKWnX1yyx7wss7hsAnUMt4");

DoubaoSTT sttClient(llmAgent, I2S_NUM_1, APP_ID, ACCESS_TOKEN,
                    HOST, 443, "/api/v2/asr", 1, 42, 2);

RecordingManager recordingManager(sttClient);

void setup() {
    Serial.begin(115200);
    Settings::begin();
    LvglDisplay::begin();

    if (connectWifi("Xiaomi_E15A", "19910226", 10)) {
        TimeUpdater::begin();
        AudioPlayer::begin();
        recordingManager.begin();
    }
}

void loop() {
}
