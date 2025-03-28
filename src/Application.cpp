#include "Application.h"

#include <TimeUpdater.h>
#include <asr/DoubaoASR.h>

DECLARE_ASR(DoubaoASR)

Application::Application() {
    _ttsClient = new DoubaoTTS();
    _llmAgent = new CozeLLMAgent();
    _asrClient = createASR();
    _audioPlayer = new AudioPlayer();
    _recordingManager = new RecordingManager();
}

void Application::begin() const {
    TimeUpdater::begin();
    _audioPlayer->begin();
    _recordingManager->begin();
}
