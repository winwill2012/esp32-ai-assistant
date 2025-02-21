#include "StorageManager.h"

#include <SPI.h>
#include <SPIFFS.h>

StorageManager::StorageManager(const String &fileName) {
    _fileName = fileName;
}

bool StorageManager::begin() {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return false;
    }
    return true;
}

void StorageManager::update(const String &content) const {
    if (content.isEmpty()) { return; }
    File file = SPIFFS.open(_fileName, FILE_WRITE);
    file.println(content);
    file.close();
}

String StorageManager::read() const {
    if (!SPIFFS.exists(_fileName)) {
        return "";
    }
    File file = SPIFFS.open(_fileName, FILE_READ);
    String value = file.readStringUntil('\n');
    file.close();
    return value;
}
