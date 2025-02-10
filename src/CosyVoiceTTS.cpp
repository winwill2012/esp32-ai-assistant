#include "CosyVoiceTTS.h"

#include <utility>

#include "utils.h"
#include "semphr.h"
#include "driver/i2s.h"
#include "freertos/task.h"
#include "Arduino.h"
#include "ArduinoJson.h"
#include "esp_system.h"
#include <vector>

JsonDocument params;
/**
 * 第0个字节：0b0001, 0b0001   (协议版本，报头大小)
 * 第1个字节：0b0001, 0b0000   (消息类型，Message type specific flags)
 * 第2个字节：0b0001, 0b0000   (序列化方式，压缩方法)
 * 第3个字节：0b0000, 0b0000   (保留字节)
 */
const uint8_t defaultHeader[] = {0x11, 0x10, 0x10, 0x00};
TaskHandle_t eventHandler;

CosyVoiceTTS::CosyVoiceTTS(i2s_port_t i2sNumber, uint32_t sampleRate, String voiceType,
                           const String &appId,
                           const String &token, const String &host, int port,
                           const String &url, int i2sDout, int i2sBclk, int i2sLrc) {
    _i2sNumber = i2sNumber;
    _voiceType = std::move(voiceType);
    _appId = appId;
    _token = token;
    _host = host;
    _port = port;
    _url = url;
    _sampleRate = sampleRate;
    _i2sDout = i2sDout;
    _i2sBclk = i2sBclk;
    _i2sLrc = i2sLrc;
    _available = xSemaphoreCreateBinary();
    xSemaphoreGive(_available);
    setupMax98357();
}

void CosyVoiceTTS::eventCallback(WStype_t type, uint8_t *payload, size_t length) {
    Serial.print("received message: ");
    Serial.println(type);
    switch (type) {
        case WStype_PING:
            break;
        case WStype_ERROR:
            Serial.println("Connect error: ");
            for (size_t i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        case WStype_CONNECTED: {
            Serial.println("WebSocket connected");
            xSemaphoreGive(_available);
            break;
        }
        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected");
            xSemaphoreTake(_available, portMAX_DELAY);
            break;
        case WStype_TEXT: {
            for (int i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        }
        case WStype_BIN:
            Serial.print("Received bin: ");
            Serial.println(length);
//            if (parseResponse(payload)) {
//                Serial.println("close the connection");
////                disconnect();
//                xSemaphoreGive(_available);
////                vTaskDelete(eventHandler);
//            }
            break;
        default:
            break;
    }
}

String CosyVoiceTTS::buildFullClientRequest(const String &text) {
    JsonObject app = params["app"].to<JsonObject>();
    app["appid"] = _appId;
    app["token"] = _token;
    app["cluster"] = "volcano_tts";

    JsonObject user = params["user"].to<JsonObject>();
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    user["uid"] = String(mac, 6);

    JsonObject audio = params["audio"].to<JsonObject>();
    audio["voice_type"] = _voiceType;
    audio["encoding"] = "pcm";
    audio["rate"] = _sampleRate;
    audio["speed_ratio"] = 1.0;
    audio["volume_ratio"] = 1.0;
    audio["pitch_ratio"] = 1.0;
    audio["emotion"] = "happy";
    audio["language"] = "cn";

    JsonObject request = params["request"].to<JsonObject>();
    request["reqid"] = generateTaskId();
    request["text"] = text;
    request["text_type"] = "plain";
    request["operation"] = "submit";
    String resStr;
    serializeJson(params, resStr);
    return resStr;
}

// 语音合成
void CosyVoiceTTS::synth(const String &text) {
    if (xSemaphoreTake(_available, 1) == pdFALSE) {
        Serial.println("tts is busy");
        return;
    }
    begin(); // 建立连接
    if (!isConnected()) {
        Serial.println("websocket is disConnected");
        return;
    }
    String payloadStr = buildFullClientRequest(text);
    uint8_t payload[payloadStr.length()];
    for (int i = 0; i < payloadStr.length(); i++) {
        payload[i] = static_cast<uint8_t>(payloadStr.charAt(i));
    }
    payload[payloadStr.length()] = '\0';
    size_t payloadSize = payloadStr.length();
    uint8_t payloadArr[4];
    payloadArr[0] = (payloadSize >> 24) & 0xFF;
    payloadArr[1] = (payloadSize >> 16) & 0xFF;
    payloadArr[2] = (payloadSize >> 8) & 0xFF;
    payloadArr[3] = payloadSize & 0xFF;

    // 先写入报头（四字节）
    std::vector<uint8_t> clientRequest(defaultHeader, defaultHeader + sizeof(defaultHeader));
    // 写入payload长度（四字节）
    clientRequest.insert(clientRequest.end(), payloadArr, payloadArr + sizeof(payloadArr));
    // 写入payload内容
    clientRequest.insert(clientRequest.end(), payload, payload + sizeof(payload));
    Serial.print("send bin: ");
    Serial.println(payloadStr);
    String base64Str = base64_encode(clientRequest.data(), clientRequest.size());
    Serial.println(base64Str);
    sendBIN(clientRequest.data(), clientRequest.size());
}

void CosyVoiceTTS::setupMax98357() {
    i2s_config_t max98357_i2s_config = {
            .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX),
            .sample_rate = _sampleRate,
            .bits_per_sample = i2s_bits_per_sample_t(16),
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_MSB),
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_buf_count = 8,
            .dma_buf_len = 1024,
            .tx_desc_auto_clear = true
    };

    const i2s_pin_config_t max98357_gpio_config = {
            .bck_io_num = _i2sBclk,
            .ws_io_num = _i2sLrc,
            .data_out_num = _i2sDout,
            .data_in_num = -1
    };

    i2s_driver_install(_i2sNumber, &max98357_i2s_config, 0, nullptr);
    i2s_set_pin(_i2sNumber, &max98357_gpio_config);
    i2s_zero_dma_buffer(_i2sNumber);
}

[[noreturn]] void webSocketLoop(void *ptr) {
    auto *client = (CosyVoiceTTS *) ptr;
    while (true) {
        client->loop();
        vTaskDelay(1);
    }
}

void CosyVoiceTTS::begin() {
    if (isConnected()) {
        return;
    }
    setExtraHeaders(("Authorization: Bearer; " + _token).c_str());
    beginSSL(_host, _port, _url);
    onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
        this->eventCallback(type, payload, length);
    });
    setReconnectInterval(1000);
    xTaskCreate(webSocketLoop, "webSocketLoop", 4096, this, 1, &eventHandler);
}

int32_t bigEndianToInt32(const uint8_t *bytes) {
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

bool CosyVoiceTTS::parseResponse(uint8_t *res) {
    uint8_t messageType = res[1] >> 4;
    uint8_t messageTypeSpecificFlags = res[1] & 0x0f;
    uint8_t *payload = res + 4;

    Serial.printf("message type: %d\n", messageType);
    Serial.printf("messageTypeSpecificFlags: %d\n", messageTypeSpecificFlags);
    if (messageType == 0xb) {  // 0b1011 - Audio-only server response (ACK).
        if (messageTypeSpecificFlags > 0) {
            auto sequenceNumber = static_cast<int32_t>(bigEndianToInt32(payload));
            auto payloadSize = static_cast<uint32_t>(bigEndianToInt32(payload + 4));
            Serial.printf("sequenceNumber: %d, payloadSize: %d, bin size: %d\n", sequenceNumber, payloadSize,
                          payloadSize);
            payload += 8;
            size_t written_size;
            i2s_write(_i2sNumber, payload, payloadSize, &written_size, portMAX_DELAY);
            if (sequenceNumber < 0) {
                Serial.println("tts synth completed");
                return true;
            }
        }
    } else if (messageType == 0xf) {
        Serial.println("synth error");
        xSemaphoreGive(_available);
    }
    return false;
}
