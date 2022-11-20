#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <vector>

class Pixel;

class PixelManager {
    friend class Pixel;

  protected:
    using Pixels = std::vector<Pixel*>;

    static void add(Pixel*);
    static void remove(Pixel*);
    static void update();

    static Pixels& _getPixels();
    static void    _update_string();
    static void    _create_task();
    static void    _task(void*);

  protected:
    static Pixels*           _pixels;
    static bool              _update;
    static TaskHandle_t      _task_handle;
};
