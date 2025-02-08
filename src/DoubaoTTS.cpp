#include "DoubaoTTS.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <driver/i2s.h>

// 替换为你的网络信息
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// WebSocket服务器信息
const char* server = "openspeech.bytedance.com";
const int port = 443;
const char* path = "/api/v1/tts/ws_binary";

// 替换为你的appid和token
const char* appid = "XXX";
const char* token = "XXX";

// 音色信息，此处xxxx替换成需要调用的音色
const char* voiceType = "xxxx";

// I2S配置
#define I2S_NUM 0
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 1024

WebSocketsClient webSocket;

// 流式合成函数
void streamSynth(const char* text, const char* voiceType) {
  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // 配置I2S
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false,
    .tx_desc_auto_clear = true
  };
  i2s_pin_config_t pin_config = {
    .bck_io_num = 26,
    .ws_io_num = 25,
    .data_out_num = 22,
    .data_in_num = I2S_PIN_NO_CHANGE
  };
  i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM, &pin_config);

  // 构造请求数据
  DynamicJsonDocument params(1024);
  params["app"]["appid"] = appid;
  params["app"]["token"] = "access_token";
  params["app"]["cluster"] = "xxxx";
  params["user"]["uid"] = "uid";
  params["audio"]["voice_type"] = voiceType;
  params["audio"]["encoding"] = "pcm";
  params["audio"]["speed_ratio"] = 1.0;
  params["audio"]["volume_ratio"] = 1.0;
  params["audio"]["pitch_ratio"] = 1.0;
  params["request"]["reqid"] = "reqid";
  params["request"]["text"] = text;
  params["request"]["text_type"] = "plain";
  params["request"]["operation"] = "submit";

  String jsonStr;
  serializeJson(params, jsonStr);

  // 连接WebSocket服务器
  webSocket.beginSSL(server, port, path);
  webSocket.setAuthorization("Bearer;" + String(token));
  webSocket.onEvent(webSocketEvent);

  // 发送请求
  webSocket.sendTXT(jsonStr);

  // 等待数据接收和处理
  while (true) {
    webSocket.loop();
    delay(10);
  }
}

// WebSocket事件处理函数
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      break;
    case WStype_BIN:
      // 处理接收到的二进制数据
      i2s_write(I2S_NUM, payload, length, &i2s_bytes_written, portMAX_DELAY);
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      break;
    case WStype_PING:
      // pong will be send automatically
      Serial.printf("[WSc] get ping\n");
      break;
    case WStype_PONG:
      Serial.printf("[WSc] get pong\n");
      break;
    case WStype_ERROR:
      Serial.printf("[WSc] get error: %s\n", payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();

  // 调用流式合成函数
  streamSynth("我想测试下语音合成的效果", voiceType);
}

void loop() {
  // 主循环，可根据需要添加其他功能
}