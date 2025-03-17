#include "AudioPlayer.h"
#include "GlobalState.h"
#include "driver/i2s.h"

QueueHandle_t AudioPlayer::_taskQueue = xQueueCreate(30, sizeof(PlayAudioTask));

void playAudio(void *ptr) {
    PlayAudioTask task{};
    size_t bytes_written;
    while (true) {
        if (xQueueReceive(AudioPlayer::getTaskQueue(), &task, portMAX_DELAY) == pdPASS) {
            GlobalState::setState(Playing);
            const esp_err_t result = i2s_write(MAX98357_I2S_NUM, task.data, task.length, &bytes_written, portMAX_DELAY);
            if (result != ESP_OK) {
                log_e("Play audio failed, errorCode: %d", result);
            }
            free(task.data);
            // 语音已经播放完成，并且队列里面没有数据，则进入监听模式
            if (uxQueueMessagesWaiting(AudioPlayer::getTaskQueue()) == 0) {
                // 此时可能i2s DMA缓冲区还有未播放的数据，延时1000ms，不然可能麦克风会监听到播放的语音
                vTaskDelay(pdMS_TO_TICKS(1000));
                GlobalState::setState(Listening);
            }
        }
        vTaskDelay(1);
    }
}

QueueHandle_t AudioPlayer::getTaskQueue() {
    return _taskQueue;
}

void AudioPlayer::begin() {
    constexpr i2s_config_t max98357_i2s_config = {
        .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL6, // 中断优先级，如果对实时性要求高，可以调高优先级
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .tx_desc_auto_clear = true
    };

    constexpr i2s_pin_config_t max98357_gpio_config = {
        .bck_io_num = MAX98357_BCLK,
        .ws_io_num = MAX98357_LRC,
        .data_out_num = MAX98357_DOUT,
        .data_in_num = -1
    };

    i2s_driver_install(MAX98357_I2S_NUM, &max98357_i2s_config, 0, nullptr);
    i2s_set_pin(MAX98357_I2S_NUM, &max98357_gpio_config);
    i2s_zero_dma_buffer(MAX98357_I2S_NUM);

    xTaskCreate(playAudio, "playAudio", 4096, nullptr, 1, nullptr);
}

void AudioPlayer::publishTask(const PlayAudioTask task) {
    if (xQueueSend(_taskQueue, &task, portMAX_DELAY) != pdPASS) {
        log_e("发送音频播放任务到队列失败: %d", task.length);
        free(task.data); // 发送到队列失败，则生产者负责将内存回收
    }
}
