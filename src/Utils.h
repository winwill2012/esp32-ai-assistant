#ifndef AI_ROBOT_UTILS_H
#define AI_ROBOT_UTILS_H

#include "Arduino.h"

String generateTaskId();

std::string getChipId(const char *prefix);

uint8_t *int2Array(uint16_t size);

#endif
