#include "Settings.h"
#include "SPIFFS.h"
#include <WiFi.h>
#include <map>
#include "ArduinoJson.h"

Preferences Settings::preferences;
String Settings::currentVoice;
String Settings::currentPersona;
int Settings::currentScreenBrightness;
float Settings::currentSpeakSpeedRatio;
float Settings::currentSpeakVolumeRatio;
double Settings::recordingRmsThreshold;
int Settings::speakPauseDuration;
std::map<std::string, std::string> Settings::voiceMap = std::map<std::string, std::string>(); // <声音，声音值>列表
std::map<std::string, std::string> Settings::personaMap = std::map<std::string, std::string>(); // <人设，botId>列表
std::string Settings::doubaoAppId;
std::string Settings::doubaoAccessToken;
std::string Settings::cozeToken;
std::string Settings::wifiSsid;
std::string Settings::wifiPassword;
std::vector<WifiInfo> Settings::scannedWifiList = std::vector<WifiInfo>();

void Settings::begin() {
    if (!SPIFFS.begin(true)) {
        log_e("an Error has occurred while mounting SPIFFS");
        ESP.restart();
    }
    File file = SPIFFS.open("/settings.json", "r");
    if (!file) {
        log_e("failed to open settings.json file for reading");
        ESP.restart();
    }
    JsonDocument doc;
    const DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        log_e("deserialize settings.json failed: %s", error.c_str());
        ESP.restart();
    }

    preferences.begin(SETTINGS_NAMESPACE, false);
    currentSpeakVolumeRatio = preferences.getFloat(SETTING_VOLUME_RATIO, doc["system"]["volumeRatio"].as<float>());
    currentSpeakSpeedRatio = preferences.getFloat(SETTING_SPEED_RATIO, doc["system"]["speakSpeed"].as<float>());
    currentVoice = preferences.getString(SETTING_VOICE_TYPE, doc["system"]["voiceType"].as<String>());
    currentPersona = preferences.getString(SETTING_PERSONA, doc["system"]["persona"].as<String>());
    recordingRmsThreshold = preferences.getDouble(SETTING_RECORDING_RMS_THRESHOLD,
                                                  doc["system"]["recordingRmsThreshold"].as<double>());
    speakPauseDuration = preferences.getInt(SETTING_SPEAK_PAUSE_DURATION,
                                            doc["system"]["speakPauseDuration"].as<int>());
    wifiSsid = preferences.getString(SETTING_WIFI_SSID, "").c_str();
    wifiPassword = preferences.getString(SETTING_WIFI_PASSWORD, "").c_str();
    currentScreenBrightness = preferences.getInt(SETTING_SCREEN_BRIGHTNESS, 80);
    preferences.end();

    doubaoAppId = doc["doubao"]["appId"].as<std::string>();
    doubaoAccessToken = doc["doubao"]["accessToken"].as<std::string>();
    cozeToken = doc["coze"]["token"].as<std::string>();
    const JsonArray voiceListJsonArray = doc["voiceList"].as<JsonArray>();
    for (JsonObject item: voiceListJsonArray) {
        voiceMap[item["name"].as<std::string>()] = item["value"].as<std::string>();
    }
    const JsonArray personaListJsonArray = doc["coze"]["personaList"].as<JsonArray>();
    for (JsonObject item: personaListJsonArray) {
        personaMap[item["name"].as<std::string>()] = item["botId"].as<std::string>();
    }
    show();
}

void Settings::show() {
    log_i("------------------------settings info begin---------------------------------");
    log_i("currentSpeakVolumeRatio: %f", currentSpeakVolumeRatio);
    log_i(" currentSpeakSpeedRatio: %f", currentSpeakSpeedRatio);
    log_i("           currentVoice: %s", currentVoice.c_str());
    log_i("         currentPersona: %s", currentPersona.c_str());
    log_i("  recordingRmsThreshold: %f", recordingRmsThreshold);
    log_i("     speakPauseDuration: %d ms", speakPauseDuration);
    log_i("            doubaoAppId: %s", doubaoAppId.c_str());
    log_i("      doubaoAccessToken: %s", doubaoAccessToken.c_str());
    log_i("              cozeToken: %s", cozeToken.c_str());
    log_i("               wifiSsid: %s", wifiSsid.c_str());
    log_i("           wifiPassword: %s", wifiPassword.c_str());
    log_i("         all voice list: ");
    for (const auto &pair: voiceMap) {
        log_i("%s [%s]", pair.first.c_str(), pair.second.c_str());
    }
    log_i("       all persona list: ");
    for (const auto &pair: personaMap) {
        log_i("%s [%s]", pair.first.c_str(), pair.second.c_str());
    }
    log_i("------------------------settings info end---------------------------------");
}

/**
*  扫描设备周围WiFi列表
*/
std::vector<WifiInfo> Settings::getWifiList(const bool refresh) {
    if (!refresh) {
        return scannedWifiList;
    }
    log_d("start scan wifi...");
    const int16_t number = WiFi.scanNetworks();
    if (number == 0) {
        return {};
    }
    log_d("scan wifi completed, found %d ap", number);
    scannedWifiList.clear();
    for (int i = 0; i < number; i++) {
        scannedWifiList.emplace_back(WiFi.SSID(i), WiFi.RSSI(i), WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
    }
    return scannedWifiList;
}

String Settings::getCurrentVoice() {
    return currentVoice;
}


void Settings::setCurrentVoice(const String &voice) {
    currentVoice = voice;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putString(SETTING_VOICE_TYPE, voice);
    preferences.end();
}

String Settings::getCurrentPersona() {
    return currentPersona;
}

void Settings::setCurrentPersona(const String &persona) {
    currentPersona = persona;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putString(SETTING_PERSONA, persona);
    preferences.end();
}

float Settings::getCurrentSpeakVolumeRatio() {
    return currentSpeakVolumeRatio;
}

void Settings::setCurrentSpeakVolumeRatio(float speakVolumeRatio) {
    currentSpeakVolumeRatio = speakVolumeRatio;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putFloat(SETTING_VOLUME_RATIO, speakVolumeRatio);
    preferences.end();
}

float Settings::getCurrentSpeakSpeedRatio() {
    return currentSpeakSpeedRatio;
}

void Settings::setCurrentSpeakSpeedRatio(float speakSpeedRatio) {
    currentSpeakSpeedRatio = speakSpeedRatio;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putFloat(SETTING_SPEED_RATIO, speakSpeedRatio);
    preferences.end();
}

int Settings::getSpeakPauseDuration() {
    return speakPauseDuration;
}

void Settings::setSpeakPauseDuration(int pauseDuration) {
    speakPauseDuration = pauseDuration;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putInt(SETTING_SPEAK_PAUSE_DURATION, pauseDuration);
    preferences.end();
}

double Settings::getRecordingRmsThreshold() {
    return recordingRmsThreshold;
}

void Settings::setRecordingRmsThreshold(double rmsThreshold) {
    recordingRmsThreshold = rmsThreshold;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putDouble(SETTING_RECORDING_RMS_THRESHOLD, rmsThreshold);
    preferences.end();
}

void Settings::setWifiInfo(const std::string &ssid, const std::string &password) {
    wifiSsid = ssid;
    wifiPassword = password;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putString(SETTING_WIFI_SSID, ssid.c_str());
    preferences.putString(SETTING_WIFI_PASSWORD, password.c_str());
    preferences.end();
}

std::pair<std::string, std::string> Settings::getWifiInfo() {
    return std::make_pair(wifiSsid, wifiPassword);
}

std::map<std::string, std::string> Settings::getVoiceMap() {
    return voiceMap;
}

std::map<std::string, std::string> Settings::getPersonaMap() {
    return personaMap;
}

std::string Settings::getDoubaoAppId() {
    return doubaoAppId;
}

std::string Settings::getDoubaoAccessToken() {
    return doubaoAccessToken;
}

std::string Settings::getCozeToken() {
    return cozeToken;
}

int Settings::getScreenBrightness() {
    return currentScreenBrightness;
}

void Settings::setScreenBrightness(int brightness) {
    currentScreenBrightness = brightness;
    analogWrite(8, static_cast<int>(currentScreenBrightness * 2.55));
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putInt(SETTING_SCREEN_BRIGHTNESS, brightness);
    preferences.end();
}
