#include "Settings.h"
#include "SPIFFS.h"
#include <WiFi.h>
#include <map>
#include "ArduinoJson.h"

Preferences Settings::preferences;
String Settings::currentVoice;
String Settings::currentPersona;
float Settings::currentSpeakSpeedRatio;
float Settings::currentSpeakVolumeRatio;
double Settings::recordingRmsThreshold;
int Settings::speakPauseDuration;
std::map<std::string, std::string> Settings::voiceMap = std::map<std::string, std::string>();    // <声音，声音值>列表
std::map<std::string, std::string> Settings::personaMap = std::map<std::string, std::string>();  // <人设，botId>列表
std::string Settings::doubaoAppId;
std::string Settings::doubaoAccessToken;
std::string Settings::cozeToken;
std::vector<WifiInfo> Settings::scannedWifiList = std::vector<WifiInfo>();

void Settings::begin() {
    if (!SPIFFS.begin(true)) {
        log_e("An Error has occurred while mounting SPIFFS");
        ESP.restart();
    }
    File file = SPIFFS.open("/settings.json", "r");
    if (!file) {
        log_e("Failed to open settings.json file for reading");
        ESP.restart();
    }
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
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
    preferences.end();

    doubaoAppId = doc["doubao"]["appId"].as<std::string>();
    doubaoAccessToken = doc["doubao"]["accessToken"].as<std::string>();
    cozeToken = doc["coze"]["token"].as<std::string>();
    JsonArray voiceListJsonArray = doc["voiceList"].as<JsonArray>();
    for (JsonObject item: voiceListJsonArray) {
        voiceMap[item["name"].as<std::string>()] = item["value"].as<std::string>();
    }
    JsonArray personaListJsonArray = doc["coze"]["personaList"].as<JsonArray>();
    for (JsonObject item: personaListJsonArray) {
        personaMap[item["name"].as<std::string>()] = item["botId"].as<std::string>();
    }
    show();
    TimerHandle_t scanWifiTimer = xTimerCreate("scanWifi", pdMS_TO_TICKS(5 * 60 * 1000), true, nullptr, [](void *ptr) {
        int16_t scanResult = WiFi.scanNetworks(true);
        while (true) {
            if (scanResult == WIFI_SCAN_FAILED) {
                break;
            } else if (scanResult == WIFI_SCAN_RUNNING) {
                vTaskDelay(pdMS_TO_TICKS(1000));
            } else if (scanResult >= 0) {
                scannedWifiList.clear();
                for (int i = 0; i < scanResult; i++) {
                    scannedWifiList.emplace_back(WiFi.SSID(i), WiFi.RSSI(i),
                                                 WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
                }
                break;
            }
        }
    });
    if (scanWifiTimer != nullptr) {
        xTimerStart(scanWifiTimer, 0);
    }
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
std::vector<WifiInfo> Settings::getWifiList(bool refresh) {
    if (!refresh) {
        return scannedWifiList;
    }
    const int16_t number = WiFi.scanNetworks();
    if (number == 0) {
        return {};
    }
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
    Settings::currentVoice = voice;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putString(SETTING_VOICE_TYPE, voice);
    preferences.end();
}

String Settings::getCurrentPersona() {
    return currentPersona;
}

void Settings::setCurrentPersona(const String &persona) {
    Settings::currentPersona = persona;
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
    log_e("设置说话语速: %f", speakSpeedRatio);
    currentSpeakSpeedRatio = speakSpeedRatio;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putFloat(SETTING_SPEED_RATIO, speakSpeedRatio);
    preferences.end();
}

int Settings::getSpeakPauseDuration() {
    return speakPauseDuration;
}

void Settings::setSpeakPauseDuration(int pauseDuration) {
    log_e("设置录音停顿时间: %d ms", pauseDuration);
    Settings::speakPauseDuration = pauseDuration;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putInt(SETTING_SPEAK_PAUSE_DURATION, pauseDuration);
    preferences.end();
}

double Settings::getRecordingRmsThreshold() {
    return recordingRmsThreshold;
}

void Settings::setRecordingRmsThreshold(double rmsThreshold) {
    Settings::recordingRmsThreshold = rmsThreshold;
    preferences.begin(SETTINGS_NAMESPACE);
    preferences.putDouble(SETTING_RECORDING_RMS_THRESHOLD, rmsThreshold);
    preferences.end();
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

