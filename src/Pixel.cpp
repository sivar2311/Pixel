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

    _color                    = color;
    _blink_info.interval      = interval;
    _blink_info.blink_count   = count;
    _blink_info.blink_counter = 1;
    _blink_info.last_blink    = millis();
    _blink_info.state         = true;
    _background_color         = CRGB::Black;

    _led = _color;

    PixelManager::update();
    return *this;
}

void Pixel::color(const CRGB& color) {
    _pixel_mode = steady;
    _color      = color;

    _led = color;

    PixelManager::update();
}

void Pixel::backgroundColor(const CRGB& color) {
    _background_color = color;
}

void Pixel::_loop() {
    if (_pixel_mode != PixelMode_t::blink) return;

    if (_blink_info.blink_count && _blink_info.blink_counter > _blink_info.blink_count) {
        _pixel_mode = PixelMode_t::off;
        _led        = _background_color;
        PixelManager::update();
    }

    unsigned long current_millis = millis();

    if (current_millis - _blink_info.last_blink >= _blink_info.interval) {
        _blink_info.last_blink = current_millis;
        _blink_info.state      = !_blink_info.state;
        if (!_blink_info.state) _blink_info.blink_counter++;
        _led = _blink_info.state ? _color : _background_color;
        PixelManager::update();
    }
}

void Pixel::shift(long ms) {
    _blink_info.last_blink -= ms;
}