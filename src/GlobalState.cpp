#include "GlobalState.h"

#include <utility>

String GlobalState::conversationId = "";
EventGroupHandle_t GlobalState::eventGroup = xEventGroupCreate();

void GlobalState::setEvents(const EventBits_t events) {
    xEventGroupSetBits(eventGroup, events);
}

void GlobalState::unsetEvents(const EventBits_t events) {
    xEventGroupClearBits(eventGroup, events);
}

EventBits_t GlobalState::waitAnyEvent(const EventBits_t events, const TickType_t tick) {
    return xEventGroupWaitBits(eventGroup, events, false, false, tick);
}

bool GlobalState::waitAllEvents(const EventBits_t events, const TickType_t tick) {
    const EventBits_t bits = xEventGroupWaitBits(eventGroup, events, false, true, tick);
    return (bits & events) == events;
}

void GlobalState::setConversationId(String conversationId) {
    GlobalState::conversationId = std::move(conversationId);
}

String GlobalState::getConversationId() {
    return conversationId;
}
