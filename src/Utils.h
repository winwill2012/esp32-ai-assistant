#ifndef AI_ROBOT_UTILS_H
#define AI_ROBOT_UTILS_H

#include "Arduino.h"
#include <vector>

std::string generateTaskId();

std::string getChipId(const char *prefix);

int32_t parseInt32(const uint8_t *bytes);

std::string parseString(const uint8_t *bytes, uint32_t length);

std::vector<uint8_t> int2Array(uint32_t size);

double calculateSoundRMS(const uint8_t *buffer, size_t bufferSize);

std::pair<int, size_t> findMinIndexOfDelimiter(const String &input);

#endif
