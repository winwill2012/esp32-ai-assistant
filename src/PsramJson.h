#ifndef ESP32_AI_ASSISTANT_PSRAMJSON_H
#define ESP32_AI_ASSISTANT_PSRAMJSON_H

#include "Arduino.h"
#include "ArduinoJson.h"
#include "ArduinoJson/Memory/Allocator.hpp"

struct SpiRamAllocator : ArduinoJson::Allocator {
    void *allocate(size_t size) {
        return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
    }

    void deallocate(void *pointer) {
        heap_caps_free(pointer);
    }

    void *reallocate(void *ptr, size_t new_size) {
        return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);
    }
};

//extern SpiRamAllocator spiRamAllocator;
#endif //ESP32_AI_ASSISTANT_PSRAMJSON_H
