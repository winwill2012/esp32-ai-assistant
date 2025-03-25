#ifndef ESP32_AI_ASSISTANT_APPLICATION_H
#define ESP32_AI_ASSISTANT_APPLICATION_H

#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "RecordingManager.h"
#include "AudioPlayer.h"

class Application {
public:
    static Application *getInstance();

    void begin() const;

    DoubaoTTS *getTTSInstance() const { return _ttsClient; }

    DoubaoSTT *getSTTInstance() const { return _sttClient; }

    CozeLLMAgent *getLlmAgentInstance() const { return _llmAgent; }

    RecordingManager *recordingManager() const { return _recordingManager; }

    AudioPlayer *getAudioPlayer() const { return _audioPlayer; }

private:
    Application();

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    static Application *_instance;

    DoubaoTTS *_ttsClient = nullptr;
    DoubaoSTT *_sttClient = nullptr;
    CozeLLMAgent *_llmAgent = nullptr;
    AudioPlayer *_audioPlayer = nullptr;
    RecordingManager *_recordingManager = nullptr;
};


#endif //ESP32_AI_ASSISTANT_APPLICATION_H
