#ifndef ESP32_AI_ASSISTANT_APPLICATION_H
#define ESP32_AI_ASSISTANT_APPLICATION_H

#include "DoubaoTTS.h"
#include "DoubaoSTT.h"
#include "RecordingManager.h"
#include "TimeUpdater.h"
#include "AudioPlayer.h"

class Application {
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

public:
    static Application *getInstance();

    void begin();

    inline DoubaoTTS *getTTSInstance() const { return _ttsClient; }

    inline DoubaoSTT *getSTTInstance() const { return _sttClient; }

    inline CozeLLMAgent *getLlmAgentInstance() const { return _llmAgent; }

    inline RecordingManager *recordingManager() const { return _recordingManager; }

    inline AudioPlayer *getAudioPlayer() const { return _audioPlayer; }
};


#endif //ESP32_AI_ASSISTANT_APPLICATION_H
