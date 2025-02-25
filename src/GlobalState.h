#ifndef IOT_AI_CONTROLLER_GLOBALSTATE_H
#define IOT_AI_CONTROLLER_GLOBALSTATE_H

#include <Arduino.h>

enum BotState {
    Init,
    Listening,
    Playing
};

extern BotState globalState;
extern String cid;

#endif //IOT_AI_CONTROLLER_GLOBALSTATE_H
