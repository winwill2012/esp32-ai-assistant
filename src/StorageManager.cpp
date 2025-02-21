#include "StorageManager.h"

StorageManager::StorageManager() {
}

bool StorageManager::begin() {
    return SPIFFS.begin(true);
}

void StorageManager::updateConversationId(const String &conversationId) {
    File file = SPIFFS.open(FILE_NAME, FILE_WRITE);
    file.println(conversationId);
    file.close();
}

String StorageManager::readConversationId() {
    File file = SPIFFS.open(FILE_NAME, FILE_READ);
    String cid = file.readStringUntil('\n');
    file.close();
    return cid;
}
