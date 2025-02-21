#include <vector>
#include "utils.h"

String generateTaskId() {
    String uuid = "";
    const char *charset = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        uuid += charset[random(16)];
    }
    return uuid;
}

int32_t parseInt32(const uint8_t *bytes) {
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

String parseString(const uint8_t *bytes, const uint32_t length) {
    String result = "";
    for (int i = 0; i < length; i++) {
        result += static_cast<char>(bytes[i]);
    }
    return result;
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

std::vector<uint8_t> int2Array(const uint32_t size) {
    std::vector<uint8_t> result(4);
    result[0] = (size >> 24) & 0xFF;
    result[1] = (size >> 16) & 0xFF;
    result[2] = (size >> 8) & 0xFF;
    result[3] = size & 0xFF;
    return result;
}

bool hasSound(const uint8_t *buffer, const size_t bufferSize, float threshold) {
    double sumSquares = 0.0;
    for (size_t i = 0; i < bufferSize; i += 2) {
        int16_t sample = (static_cast<int16_t>(buffer[i]) << 8) | buffer[i + 1];
        sumSquares += (sample * sample);
    }
    const double rms = sqrt(2 * sumSquares / bufferSize / 2);
    //    Serial.printf("sumSquares: %f  RMS值: %f\n", sumSquares, rms);
    return rms > threshold;
}

std::pair<int, size_t> findMinIndexOfDelimiter(const String &input) {
    // 定义需要处理的中英文标点集合
    std::vector<String> delimiters = {"，", "。", ".", ",", "！", "：", "；", "？"};

    int minIndex = -1;
    size_t minIndexDelimiterLength = 0;
    for (const String &delimiter: delimiters) {
        const int index = input.indexOf(delimiter);
        if (index > 0 && (index < minIndex || minIndex == -1)) {
            minIndex = index;
            minIndexDelimiterLength = delimiter.length();
        }
    }
    return std::make_pair(minIndex, minIndexDelimiterLength);
}
