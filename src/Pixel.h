#pragma once

#include <FastLED.h>

class Pixel {
  public:
    Pixel(CRGB& led);

    void   blink(const CRGB& color, unsigned long interval, unsigned long count = 0);
    void   color(const CRGB& color);
    Pixel& off_interval(unsigned long off_interval);
    Pixel& shift(unsigned long shift);
    Pixel& bgColor(const CRGB& color);

  protected:
    static void vTimer(TimerHandle_t xTimer);
    void set_color(const CRGB& color);
    void start_timer(unsigned long ms);
    bool is_shifted();
    void reset_shift();
    bool is_blinking();

    CRGB&         m_led;
    CRGB          m_color;
    CRGB          m_bgColor = CRGB::Black;
    unsigned long m_counter;
    unsigned long m_count;
    unsigned long m_interval;
    unsigned long m_off_interval;
    unsigned long m_shift = 0;
    bool          m_state = false;
    bool          m_blink = false;

    TimerHandle_t timer_handle = 0;
};
