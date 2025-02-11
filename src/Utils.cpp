#include "utils.h"

String generateTaskId() {
    String uuid = "";
    const char *charset = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        uuid += charset[random(16)];
    }
    return uuid;
}

std::string getChipId(const char *prefix) {
    std::string content{prefix ? prefix : ""};
    std::size_t size = content.length();
    content.resize(size + 12); // mac 地址 6 * 2
    uint8_t buffer[6];
    esp_efuse_mac_get_default(buffer);
    sprintf(&content.at(size), "%02X%02X%02X%02X%02X%02X", buffer[0], buffer[1],
            buffer[2], buffer[3], buffer[4], buffer[5]);
    return content;
}
