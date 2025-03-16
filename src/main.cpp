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
    Settings::setCurrentSpeakVolumeRatio(10);
    LvglDisplay::begin();

    DoubaoTTS ttsClient;
    CozeLLMAgent llmAgent(ttsClient);
    //DoubaoBigModelSTT sttClient(llmAgent);
    DoubaoSTT sttClient(llmAgent);

    RecordingManager recordingManager(sttClient);
    if (connectWifi("Xiaomi_E15A", "19910226", 10)) {
        TimeUpdater::begin();
        AudioPlayer::begin();
        recordingManager.begin();
    }

}

void loop() {
}
