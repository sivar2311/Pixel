#pragma once

#include <FastLED.h>

class Pixel {
    friend class PixelManager;

  public:
    Pixel(CRGB& led);
    ~Pixel();

    Pixel& blink(const CRGB& color, unsigned long interval, unsigned int count = 0);
    Pixel& color(const CRGB color);
    Pixel& shift(unsigned long ms);
    Pixel& bgColor(const CRGB bgColor);
    Pixel& off_interval(unsigned long interval);

  protected:
    enum PixelMode_t {
        PM_OFF,
        PM_PERMANENT,
        PM_BLINK
    };

    CRGB&       led;
    CRGB        pixel_color;
    CRGB        pixel_bg_color;
    PixelMode_t pixel_mode;

    unsigned long shift_time;
    unsigned long blink_on_interval;
    unsigned long blink_off_interval;
    bool          pixel_state;
    unsigned long blink_count;
    unsigned long blink_counter;
    unsigned long last_millis;

  protected:
    // clean code helper functions

    inline bool          pixel_is_shifted();
    inline bool          pixel_is_in_blink_mode();
    inline bool          pixel_is_not_in_blink_mode();
    inline bool          pixel_is_in_permanent_mode();
    inline bool          pixel_is_not_in_permanent_mode();
    inline unsigned long get_wait_time();
    inline bool          blink_time_reached();
    inline bool          blink_time_not_reached();
    inline void          set_pixel_color_to_current_blink_state();
    inline void          flip_state();
    inline void          increment_blink_counter();
    inline bool          blink_counter_is_at_maximum();
    inline void          stop_blinking();
    inline bool          state_is_on();
    inline bool          state_is_off();
    inline void          set_pixel_color(const CRGB& color);

    // work functions

    void handle_blink_mode();
    void handle_permanent_mode();
    void _loop();
};