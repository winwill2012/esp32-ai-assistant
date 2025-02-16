#ifndef AI_ROBOT_UTILS_H
#define AI_ROBOT_UTILS_H

#include "Arduino.h"

String generateTaskId();

std::string getChipId(const char *prefix);

int32_t parseInt32(const uint8_t *bytes);

String parseString(const uint8_t *bytes, uint32_t length);

uint8_t *int2Array(uint32_t size);

bool hasSound(const uint8_t *buffer, size_t bufferSize, float threshold);

#endif
