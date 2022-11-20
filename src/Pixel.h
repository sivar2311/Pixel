#pragma once

#include <FastLED.h>

enum PixelMode_t {
    off,
    steady,
    blink,
    shifted
};

struct BlinkInfo_t {
    unsigned long interval;
    unsigned long off_interval;
    unsigned long blink_count;
    unsigned long blink_counter;
    unsigned long last_blink;
    unsigned long shift;
    bool          state;
};

class Pixel {
    friend class PixelManager;

  public:
    Pixel(CRGB&);
    ~Pixel();

    Pixel& blink(const CRGB& color, unsigned long interval, unsigned int count = 0);
    void   color(const CRGB& color);
    Pixel& backgroundColor(const CRGB& color);
    Pixel& shift(long ms);
    Pixel& off_interval(long ms);

  protected:
    void _loop();

  protected:
    CRGB&       _led;
    CRGB        _color;
    CRGB        _background_color = CRGB::Black;
    PixelMode_t _pixel_mode       = PixelMode_t::off;
    BlinkInfo_t _blink_info;
};