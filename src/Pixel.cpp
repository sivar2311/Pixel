#include "Pixel.h"

#include "PixelManager.h"

// public functions

Pixel::Pixel(CRGB& led)
    : led(led) {
    PixelManager::add(this);
}

Pixel::~Pixel() {
    PixelManager::remove(this);
}

Pixel& Pixel::blink(const CRGB& color, unsigned long interval, unsigned int count) {
    this->pixel_color        = color;
    this->pixel_bg_color     = CRGB::Black;
    this->blink_on_interval  = interval;
    this->blink_off_interval = interval;
    this->blink_counter      = 0;
    this->blink_count        = count;
    this->pixel_mode         = PM_BLINK;
    this->pixel_state        = false;
    this->last_millis        = 0;
    return *this;
}

Pixel& Pixel::color(const CRGB color) {
    this->pixel_state = false;
    this->pixel_color = color;
    this->pixel_mode  = PM_PERMANENT;
    return *this;
}

Pixel& Pixel::shift(unsigned long ms) {
    this->shift_time = millis() + ms;
    return *this;
}

Pixel& Pixel::bgColor(const CRGB bgColor) {
    this->pixel_bg_color = bgColor;
    return *this;
}

Pixel& Pixel::off_interval(unsigned long interval) {
    this->blink_off_interval = interval;
    return *this;
}

// clean code helper functions

inline bool Pixel::pixel_is_shifted() {
    if ((shift_time > 0) && (millis() < shift_time)) return true;
    shift_time = 0;
    return false;
}

inline bool Pixel::pixel_is_in_blink_mode() {
    return pixel_mode == PM_BLINK;
}

inline bool Pixel::pixel_is_not_in_blink_mode() {
    return pixel_mode != PM_BLINK;
}

inline bool Pixel::pixel_is_in_permanent_mode() {
    return pixel_mode == PM_PERMANENT;
}

inline bool Pixel::pixel_is_not_in_permanent_mode() {
    return pixel_mode != PM_PERMANENT;
}

inline unsigned long Pixel::get_wait_time() {
    return pixel_state ? blink_on_interval : blink_off_interval;
}

inline bool Pixel::blink_time_reached() {
    if (last_millis == 0) {
        last_millis = millis();
        return true;
    }

    if (millis() - last_millis >= get_wait_time()) {
        last_millis = millis();
        return true;
    }
    return false;
}

inline bool Pixel::blink_time_not_reached() {
    return !blink_time_reached();
}

inline void Pixel::set_pixel_color_to_current_blink_state() {
    CRGB& color = pixel_state ? pixel_color : pixel_bg_color;
    set_pixel_color(color);
}

inline void Pixel::flip_state() {
    pixel_state = !pixel_state;
}

inline void Pixel::increment_blink_counter() {
    if (blink_count > 0 && pixel_state == false) blink_counter++;
}

inline bool Pixel::blink_counter_is_at_maximum() {
    if (!blink_count) return false;
    return blink_count == blink_counter;
}

inline void Pixel::stop_blinking() {
    pixel_mode = PM_OFF;
}

inline bool Pixel::state_is_off() {
    return pixel_state == false;
}

inline bool Pixel::state_is_on() {
    return pixel_state == true;
}

inline void Pixel::set_pixel_color(const CRGB& color) {
    led = color;
    PixelManager::force_update();
}

// work functions

void Pixel::handle_blink_mode() {
    if (blink_time_not_reached()) return;

    flip_state();
    set_pixel_color_to_current_blink_state();

    increment_blink_counter();
    if (blink_counter_is_at_maximum()) stop_blinking();
}

void Pixel::handle_permanent_mode() {
    if (state_is_off()) {
        set_pixel_color(pixel_color);
        pixel_state = true;
    }
}

void Pixel::_loop() {
    if (pixel_is_shifted()) return;
    if (pixel_is_in_blink_mode()) handle_blink_mode();
    if (pixel_is_in_permanent_mode()) handle_permanent_mode();
}
