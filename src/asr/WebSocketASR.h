#ifndef ASR_H
#define ASR_H
#include <vector>
#include <WebSocketsClient.h>

struct WebSocketASRTask;

class WebSocketASR : public WebSocketsClient {
public:
    virtual void recognize(WebSocketASRTask task) = 0;
};

struct WebSocketASRTask {
    WebSocketASRTask(const std::vector<uint8_t> &data, const bool firstPacket, const bool lastPacket)
        : data(data), firstPacket(firstPacket), lastPacket(lastPacket) {
    };

    // 音频数据
    std::vector<uint8_t> data;

    // 是否第一帧数据
    bool firstPacket;

    // 是否最后一帧数据
    bool lastPacket;
};

#define DECLARE_ASR(ASR_CLASS_NAME) \
WebSocketASR* createASR() { \
    return new ASR_CLASS_NAME(); \
}

#endif //ASR_H
