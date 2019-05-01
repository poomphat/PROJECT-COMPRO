#include <FastLED.h>

#define DATA_PIN    8

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120




void setup() {
  delay(3000); 
  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
  {
    sinelon();
    FastLED.show();  
    FastLED.delay(1000/FRAMES_PER_SECOND); 
  }

void sinelon()
{
    static uint8_t hue;
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = beatsin16( 7, 0, NUM_LEDS-1 );
  leds[pos] += CHSV(hue++, 255, 255);
}
