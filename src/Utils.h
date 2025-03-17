#ifndef AI_ROBOT_UTILS_H
#define AI_ROBOT_UTILS_H

#include <GlobalState.h>

#include "Arduino.h"
#include <vector>
#include <WiFi.h>

std::string generateTaskId();

std::string getChipId(const char *prefix);

int32_t parseInt32(const uint8_t *bytes);

std::string parseString(const uint8_t *bytes, uint32_t length);

std::vector<uint8_t> int2Array(uint32_t size);

double calculateSoundRMS(const uint8_t *buffer, size_t bufferSize);

std::pair<int, size_t> findMinIndexOfDelimiter(const String &input);

bool connectWifi(const String &ssid, const String &password, int maxRetries);

std::vector<uint8_t> int16ToUint8BigEndian(const std::vector<int16_t> &input);

std::vector<int16_t> uint8ToInt16BigEndian(const std::vector<uint8_t> &input);
#endif
