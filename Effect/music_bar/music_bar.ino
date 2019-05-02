
#include <Adafruit_NeoPixel.h> 
#ifdef __AVR__
#include <avr/power.h> 
#endif              

#define LED_PIN   8 
#define LED_TOTAL 50 
#define LED_HALF  LED_TOTAL/2
#define AUDIO_PIN A0  
#define KNOB_PIN  A1 



Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);  //LED strand objetc

uint16_t gradient = 0; 

uint8_t volume = 0;   
uint8_t last = 0;   

float maxVol = 15;    
float knob = 1023.0;  
float avgVol = 0;   
float avgBump = 0;    

bool bump = false;    


void setup() {  

  Serial.begin(9600);

  strand.begin(); 
  strand.show();  
}


void loop() {  
  volume = analogRead(AUDIO_PIN);      
  knob = analogRead(KNOB_PIN) / 1023.0;
  avgVol = (avgVol + volume) / 2.0;     

  if (volume < avgVol / 2.0 || volume < 15) volume = 0;


  if (volume > maxVol) maxVol = volume;

 
  if (gradient > 1529) {

    gradient %= 1530;


    maxVol = (maxVol + volume) / 2.0;
  }

  
  if (volume - last > avgVol - last && avgVol - last > 0) avgBump = (avgBump + (volume - last)) / 2.0;

  bump = (volume - last) > avgBump;

  Pulse();  

  gradient++;  

  last = volume;

  delay(30);   
}





void Pulse() {

  fade(0.75);  
  if (bump) gradient += 64;


  if (volume > 0) {
    uint32_t col = Rainbow(gradient);

   
    int start = LED_HALF - (LED_HALF * (volume / maxVol));
    int finish = LED_HALF + (LED_HALF * (volume / maxVol)) + strand.numPixels() % 2;


    for (int i = start; i < finish; i++) {


      float damp = float(
                     ((finish - start) / 2.0) -
                     abs((i - start) - ((finish - start) / 2.0))
                   )
                   / float((finish - start) / 2.0);

      strand.setPixelColor(i, strand.Color(
                             split(col, 0) * pow(damp, 2.0) * knob,
                             split(col, 1) * pow(damp, 2.0) * knob,
                             split(col, 2) * pow(damp, 2.0) * knob
                           ));
    }
 
    strand.setBrightness(255.0 * pow(volume / maxVol, 2));
  }

  strand.show();
}


void fade(float damper) {

  if (damper >= 1) damper = 0.99;

  for (int i = 0; i < strand.numPixels(); i++) {

    uint32_t col = (strand.getPixelColor(i)) ? strand.getPixelColor(i) : strand.Color(0, 0, 0);


    if (col == 0) continue;

    float colors[3]; //Array of the three RGB values


    for (int j = 0; j < 3; j++) colors[j] = split(col, j) * damper;


    strand.setPixelColor(i, strand.Color(colors[0] , colors[1], colors[2]));
  }
}


uint8_t split(uint32_t color, uint8_t i ) {

  //0 = Red, 1 = Green, 2 = Blue

  if (i == 0) return color >> 16;
  if (i == 1) return color >> 8;
  if (i == 2) return color >> 0;
  return -1;
}



uint32_t Rainbow(unsigned int i) {
  if (i > 1529) return Rainbow(i % 1530);
  if (i > 1274) return strand.Color(255, 0, 255 - (i % 255));   //violet -> red
  if (i > 1019) return strand.Color((i % 255), 0, 255);         //blue -> violet
  if (i > 764) return strand.Color(0, 255 - (i % 255), 255);    //aqua -> blue
  if (i > 509) return strand.Color(0, 255, (i % 255));          //green -> aqua
  if (i > 255) return strand.Color(255 - (i % 255), 255, 0);    //yellow -> green
  return strand.Color(255, i, 0);                               //red -> yellow
}
