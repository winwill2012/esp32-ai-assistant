#ifndef IOT_AI_CONTROLLER_SETTINGS_H
#define IOT_AI_CONTROLLER_SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>
#include <utility>
#include <vector>

#define SETTINGS_NAMESPACE   "settings"
#define SETTING_VOLUME_RATIO "volumeRatio"
#define SETTING_SPEED_RATIO  "speedRatio"
#define SETTING_VOICE_TYPE   "voiceType"
#define SETTING_EMOTION      "emotion"

struct WifiInfo {
    WifiInfo(String ssid, const int rssi, const bool encrypted): _ssid(std::move(ssid)),
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

    static float getVolumeRatio();

    static String getVoiceType();

    static String getEmotion();

    static float getSpeedRatio();

    static void setVolumeRatio(float volumeRatio);

    static void setVoiceType(const String &voiceType);

    static void setEmotion(const String &emotion);

    static void setSpeedRatio(float speedRatio);

    static std::vector<WifiInfo> getWifiList();

private:
    // 发音人
    static String _voiceType;
    // 情绪
    static String _emotion;
    // 音量
    static float _volumeRatio;
    // 说话语速
    static float _speedRatio;

    static Preferences preferences;
};


#endif //IOT_AI_CONTROLLER_SETTINGS_H
