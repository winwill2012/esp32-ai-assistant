#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H
#include<Arduino.h>
#include<SPIFFS.h>

#define FILE_NAME "/cid.txt"

class StorageManager : public fs::SPIFFSFS {
public:
    StorageManager();

    static bool begin();

    static void updateConversationId(const String &conversationId);

    static String readConversationId();
};
#endif //STORAGEMANAGER_H
