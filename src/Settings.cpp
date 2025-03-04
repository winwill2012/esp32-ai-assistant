#include "Settings.h"

#include <WiFi.h>

Preferences Settings::preferences;
String Settings::_voiceType;
String Settings::_emotion;
float Settings::_speedRatio;
float Settings::_volumeRatio;
double Settings::_backgroundNoiseRMS;
int Settings::_recordingSilenceTime;

void Settings::begin() {
    preferences.begin(SETTINGS_NAMESPACE, false);
    _volumeRatio = preferences.getFloat(SETTING_VOLUME_RATIO, 0.7);
    _speedRatio = preferences.getFloat(SETTING_SPEED_RATIO, 1.0);
    _voiceType = preferences.getString(SETTING_VOICE_TYPE, "BV700_streaming");
    _emotion = preferences.getString(SETTING_EMOTION, "happy");
    _backgroundNoiseRMS = preferences.getDouble(SETTING_BACKGROUND_NOISE_RMS, 5000);
    _recordingSilenceTime = preferences.getInt(SETTING_RECORDING_SILENCE_TIME, 1000);
    preferences.end();
}

float Settings::getVolumeRatio() {
    return _volumeRatio;
}

String Settings::getVoiceType() {
    return _voiceType;
}

String Settings::getEmotion() {
    return _emotion;
}

float Settings::getSpeedRatio() {
    return _speedRatio;
}

void Settings::setVolumeRatio(const float volumeRatio) {
    _volumeRatio = volumeRatio;
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putFloat(SETTING_VOLUME_RATIO, volumeRatio);
    preferences.end();
}

void Settings::setVoiceType(const String &voiceType) {
    _voiceType = voiceType;
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putString(SETTING_VOICE_TYPE, voiceType);
    preferences.end();
}

void Settings::setEmotion(const String &emotion) {
    _emotion = emotion;
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putString(SETTING_EMOTION, emotion);
    preferences.end();
}

void Settings::setSpeedRatio(const float speedRatio) {
    _speedRatio = speedRatio;
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putFloat(SETTING_SPEED_RATIO, speedRatio);
    preferences.end();
}

void Settings::setRecordingSilenceTime(const int recordingSilenceTime) {
    _recordingSilenceTime = recordingSilenceTime;
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putInt(SETTING_RECORDING_SILENCE_TIME, recordingSilenceTime);
    preferences.end();
}

int Settings::getRecordingSilenceTime() {
    return _recordingSilenceTime;
}

double Settings::getBackgroundNoiseRMS() {
    return _backgroundNoiseRMS;
}

void Settings::setBackgroundNoiseRMS(const double backgroundNoiseRMS) {
    _backgroundNoiseRMS = backgroundNoiseRMS;
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putDouble(SETTING_BACKGROUND_NOISE_RMS, backgroundNoiseRMS);
    preferences.end();
}

/**
*  扫描设备周围WiFi列表
*/
std::vector<WifiInfo> Settings::getWifiList() {
    const int16_t number = WiFi.scanNetworks();
    if (number == 0) {
        return {};
    }
    std::vector<WifiInfo> list;
    for (int i = 0; i < number; i++) {
        list.emplace_back(WiFi.SSID(i), WiFi.RSSI(i), WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
    }
    return list;
}
