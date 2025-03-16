#ifndef IOT_AI_CONTROLLER_SETTINGS_H
#define IOT_AI_CONTROLLER_SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>
#include <vector>
#include <map>

#define SETTINGS_NAMESPACE                  "settings"
#define SETTING_VOLUME_RATIO                "volumeRatio"
#define SETTING_SPEED_RATIO                 "speedRatio"
#define SETTING_VOICE_TYPE                  "voiceType"
#define SETTING_PERSONA                     "persona"
#define SETTING_SPEAK_PAUSE_DURATION        "pauseDur"
#define SETTING_RECORDING_RMS_THRESHOLD     "rmsThreshold"

struct WifiInfo {
    WifiInfo(String ssid, const int rssi, const bool encrypted) : _ssid(std::move(ssid)),
                                                                  _rssi(rssi),
                                                                  _encrypted(encrypted) {
    }

    String _ssid; // WiFi名称
    int _rssi; // WiFi信号强度
    bool _encrypted; // 是否需要密码
};

class Settings {
public:
    static void begin();

    static void show();

    static std::vector<WifiInfo> getWifiList(bool refresh);

    static String getCurrentVoice();

    static void setCurrentVoice(const String &voice);

    static String getCurrentPersona();

    static std::map<std::string, std::string> getVoiceMap();

    static std::map<std::string, std::string> getPersonaMap();

    static std::string getDoubaoAppId();

    static std::string getDoubaoAccessToken();

    static std::string getCozeToken();

    static void setCurrentPersona(const String &persona);

    static float getCurrentSpeakVolumeRatio();

    static void setCurrentSpeakVolumeRatio(float speakVolumeRatio);

    static float getCurrentSpeakSpeedRatio();

    static void setCurrentSpeakSpeedRatio(float speakSpeedRatio);

    static int getSpeakPauseDuration();

    static void setSpeakPauseDuration(int pauseDuration);

    static double getRecordingRmsThreshold();

    static void setRecordingRmsThreshold(double rmsThreshold);

private:
    static String currentVoice;   // 当前设置的发音人
    static String currentPersona; // 当前设置的人设
    static float currentSpeakVolumeRatio;                     // 当前设置的音量
    static float currentSpeakSpeedRatio;                      // 当前设置的说话语速

    // 每一次录音的静默时间，单位ms，超过该时间则认为本次录音已完成
    static int speakPauseDuration;
    static double recordingRmsThreshold; // 录音RMS阈值
    static std::map<std::string, std::string> voiceMap;    // <声音，声音值>
    static std::map<std::string, std::string> personaMap;  // <人设，botId>
    static std::string doubaoAppId;
    static std::string doubaoAccessToken;
    static std::string cozeToken;
    static std::vector<WifiInfo> scannedWifiList;        // 已扫描的wifi列表
    static Preferences preferences;
};

#endif //IOT_AI_CONTROLLER_SETTINGS_H
