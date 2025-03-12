#include "AudioPlayer.h"
#include "GlobalState.h"

AudioPlayer AudioPlayer::instance;

AudioPlayer &AudioPlayer::getInstance() {
    return instance;
}

AudioPlayer::AudioPlayer() {
    _taskQueue = xQueueCreate(20, sizeof(PlayAudioTask));
    const i2s_config_t max98357_i2s_config = {
            .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
            .sample_rate = SAMPLE_RATE,
            .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = I2S_COMM_FORMAT_STAND_I2S,
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
            .dma_buf_count = 8,
            .dma_buf_len = 1024,
            .tx_desc_auto_clear = true
    };

    const i2s_pin_config_t max98357_gpio_config = {
            .bck_io_num = MAX98357_BCLK,
            .ws_io_num = MAX98357_LRC,
            .data_out_num = MAX98357_DOUT,
            .data_in_num = -1
    };

    i2s_driver_install(I2S_NUM_0, &max98357_i2s_config, 0, nullptr);
    i2s_set_pin(I2S_NUM_0, &max98357_gpio_config);
    i2s_zero_dma_buffer(I2S_NUM_0);
}

void playAudio(void *ptr) {
    PlayAudioTask task{};
    size_t bytes_written;
    while (1) {
        if (xQueueReceive(AudioPlayer::getInstance().getTaskQueue(), &task, portMAX_DELAY) == pdPASS) {
            GlobalState::setState(Playing);
            esp_err_t result = i2s_write(I2S_NUM_0, task.data, task.length, &bytes_written, portMAX_DELAY);
            if (result != ESP_OK) {
                log_e("播放音频失败, 错误码: %d", result);
            } else {
                log_d("播放音频成功: %d", task.length);
            }
            free(task.data);
            // 语音已经播放完成，并且队列里面没有数据，则进入监听模式
            if (uxQueueMessagesWaiting(AudioPlayer::getInstance().getTaskQueue()) == 0) {
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
    xTaskCreate(playAudio, "playAudio", 4096, nullptr, 1, nullptr);
}

void AudioPlayer::publishTask(PlayAudioTask task) {
    if (xQueueSend(_taskQueue, &task, portMAX_DELAY) != pdPASS) {
        log_e("发送音频播放任务到队列失败: %d", task.length);
    }
}

