#include <FastLED.h>
#define LED_TYPE WS2811
#define NUM_LEDS 300
#define DATA_PIN 8

CRGB leds[NUM_LEDS];

void setup() { 

  LEDS.addLeds<LED_TYPE,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(150);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(random8(200, 257)); 
    } 
}

void loop() { 
  static uint8_t hue = 0;

  for(int i = 0; i < NUM_LEDS; i++) {

    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
    fadeall();
    FastLED.delay(30);
  }
}
