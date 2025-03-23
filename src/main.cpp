#include <CozeLLMAgent.h>
#include <Settings.h>
#include <utils.h>
#include "Arduino.h"
#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "RecordingManager.h"
#include "LvglDisplay.h"
#include "TimeUpdater.h"
#include "AudioPlayer.h"

/**
 *  一定要记得修改WebSockets.h中的如下定义：
 *  #define WEBSOCKETS_MAX_DATA_SIZE (64 * 1024)
 */

void setup() {
    Serial.begin(115200);
    Settings::begin();
    LvglDisplay::begin();
    analogWrite(8, (int) (Settings::getScreenBrightness() * 2.55));  // 设置屏幕亮度

    auto wifiInfo = Settings::getWifiInfo();
    if (wifiInfo.first.empty() || wifiInfo.second.empty()) {
        log_e("No wifi configuration found");
        GlobalState::setState(NetworkConfigurationNotFound);
    } else {
        connectWifi(wifiInfo.first.c_str(), wifiInfo.second.c_str(), 20);
    }
    log_d("等待网络连接...");
    // 等待网络连接成功
    xEventGroupWaitBits(GlobalState::getEventGroup(), GlobalState::getEventBits({NetworkConnected}),
                        false, true, portMAX_DELAY);
    log_d("网络连接成功");
    GlobalState::setState(Sleep);
    DoubaoTTS ttsClient;
    CozeLLMAgent llmAgent(ttsClient);
    DoubaoSTT sttClient(llmAgent);

    RecordingManager recordingManager(sttClient);
    TimeUpdater::begin();
    AudioPlayer::begin();
    recordingManager.begin();
}

void loop() {

}
