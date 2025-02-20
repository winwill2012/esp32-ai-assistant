//#ifndef IOT_AI_CONTROLLER_TASKWATCHER_H
//#define IOT_AI_CONTROLLER_TASKWATCHER_H
//
//#include <Arduino.h>
//#include "LLMAgent.h"
//#include "DoubaoTTS.h"
//#include "freertos/FreeRTOS.h"
//#include "freertos/queue.h"
//
//class TaskWatcher {
//public :
//    TaskWatcher(const LLMAgent &llmAgent, DoubaoTTS tts);
//
//    ~TaskWatcher();
//
//    void publishChatTask(String *text);
//
//    void publishTTSTask(String *message);
//
//    QueueHandle_t getChatQueue();
//
//    QueueHandle_t getTTSQueue();
//
//    LLMAgent getLLMAgent();
//
//    DoubaoTTS getTTS();
//
//private :
//    LLMAgent _llmAgent;
//    DoubaoTTS _tts;
//    QueueHandle_t _chatQueue;
//    QueueHandle_t _ttsQueue;
//};
//
//#endif
