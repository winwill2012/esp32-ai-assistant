#ifndef IOT_AI_CONTROLLER_GLOBALSTATE_H
#define IOT_AI_CONTROLLER_GLOBALSTATE_H

#include <Arduino.h>
#include <freertos/event_groups.h>

#define EVENT_TTS_WS_CONNECTED (1<<1)
#define EVENT_TTS_WS_TASK_FINISHED (1<<2)
#define EVENT_STT_WS_CONNECTED (1<<3)
#define EVENT_STT_WS_TASK_FINISHED (1<<4)
#define EVENT_LISTENING        (1<<5)
#define EVENT_PLAYING_AUDIO    (1<<6)

class GlobalState {
public:
    static void setEvents(EventBits_t events);

    static void unsetEvents(EventBits_t events);

    static EventBits_t waitAnyEvent(EventBits_t events, TickType_t tick);

    static bool waitAllEvents(EventBits_t events, TickType_t tick);

    static void setConversationId(String conversationId);

    static String getConversationId();

private:
    static String conversationId;
    static EventGroupHandle_t eventGroup;
};


#endif
