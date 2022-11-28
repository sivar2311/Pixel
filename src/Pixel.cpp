#include "Pixel.h"

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

Pixel::Pixel(CRGB& led)
    : m_led(led) {
}

Pixel& Pixel::shift(unsigned long shift) {
    m_shift = shift;
    return *this;
}

void Pixel::blink(const CRGB& color, unsigned long interval, unsigned long count) {
    m_color    = color;
    m_interval = interval;
    m_count    = count;
    m_counter  = 0;
    m_blink    = true;
    if (!m_off_interval) m_off_interval = interval;

    if (m_shift) {
        start_timer(m_shift);
    } else {
        m_state = true;
        set_color(m_color);
        start_timer(m_interval);
    }
}

void Pixel::color(const CRGB& color) {
    m_blink = false;
    m_color = color;

    if (m_shift) {
        start_timer(m_shift);
    } else {
        set_color(color);
        m_state = true;
    }
}

Pixel& Pixel::off_interval(unsigned long off_interval) {
    m_off_interval = off_interval;
    return *this;
}

Pixel& Pixel::bgColor(const CRGB& color) {
    m_bgColor = color;
    return *this;
}

void Pixel::vTimer(TimerHandle_t xTimer) {
    Pixel* pixel = (Pixel*)pvTimerGetTimerID(xTimer);

    if (pixel->is_shifted()) {
        pixel->reset_shift();
        if (pixel->is_blinking()) {
            pixel->start_timer(pixel->m_interval);
            pixel->set_color(pixel->m_color);
            pixel->m_state = true;
        } else {
            pixel->set_color(pixel->m_color);
            pixel->m_state = true;
        }
    } else {
        if (pixel->is_blinking()) {
            pixel->m_state = !pixel->m_state;
            CRGB color     = pixel->m_state ? pixel->m_color : pixel->m_bgColor;
            pixel->set_color(color);
            if (!pixel->m_state) pixel->m_counter++;

            if (pixel->m_count && pixel->m_count == pixel->m_counter) {
                pixel->m_counter = 0;
                return;
            }
            pixel->start_timer(pixel->m_state ? pixel->m_interval : pixel->m_off_interval);
        } 
    }
}

void Pixel::set_color(const CRGB& color) {
    m_led = color;
    FastLED.show();
}

void Pixel::start_timer(unsigned long ms) {
    if (!timer_handle) {
        timer_handle = xTimerCreate("Pixel", pdMS_TO_TICKS(ms), pdFALSE, this, vTimer);
    } else {
        xTimerChangePeriod(timer_handle, pdMS_TO_TICKS(ms), 0);
    }
    xTimerStart(timer_handle, 0);
}

bool Pixel::is_shifted() {
    return m_shift;
}

void Pixel::reset_shift() {
    m_shift = 0;
}

bool Pixel::is_blinking() {
    return m_blink;
}
