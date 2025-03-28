#ifndef AI_ROBOT_UTILS_H
#define AI_ROBOT_UTILS_H

#include "Arduino.h"
#include <vector>
#include <WiFi.h>

std::string generateTaskId();

std::string getChipId(const char *prefix);

int32_t readInt32(const uint8_t *bytes);

std::string readString(const uint8_t *bytes, uint32_t length);

std::vector<uint8_t> uint32ToUint8Array(uint32_t size);

double calculateSoundRMS(const int16_t *buffer, size_t bufferSize);

std::pair<int, size_t> findMinIndexOfDelimiter(const String &input);

bool connectWifi(const char *ssid, const char *password, int maxRetries);

std::vector<uint8_t> int16ToUint8BigEndian(const std::vector<int16_t> &input);

std::vector<int16_t> uint8ToInt16BigEndian(const uint8_t *input, size_t size);

#endif
