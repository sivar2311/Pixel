#include <Arduino.h>
#include <Pixel.h>

#include <FastLED.h>

const int    GPIO_LEDS       = 25;
const size_t NUM_LEDS_STRIPE = 6;
CRGB         stripe[NUM_LEDS_STRIPE]{0};

Pixel pixel1(stripe[0]);
Pixel pixel2(stripe[1]);
Pixel pixel3(stripe[2]);
Pixel pixel4(stripe[3]);
Pixel pixel5(stripe[4]);
Pixel pixel6(stripe[5]);

void setup_fastled() {
    FastLED.addLeds<WS2812B, GPIO_LEDS, RGB>(stripe, NUM_LEDS_STRIPE);
    FastLED.show();
}

void blink_all(const CRGB& color, const CRGB& bgColor = CRGB::Black) {
    pixel1.blink(color, 500).bgColor(bgColor);
    pixel2.blink(color, 500).bgColor(bgColor);
    pixel3.blink(color, 500).bgColor(bgColor);
    pixel4.blink(color, 500).bgColor(bgColor);
    pixel5.blink(color, 500).bgColor(bgColor);
    pixel6.blink(color, 500).bgColor(bgColor);
    delay(5000);
}

void runway_right(const CRGB& color) {
    pixel1.blink(color, 100).off_interval(600).shift(0);
    pixel2.blink(color, 100).off_interval(600).shift(100);
    pixel3.blink(color, 100).off_interval(600).shift(200);
    pixel4.blink(color, 100).off_interval(600).shift(300);
    pixel5.blink(color, 100).off_interval(600).shift(400);
    pixel6.blink(color, 100).off_interval(600).shift(500);
    delay(4000);
}


void runway_left(const CRGB& color) {
    pixel1.blink(color, 100).off_interval(600).shift(500);
    pixel2.blink(color, 100).off_interval(600).shift(400);
    pixel3.blink(color, 100).off_interval(600).shift(300);
    pixel4.blink(color, 100).off_interval(600).shift(200);
    pixel5.blink(color, 100).off_interval(600).shift(100);
    pixel6.blink(color, 100).off_interval(600).shift(0);
    delay(4000);
}

void right(const CRGB& color) {
    pixel1.blink(color, 500).shift(0);
    pixel2.blink(color, 500).shift(100);
    pixel3.blink(color, 500).shift(200);
    pixel4.blink(color, 500).shift(300);
    pixel5.blink(color, 500).shift(400);
    pixel6.blink(color, 500).shift(500);
    delay(5000);
}

void left(const CRGB& color) {
    pixel1.blink(color, 500).shift(500);
    pixel2.blink(color, 500).shift(400);
    pixel3.blink(color, 500).shift(300);
    pixel4.blink(color, 500).shift(200);
    pixel5.blink(color, 500).shift(100);
    pixel6.blink(color, 500).shift(0);
    delay(5000);
}

void outer(const CRGB& color) {
    pixel1.blink(color, 500).shift(200);
    pixel2.blink(color, 500).shift(100);
    pixel3.blink(color, 500).shift(0);
    pixel4.blink(color, 500).shift(0);
    pixel5.blink(color, 500).shift(100);
    pixel6.blink(color, 500).shift(200);
    delay(5200);
}

void inner(const CRGB& color) {
    pixel1.blink(color, 500).shift(0);
    pixel2.blink(color, 500).shift(100);
    pixel3.blink(color, 500).shift(200);
    pixel4.blink(color, 500).shift(200);
    pixel5.blink(color, 500).shift(100);
    pixel6.blink(color, 500).shift(0);
    delay(5200);
}

void setup() {
    Serial.begin(115200);
    setup_fastled();
    delay(2000);
}

void loop() {
    blink_all(CRGB::Red);
    blink_all(CRGB::Green, CRGB::Blue);
    runway_right(CRGB::Red);
    runway_left(CRGB::Green);
    right(CRGB::Red);
    left(CRGB::Green);
    inner(CRGB::Blue);
    outer(CRGB::Green);
}