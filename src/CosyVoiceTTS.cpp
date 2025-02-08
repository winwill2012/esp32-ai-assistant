#include "CosyVoiceTTS.h"

#include <utility>

#include "utils.h"
#include "semphr.h"
#include "driver/i2s.h"
#include "freertos/task.h"
#include "Arduino.h"
#include "ArduinoJson.h"

JsonDocument doc;

CosyVoiceTTS::CosyVoiceTTS(i2s_port_t i2SPort, uint32_t rate, String v) {
    this->i2sNumber = i2SPort;
    this->sampleRate = rate;
    this->voice = std::move(v);
    this->connected = xSemaphoreCreateBinary();
    this->taskStarted = xSemaphoreCreateBinary();
    this->taskRunning = xSemaphoreCreateBinary();
    xSemaphoreGive(this->taskRunning);
}

void CosyVoiceTTS::eventCallback(WStype_t type, uint8_t *payload, size_t length) const {
    switch (type) {
        case WStype_ERROR:
            Serial.println("Connect error: ");
            for (size_t i = 0; i < length; i++) {
                Serial.print(static_cast<char>(payload[i]));
            }
            Serial.println();
            break;
        case WStype_CONNECTED: {
            Serial.println("WebSocket connected");
            xSemaphoreGive(this->connected);
            break;
        }
        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected");
            xSemaphoreTake(this->connected, portMAX_DELAY);
            break;
        case WStype_TEXT: {
            String message = String(reinterpret_cast<char *>(payload));
            if (message.indexOf("task-started") > 0) {
                Serial.println("task-started....");
                xSemaphoreGive(taskStarted);
            } else if (message.indexOf("task-finished") > 0) {
                Serial.println("task-finished....");
                xSemaphoreGive(taskRunning);
            } else if (message.indexOf("task-failed") > 0) {
                Serial.println("task-failed....");
                xSemaphoreGive(taskRunning);
            }
            break;
        }
        case WStype_BIN:
            Serial.print("Received bin: ");
            Serial.println(length);
            size_t bytes_written;
            i2s_write(i2sNumber, payload, length, &bytes_written, portMAX_DELAY);
            break;
        default:
            break;
    }
}

String CosyVoiceTTS::buildRunTask() {
    // 创建 header 对象
    JsonObject header = doc["header"].to<JsonObject>();
    header["action"] = "run-task";
    header["task_id"] = generateTaskId();
    header["streaming"] = "duplex";

    // 创建 payload 对象
    JsonObject payload = doc["payload"].to<JsonObject>();
    payload["task_group"] = "audio";
    payload["task"] = "tts";
    payload["function"] = "SpeechSynthesizer";
    payload["model"] = "cosyvoice-v1";
    payload["input"].to<JsonObject>();

    // 创建 parameters 对象
    JsonObject parameters = payload["parameters"].to<JsonObject>();
    parameters["text_type"] = "PlainText";
    parameters["voice"] = this->voice;
    parameters["format"] = "pcm";
    parameters["sample_rate"] = this->sampleRate;
    parameters["volume"] = 80;
    parameters["rate"] = 1;
    parameters["pitch"] = 1;

    String jsonStr;
    serializeJson(doc, jsonStr);
    return jsonStr;
}

String CosyVoiceTTS::buildContinueTask(const String &text) {
    // 创建 header 对象
    JsonObject header = doc["header"].to<JsonObject>();
    header["action"] = "continue-task";
    header["task_id"] = generateTaskId();
    header["streaming"] = "duplex";

    JsonObject payload = doc["payload"].to<JsonObject>();
    payload["task_group"] = "audio";
    payload["task"] = "tts";
    payload["function"] = "SpeechSynthesizer";
    payload["model"] = "cosyvoice-v1";

    JsonObject input = payload["input"].to<JsonObject>();
    input["text"] = text;

    String jsonStr;
    serializeJson(doc, jsonStr);
    return jsonStr;
}

String CosyVoiceTTS::buildFinishTask() {
    JsonObject header = doc["header"].to<JsonObject>();
    header["action"] = "finish-task";
    header["task_id"] = generateTaskId();
    header["streaming"] = "duplex";

    JsonObject payload = doc["payload"].to<JsonObject>();
    payload["input"].to<JsonObject>();

    String jsonStr;
    serializeJson(doc, jsonStr);
    return jsonStr;
}

void CosyVoiceTTS::tts(const String &text) {
    if (xSemaphoreTake(this->taskRunning, 1) == pdFALSE) {
        Serial.println("tts is busy");
        return;
    }
    if (xSemaphoreTake(connected, portMAX_DELAY) == pdTRUE) {
        xSemaphoreGive(connected);
        Serial.print("Run task: ");
        Serial.println(text);
        String runTask = buildRunTask();
        sendTXT(runTask);
        if (xSemaphoreTake(taskStarted, portMAX_DELAY) == pdTRUE) {
            Serial.print("Continue task: ");
            Serial.println(text);
            String continueTask = buildContinueTask(text);
            sendTXT(continueTask);
            Serial.print("Finish task: ");
            Serial.println(text);
            String finishTask = buildFinishTask();
            sendTXT(finishTask);
        }
    }
}

void CosyVoiceTTS::setupMax98357() {
    i2s_config_t max98357_i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = this->sampleRate,
        .bits_per_sample = i2s_bits_per_sample_t(16),
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .tx_desc_auto_clear = true
    };

    const i2s_pin_config_t max98357_gpio_config = {
        .bck_io_num = this->i2sBclk,
        .ws_io_num = this->i2sLrc,
        .data_out_num = this->i2sDout,
        .data_in_num = -1
    };

    i2s_driver_install(i2sNumber, &max98357_i2s_config, 0, nullptr);
    i2s_set_pin(i2sNumber, &max98357_gpio_config);
    i2s_zero_dma_buffer(i2sNumber);
}

[[noreturn]] void webSocketLoop(void *ptr) {
    auto *client = (CosyVoiceTTS *) ptr;
    while (true) {
        client->loop();
        vTaskDelay(1);
    }
}

void CosyVoiceTTS::begin(const String &sk, const String &host, int port, const String &url,
                         int out, int bclk, int lrc) {
    this->i2sDout = out;
    this->i2sBclk = bclk;
    this->i2sLrc = lrc;
    this->setupMax98357();
    setExtraHeaders(("Authorization: bearer " + sk + "\r\nX-DashScope-DataInspection: enable").c_str());
    beginSSL(host, port, url);
    onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
        this->eventCallback(type, payload, length);
    });
    setReconnectInterval(1000);
    xTaskCreate(webSocketLoop, "webSocketLoop", 4096, this, 1, nullptr);
}
