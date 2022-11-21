#include "Pixel.h"

#include "PixelManager.h"

Pixel::Pixel(CRGB& led)
    : _led(led) {
    PixelManager::add(this);
}

Pixel::~Pixel() {
    PixelManager::remove(this);
}

Pixel& Pixel::blink(const CRGB& color, unsigned long interval, unsigned int count) {
    _pixel_mode = PixelMode_t::blink;

    _color            = color;
    _background_color = CRGB::Black;

    _blink_info = {
        .interval      = interval,
        .off_interval  = interval,
        .blink_count   = count,
        .blink_counter = 1,
        .last_blink    = 0,
        .state         = false,
    };

    return *this;
}

Pixel& Pixel::color(const CRGB& color) {
    _pixel_mode = steady;
    _color      = color;
    _led        = color;

    PixelManager::update();
    return *this;
}

Pixel& Pixel::backgroundColor(const CRGB& color) {
    _background_color = color;
    return *this;
}

void Pixel::_loop() {
    unsigned long current_millis = millis();

    if (_pixel_mode == PixelMode_t::shifted && current_millis >= _shift) {
        _pixel_mode = PixelMode_t::blink;

        _blink_info.last_blink = current_millis;
        _blink_info.state      = true;
        _led                   = _color;
        PixelManager::update();
        return;
    }

    if (_pixel_mode != PixelMode_t::blink) return;

    unsigned long max_count = _blink_info.blink_count;
    unsigned long counter   = _blink_info.blink_counter;

    if (max_count && counter > max_count) {
        _pixel_mode = PixelMode_t::off;
        _led        = _background_color;
        PixelManager::update();
    }

    long          wait_time    = _blink_info.state ? _blink_info.interval : _blink_info.off_interval;
    unsigned long elapsed_time = _blink_info.last_blink ? current_millis - _blink_info.last_blink : wait_time;

    if (elapsed_time >= wait_time) {
        _blink_info.last_blink = current_millis;
        _blink_info.state      = !_blink_info.state;
        if (!_blink_info.state) _blink_info.blink_counter++;
        _led = _blink_info.state ? _color : _background_color;
        PixelManager::update();
    }
}

Pixel& Pixel::shift(long ms) {
    _shift      = millis() + ms;
    _pixel_mode = PixelMode_t::shifted;
    return *this;
}

Pixel& Pixel::off_interval(long ms) {
    _blink_info.off_interval = ms;
    return *this;
}