#include <FastLED.h>

#define DATA_PIN    8

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         255

void setup() {
  delay(1); 
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
  {
    confetti();
    FastLED.show();  
    FastLED.delay(5); 
  }

void confetti() 
{
  
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random(NUM_LEDS);
  leds[pos] = CHSV(analogRead(A1)/4,255,255);
}
