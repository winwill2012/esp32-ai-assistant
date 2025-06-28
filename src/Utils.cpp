#include <GlobalState.h>
#include <vector>

#include "LvglDisplay.h"
#include "utils.h"
#include "gui/gui_guider.h"
#include "misc/lv_timer_private.h"
auto charset = "0123456789abcdef";

static bool isConnectingWifi = false;
static int connectRetries = 0;

std::string generateTaskId()
{
    randomSeed(millis());
    char uuid[33];
    for (int i = 0; i < 32; i++)
    {
        uuid[i] = charset[random(16)];
    }
    uuid[32] = '\0';
    return {uuid};
}

int32_t readInt32(const uint8_t* bytes)
{
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

std::string readString(const uint8_t* bytes, const uint32_t length)
{
    std::string result;
    for (int i = 0; i < length; i++)
    {
        result += static_cast<char>(bytes[i]);
    }
    return result;
}

std::string getChipId(const char* prefix)
{
    std::string content{prefix ? prefix : ""};
    const std::size_t size = content.length();
    content.resize(size + 12); // mac 地址 6 * 2
    uint8_t buffer[6];
    esp_efuse_mac_get_default(buffer);
    sprintf(&content.at(size), "%02X%02X%02X%02X%02X%02X", buffer[0], buffer[1],
            buffer[2], buffer[3], buffer[4], buffer[5]);
    return content;
}

std::vector<uint8_t> uint32ToUint8Array(const uint32_t size)
{
    std::vector<uint8_t> result(4);
    result[0] = (size >> 24) & 0xFF;
    result[1] = (size >> 16) & 0xFF;
    result[2] = (size >> 8) & 0xFF;
    result[3] = size & 0xFF;
    return result;
}

std::pair<int, size_t> findMinIndexOfDelimiter(const String& input)
{
    // 定义需要处理的中英文标点集合
    std::vector<String> delimiters = {"，", "。", "！", "：", "；", "？"};

    int minIndex = -1;
    size_t minIndexDelimiterLength = 0;
    for (const String& delimiter : delimiters)
    {
        const int index = input.indexOf(delimiter);
        if (index > 0 && (index < minIndex || minIndex == -1))
        {
            minIndex = index;
            minIndexDelimiterLength = delimiter.length();
        }
    }
    return std::make_pair(minIndex, minIndexDelimiterLength);
}

void connectSavedWifi(const char* ssid, const char* password, int maxRetries)
{
    GlobalState::setState(NetworkConnecting);
    WiFiClass::mode(WIFI_MODE_STA);
    WiFiClass::useStaticBuffers(true);
    WiFi.begin(ssid, password);
    int retryCount = 0;
    while (WiFiClass::status() != WL_CONNECTED && retryCount < maxRetries)
    {
        retryCount++;
        vTaskDelay(pdMS_TO_TICKS(1000));
        GlobalState::setState(NetworkConnecting);
    }
    if (WiFiClass::status() == WL_CONNECTED)
    {
        GlobalState::setState(NetworkConnected);
    }
    else
    {
        WiFi.disconnect(false, true);
        GlobalState::setState(NetworkConnectFailed);
    }
}

bool reconnectWifi(lv_timer_t* timer, const char* ssid, const char* password, const int maxRetries)
{
    if (isConnectingWifi)
    {
        connectRetries++;
        GlobalState::setState(NetworkConnecting);
        if (WiFi.isConnected())
        {
            GlobalState::setState(NetworkConnected);
            lv_timer_delete(timer); // 连接成功，删除联网定时器
            lv_screen_load(guider_ui.screen_main);
            isConnectingWifi = false;
            connectRetries = 0;
            return true;
        }
        if (connectRetries >= maxRetries)
        {
            GlobalState::setState(NetworkConnectFailed);
            lv_timer_delete(timer); // 重试次数超过限制，联网失败，删除联网定时器
            isConnectingWifi = false;
            connectRetries = 0;
            return false;
        }
        return false;
    }
    isConnectingWifi = true;
    GlobalState::setState(NetworkConnecting);
    if (WiFi.isConnected())
    {
        WiFi.disconnect(true, true);
    }
    log_d("connect wifi with config: [%s, %s]", ssid, password);
    WiFiClass::mode(WIFI_MODE_STA);
    WiFiClass::useStaticBuffers(true);
    WiFi.begin(ssid, password);
    return false;
}

uint32_t hexColorToUInt(String hex)
{
    if (hex.length() != 7 || hex[0] != '#')
    {
        return 0xffffff;
    }
    hex.replace("#", "");
    return std::stoul(hex.c_str(), nullptr, 16);
}

int str2int(const String& input)
{
    return std::stoi(input.c_str(), nullptr, 10);
}

double str2double(const String& input)
{
    return std::stod(input.c_str(), nullptr);
}
