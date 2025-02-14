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

uint8_t *int2Array(uint16_t size) {
    auto *result = new uint8_t[4];
    result[0] = (size >> 24) & 0xFF;
    result[1] = (size >> 16) & 0xFF;
    result[2] = (size >> 8) & 0xFF;
    result[3] = size & 0xFF;
    return result;
}

// 检查是否有声音
bool hasSound(uint8_t *buffer, const size_t bufferSize) {
    constexpr float threshold = 100.0; // 预设阈值，可根据实际情况调整
    float sumSquares = 0.0;
    // 遍历音频缓冲区
    for (size_t i = 0; i < bufferSize; i += 4) {
        // 假设数据为32位
        int32_t sample = *reinterpret_cast<int32_t *>(&buffer[i]);
        sumSquares += static_cast<float>(sample * sample);
    }
    // 计算均方根（RMS）值
    const float rms = sqrt(sumSquares / (bufferSize / 4));
    // 判断RMS值是否超过阈值
    Serial.printf("声音RMS值: %f\n", rms);
    return rms > threshold;
}
