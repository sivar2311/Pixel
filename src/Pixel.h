#pragma once

#include <FastLED.h>

enum PixelMode_t {
    off,
    steady,
    blink
};

struct BlinkInfo_t {
    unsigned long interval      = 0;
    unsigned long blink_count   = 0;
    unsigned long blink_counter = 0;
    unsigned long last_blink    = 0;
    bool          state         = false;
};

class Pixel {
    friend class PixelManager;

  public:
    Pixel(CRGB&);
    ~Pixel();

    Pixel& blink(const CRGB& color, unsigned long interval, unsigned int count = 0);
    void   color(const CRGB& color);
    void   backgroundColor(const CRGB& color);
    void   shift(long ms);

  protected:
    void _loop();

  protected:
    CRGB&       _led;
    CRGB        _color;
    CRGB        _background_color = CRGB::Black;
    PixelMode_t _pixel_mode       = PixelMode_t::off;
    BlinkInfo_t _blink_info;
};