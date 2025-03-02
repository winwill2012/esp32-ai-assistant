#include "GlobalState.h"

#include <utility>

String GlobalState::conversationId = "";
MachineState GlobalState::machineState = Sleep;

void GlobalState::setConversationId(String conversationId) {
    GlobalState::conversationId = std::move(conversationId);
}

String GlobalState::getConversationId() {
    return conversationId;
}

MachineState GlobalState::getState() {
    return machineState;
}

void GlobalState::setState(MachineState state) {
    machineState = state;
}
