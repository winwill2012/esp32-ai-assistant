#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H
#include<Arduino.h>

class StorageManager {
public:
    StorageManager(const String &fileName);

    static bool begin();

    void update(const String &content) const;

    String read() const;

private:
    String _fileName;
};
#endif //STORAGEMANAGER_H
