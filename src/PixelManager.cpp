#include "PixelManager.h"

#include <FastLED.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <algorithm>

#include "Pixel.h"

PixelManager::Pixels* PixelManager::_pixels      = 0;
bool                  PixelManager::_update      = false;
TaskHandle_t          PixelManager::_task_handle = 0;

void PixelManager::add(Pixel* pixel) {
    if (!_task_handle) _create_task();

    Pixels& pixels = _getPixels();
    pixels.push_back(pixel);
}

void PixelManager::remove(Pixel* pixel) {
    Pixels& pixels = _getPixels();
    pixels.erase(std::remove(pixels.begin(), pixels.end(), pixel), pixels.end());
}

void PixelManager::update() {
    _update = true;
}

PixelManager::Pixels& PixelManager::_getPixels() {
    if (!_pixels) _pixels = new Pixels;
    return *_pixels;
}

void PixelManager::_update_string() {
    FastLED.show();
    _update = false;
}

void PixelManager::_create_task() {
    xTaskCreate(_task, "PixelManager", 4096, nullptr, 1, &_task_handle);
}

void PixelManager::_task(void* arg) {
    Pixels& pixels = _getPixels();
    for (;;) {
        for (auto pixel : pixels) pixel->_loop();
        if (_update) _update_string();
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}