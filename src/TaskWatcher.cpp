#include "TaskWatcher.h"

#include <utility>

void checkChatTask(void *ptr) {
    auto *watcher = static_cast<TaskWatcher *>(ptr);
    String *message;
    while (true) {
        if (xQueueReceive(watcher->getChatQueue(), &message, portMAX_DELAY) == pdTRUE) {
            Serial.printf("收到chat任务: %s\n", (*message).c_str());
            watcher->getLLMAgent().begin(*message);
            free(message);
            vTaskDelay(1);
        }
    }
}

void checkTTSTask(void *ptr) {
    auto *watcher = static_cast<TaskWatcher *>(ptr);
    String *message;
    while (true) {
        if (xQueueReceive(watcher->getTTSQueue(), &message, portMAX_DELAY) == pdTRUE) {
            Serial.printf("收到tts任务: %s\n", (*message).c_str());
            watcher->getTTS().synth(*message);
            free(message);
            vTaskDelay(1);
        }
    }
}

TaskWatcher::TaskWatcher(const LLMAgent &llmAgent, DoubaoTTS tts) : _llmAgent(llmAgent), _tts(std::move(tts)) {
    _chatQueue = xQueueCreate(3, sizeof(String *));
    _ttsQueue = xQueueCreate(3, sizeof(String *));
    xTaskCreate(checkChatTask, "checkChatTask", 4096, this, 1, nullptr);
    xTaskCreate(checkTTSTask, "checkTTSTask", 8192, this, 1, nullptr);
}

TaskWatcher::~TaskWatcher() = default;

void TaskWatcher::publishChatTask(String *text) {
    Serial.printf("往chat队列发送消息: %s\n", (*text).c_str());
    xQueueSend(_chatQueue, &text, portMAX_DELAY);
}

void TaskWatcher::publishTTSTask(String *message) {
    Serial.printf("往tts队列发送消息: %s\n", (*message).c_str());
    xQueueSend(_ttsQueue, &message, portMAX_DELAY);
}

QueueHandle_t TaskWatcher::getChatQueue() {
    return _chatQueue;
}

QueueHandle_t TaskWatcher::getTTSQueue() {
    return _ttsQueue;
}

LLMAgent TaskWatcher::getLLMAgent() {
    return _llmAgent;
}

DoubaoTTS TaskWatcher::getTTS() {
    return _tts;
}
