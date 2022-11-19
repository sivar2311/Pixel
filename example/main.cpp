#include <Arduino.h>

#include <Pixel.h>

const size_t NUM_LEDS_STRIPE_1 = 3;
const size_t NUM_LEDS_STRIPE_2 = 3;

CRGB stripe_1[NUM_LEDS_STRIPE_1]{0};
CRGB stripe_2[NUM_LEDS_STRIPE_2]{0};

Pixel pixel(stripe_1[0]);

void setup_fastled() {
    FastLED.addLeds<WS2812B, 25, RGB>(stripe_1, NUM_LEDS_STRIPE_1);
    FastLED.addLeds<WS2812B, 26, RGB>(stripe_2, NUM_LEDS_STRIPE_2);
    FastLED.setBrightness(64);
    FastLED.show();
}

void black_to_red() {
    pixel.blink(CRGB::Red, 250, 10);
    delay(6000);
    pixel.color(CRGB::Red);
    delay(2000);
}

void red_to_green() {
    pixel.blink(CRGB::Red, 250, 10).backgroundColor(CRGB::Green);
    delay(7000);
}

void green_to_blue() {
    pixel.blink(CRGB::Green, 250, 10).backgroundColor(CRGB::Blue);
    delay(7000);
}

void blue_to_red() {
    pixel.blink(CRGB::Blue, 250, 10).backgroundColor(CRGB::Red);
    delay(7000);
}

void setup() {
    setup_fastled();
    black_to_red();
}

void loop() {
    red_to_green();
    green_to_blue();
    blue_to_red();
}
