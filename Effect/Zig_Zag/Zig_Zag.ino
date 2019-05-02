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
    bpm();
    FastLED.show();  
    FastLED.delay(1000/FRAMES_PER_SECOND); 
  }

void bpm()
{

  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = RainbowColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = ColorFromPalette(palette, (i*2), beat+(i*10));
  }
}
