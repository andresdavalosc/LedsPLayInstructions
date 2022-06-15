//include the library and define the color, order num of leds , randNumber, r_change, etc.
#include <FastLED.h>
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
long randNumber;
long r_change;
int r_color=0;
//put the color values in a 2d array
int color[2][3]={{220, 37, 127},{255, 180, 0}};

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B,13,COLOR_ORDER>(leds, 64).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  fill_solid( leds, NUM_LEDS, CRGB::Blue);
  FastLED.setBrightness(255);
  FastLED.show();
  randNumber = random(NUM_LEDS);
  r_change = random(0,15);
}

void loop() { 
  //give a random led one of the 2 color inside of the 2D color array
  leds[randNumber] = CRGB(color[r_color][0], color[r_color][1], color[r_color][2]) ;
  //fill_solid( leds+randNumber, 1,CRGB(color[r_color][0], color[r_color][1], color[r_color][2]));
  FastLED.show();
  FastLED.delay(1500);
  //turn back the chosen led to blue
  fill_solid( leds+randNumber, 1,CRGB::Blue);
  randNumber = random(NUM_LEDS);
  r_change = random(0,15);
  if(r_color == 1){
    delay(1500);
      gameover();
  }
  if(r_change >= 10){
      r_color = 1;

  }else{

      r_color = 0;

  }
}
    

void gameover(){
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(220, 37, 127);
      FastLED.delay(50);
  }
  FastLED.show();
  FastLED.delay(2000);
  fill_solid( leds, NUM_LEDS, CRGB::Blue);

}
