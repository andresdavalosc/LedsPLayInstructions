//include led library and define the number of leds and pin of input for the leds
#include <FastLED.h>
#define DATA_PIN    13
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
int r[9] = {0, 8, 16, 24, 32, 40, 48, 56, 64};
long randNumber;
//change the delay number
int _delay = 500;


void setup() {
  //start communication
  Serial.begin(9600);
  //setup the leds
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  //put every led on blue
  fill_solid( leds, NUM_LEDS, CRGB::Blue);
  //brightness of the led
  FastLED.setBrightness(255);
  //pass a random number to randNumber
  randNumber = random(NUM_LEDS);
  //give a random led the color of (0,200,33).
  fill_solid( leds + randNumber, 1, CRGB(0, 200, 33));
  FastLED.show();

}

void loop() {
//forloop for decreasing and inscreasing to move the sweeper.
  for (int l = 7; l > 0; l--) {
    draw(l);
  }
  //chose the previous chosen led and turn it back blue
  leds[randNumber] = CRGB(0, 30, 200);
  //change the random number again
  randNumber = random(NUM_LEDS);

  for (int i = 0; i < 7; i++) {
    draw(i);
  }
  FastLED.show();
  leds[randNumber] = CRGB(0, 30, 200);
  //fill_solid( leds+randNumber, 1, CRGB(0, 30, 200));
  randNumber = random(NUM_LEDS);
  _delay -= 2;
  Serial.println(_delay);
}



void draw(int i) {

  fill_solid( leds + r[i], 8, CRGB(220, 37, 127));
  FastLED.delay(_delay);
  fill_solid( leds + r[i], 8, CRGB(0, 30, 200));
  //fill_solid( leds+randNumber, 1, CRGB(255, 180, 0));
  //give the new chosen led another color
  leds[randNumber] = CRGB(255, 180, 0);
}
