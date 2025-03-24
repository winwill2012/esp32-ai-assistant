#include "Application.h"

Application *Application::_instance = nullptr;

Application::Application() {
    _ttsClient = new DoubaoTTS();
    _llmAgent = new CozeLLMAgent();
    _sttClient = new DoubaoSTT();
    _audioPlayer = new AudioPlayer();
    _recordingManager = new RecordingManager();
}

void Application::begin() {
    TimeUpdater::begin();
    _audioPlayer->begin();
    _recordingManager->begin();
}

Application *Application::getInstance() {
    if (_instance == nullptr) {
        _instance = new Application();
    }
    return _instance;
}