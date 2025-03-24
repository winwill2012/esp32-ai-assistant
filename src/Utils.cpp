#include <GlobalState.h>
#include <vector>
#include "utils.h"
#include "arduinoFFT.h"

auto charset = "0123456789abcdef";

std::string generateTaskId() {
    randomSeed(millis());
    char uuid[33];
    for (int i = 0; i < 32; i++) {
        uuid[i] = charset[random(16)];
    }
    uuid[32] = '\0';
    return {uuid};
}

int32_t readInt32(const uint8_t *bytes) {
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

std::string readString(const uint8_t *bytes, const uint32_t length) {
    std::string result;
    for (int i = 0; i < length; i++) {
        result += static_cast<char>(bytes[i]);
    }
    return result;
}

std::string getChipId(const char *prefix) {
    std::string content{prefix ? prefix : ""};
    const std::size_t size = content.length();
    content.resize(size + 12); // mac 地址 6 * 2
    uint8_t buffer[6];
    esp_efuse_mac_get_default(buffer);
    sprintf(&content.at(size), "%02X%02X%02X%02X%02X%02X", buffer[0], buffer[1],
            buffer[2], buffer[3], buffer[4], buffer[5]);
    return content;
}

std::vector<uint8_t> uint32ToUint8Array(const uint32_t size) {
    std::vector<uint8_t> result(4);
    result[0] = (size >> 24) & 0xFF;
    result[1] = (size >> 16) & 0xFF;
    result[2] = (size >> 8) & 0xFF;
    result[3] = size & 0xFF;
    return result;
}

double calculateSoundRMS(const uint8_t *buffer, const size_t bufferSize) {
    if (bufferSize % 2 != 0) {
        return 0.0;
    }
    double sumSquares = 0.0;
    for (size_t i = 0; i < bufferSize; i += 2) {
        const auto sample = static_cast<int16_t>((buffer[i] << 8) | buffer[i + 1]);
        sumSquares += (sample * sample);
    }
    double rms = sqrt(sumSquares * 2 / bufferSize);
    return rms;
}


std::pair<int, size_t> findMinIndexOfDelimiter(const String &input) {
    // 定义需要处理的中英文标点集合
    std::vector<String> delimiters = {"，", "。", "！", "：", "；", "？"};

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

bool connectWifi(const char *ssid, const char *password, const int maxRetries) {
    // 如果当前已经连接成功，先断开网络
    if (WiFi.isConnected()) {
        WiFi.disconnect(true, true);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    log_d("connect wifi with config: [%s, %s]", ssid, password);
    GlobalState::setState(NetworkConnecting);
    WiFiClass::mode(WIFI_MODE_STA);
    WiFiClass::useStaticBuffers(true);
    WiFi.begin(ssid, password);
    int retries = 0;
    while (!WiFi.isConnected() && retries < maxRetries) {
        Serial.print(".");
        vTaskDelay(1000);
        retries++;
    }
    if (WiFi.isConnected()) {
        GlobalState::setState(NetworkConnected);
        log_i("network connect successfully!");
        return true;
    }
    GlobalState::setState(NetworkConnectFailed);
    log_e("network connect failed!");
    return false;
}

// 将 int16_t 数组转换成 uint8_t 数组，采用大端序，返回 std::vector<uint8_t>
std::vector<uint8_t> int16ToUint8BigEndian(const std::vector<int16_t> &input) {
    std::vector<uint8_t> output;
    output.reserve(input.size() * 2);

    for (const int16_t value: input) {
        output.push_back(static_cast<uint8_t>(value >> 8)); // 高字节
        output.push_back(static_cast<uint8_t>(value & 0xFF)); // 低字节
    }

    return output;
}

// 将 uint8_t 数组转换成 int16_t 数组，采用大端序，返回 std::vector<int16_t>
std::vector<int16_t> uint8ToInt16BigEndian(const std::vector<uint8_t> &input) {
    std::vector<int16_t> output;
    if (input.size() % 2 != 0) {
        return output;
    }
    output.reserve(input.size() / 2);
    for (size_t i = 0; i < input.size(); i += 2) {
        auto value = static_cast<int16_t>((input[i] << 8) | input[i + 1]);
        output.push_back(value);
    }
    return output;
}
