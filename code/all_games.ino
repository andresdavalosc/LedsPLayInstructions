#include <CapacitiveSensor.h>
#include <MIDI.h>
#include <FastLED.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define n_inputs 64
#define LED_PIN   13
#define NUM_LEDS  n_inputs
CRGB leds[NUM_LEDS];
const byte interruptPin = 12;

long r_change;
int r_color = 0;

// Multiplexer control pins:
int muxPin1 = 11;
int muxPin2 = 10;
int muxPin3 = 9;
int muxPin4 = 8;

//midi
byte midiCh = 1;
byte note = 1;
byte cc = 1;

//sensor pins
int sensorPin = 2;
int sensorPin3 = 3;
int sensorPin4 = 5;
int sensorPin2 = 6;
int tap = 0;
int state = 0;
int touch[n_inputs] = {};
long total[n_inputs] = {0};
int flag[n_inputs] = {0} ;

int r[9] = {0, 8, 16, 24, 32, 40, 48, 56, 64};
int color[2][3] = {{220, 37, 127}, {255, 180, 0},};

long randNumber;
int _delay = 100;
CapacitiveSensor capSense = CapacitiveSensor( 4, sensorPin  );
CapacitiveSensor capSense2 = CapacitiveSensor( 4, sensorPin2  );
CapacitiveSensor capSense3 = CapacitiveSensor( 4, sensorPin3  );
CapacitiveSensor capSense4 = CapacitiveSensor( 4, sensorPin4  );




void setup() {
  Serial.begin (115200) ;
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  FastLED.clear();
  FastLED.show();

  // Set multiplexer control pins pinMode:
  pinMode(muxPin1, OUTPUT);
  pinMode(muxPin2, OUTPUT);
  pinMode(muxPin3, OUTPUT);
  pinMode(muxPin4, OUTPUT);

  randNumber = random(7);
  r_change = random(0, 15);
  //pinMode(interruptPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), blink, HIGH);

}

// Function for accessing individual multiplexer sensors. Input sensor number:
void readMuxSingle(int number) {
  digitalWrite(muxPin1, bitRead(number, 0));
  digitalWrite(muxPin2, bitRead(number, 1));
  digitalWrite(muxPin3, bitRead(number, 2));
  digitalWrite(muxPin4, bitRead(number, 3));

  if (number < 16) {
    touch[number] = capSense.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }
  else if (number < 32) {
    touch[number] = capSense2.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }
  else if (number < 48) {
    touch[number] = capSense3.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it
  }
  else if ( number < 64) {
    touch[number] = capSense4.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }

  //Serial.print(total[number]);
  //Serial.print("\t");
  //Serial.print(  total2[number]);
  //Serial.print("\t");
  if (state == 0) {
    DrawFunction(number);
  }
  else if (state ==  1) {
      Sweeper(number);
  }
  else if (state == 1) {
    //WhackaMole(number);
  }

}

// Main loop:
void loop() {
  // Make variables for for loops:
  for (int i = 0; i < n_inputs; i++) {
    readMuxSingle(i);

  }
   //Serial.println();
  delay(10);
}

//---------------------DRAW

void DrawFunction(int i ) {
  if (total[i] > 9 && flag[i] == 0)
  {
    Serial.println("Touched");
    flag[i] = 1;

    //sending note, velocity and channel to the midi and after 50ms turning it off
     MIDI.sendNoteOn(i, 127, midiCh);
    delay(50);
     MIDI.sendNoteOn(i, 0, midiCh);

    tap++;
    switch (tap) {
      case 1:
        leds[i] = CRGB ( 0, 0, 255);
        break;
      case 2:
        leds[i] = CRGB ( 0, 255, 0);
        break;
      case 3:
        leds[i] = CRGB ( 255, 0, 0);
        break;
      case 4:
        leds[i] = CRGB ( 90, 40, 50);
        tap = 0;
        break;
    }
    FastLED.show();



  }

  //if sensor isnt pressed anymore put flag back to 0 in order to press again the sensor
  else if (total[i] < 9)
  {
    // Serial.println("Released");
    flag[i] = 0;
  }
}

//---------------------SWEEPER

void Sweeper(int x) {
  for (int l = 7; l > 0; l--) {
    drawSweeper(l);
  }

  for (int i = 0; i < 7; i++) {
    drawSweeper(i);
  }
  FastLED.show();
  if (touch[x] > 9 && x == randNumber) {
    Serial.println("touched");
    leds[randNumber] = CRGB(0, 30, 200);
    randNumber = random(7);
    //    _delay -= 2;
  }

}

void drawSweeper(int i) {
  fill_solid( leds + r[i], 8, CRGB(220, 37, 127));
  FastLED.delay(_delay);
  fill_solid( leds + r[i], 8, CRGB(0, 30, 200));
  leds[randNumber] = CRGB(255, 180, 0);
}


//---------------------WHACK A MOLE

void WhackaMole(int z) {
  leds[randNumber] = CRGB(color[r_color][0], color[r_color][1], color[r_color][2]) ;
  FastLED.show();
  if (touch[z] > 2 && z == randNumber) {
        Serial.println("Touched");
    if (r_color == 1) {
      gameover();
    }
    else {
      leds[randNumber] = CRGB::Green;
      FastLED.delay(500);
      leds[randNumber] = CRGB::Red;
      FastLED.delay(500);
      leds[randNumber] = CRGB::Green;
      FastLED.delay(500);
      leds[randNumber] = CRGB::Red;
      FastLED.delay(500);

    }
  } else {
    r_change = random(0, 15);
  }
  if (r_change >= 10) {
    r_color = 1;
  }
  FastLED.delay(1000);
  leds[randNumber] = CRGB::Black;
  randNumber = random(NUM_LEDS);



}

void gameover() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(220, 37, 127);
    FastLED.delay(50);
  }
  FastLED.show();
  FastLED.delay(5000);
  fill_solid( leds, NUM_LEDS, CRGB::Blue);

}
//
//void blink() {
//  state++;
//  if (state >= 3) {
//    state = 0;
//  }
//}
