#include "Application.h"

#include <TimeUpdater.h>
#include <asr/DoubaoASR.h>

#include "IOT.h"

DECLARE_ASR(DoubaoASR)

Application::Application()
{
    IOT::begin();
    _ttsClient = new DoubaoTTS();
    _llmAgent = new CozeLLMAgent();
    _asrClient = createASR();
    _audioPlayer = new AudioPlayer();
    _recordingManager = new RecordingManager();
}

void Application::begin() const
{
    TimeUpdater::begin();
    _audioPlayer->begin();
    // showMemoryInfo();
    _recordingManager->begin();
}

void Application::showMemoryInfo()
{
    xTaskCreate([](void* ptr)
    {
        while (true)
        {
            ESP_LOGD("Application", "Free ram: %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
            ESP_LOGD("Application", "Free psram: %d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }, "showMemoryInfo", 2048, nullptr, 1, nullptr);
}
