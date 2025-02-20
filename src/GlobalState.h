
#ifndef IOT_AI_CONTROLLER_GLOBALSTATE_H
#define IOT_AI_CONTROLLER_GLOBALSTATE_H

enum BotState {
    Init,
    Listening,
    Playing
};

extern BotState globalState;

#endif //IOT_AI_CONTROLLER_GLOBALSTATE_H
