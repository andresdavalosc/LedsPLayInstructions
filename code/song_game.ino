//including the library
#include <CapacitiveSensor.h>
#include <MIDI.h>
#include <FastLED.h>

//starting the midi
MIDI_CREATE_DEFAULT_INSTANCE();

//defining the sensors inputs, led pin and nulber of leds
#define n_inputs 8
#define LED_PIN   13
#define NUM_LEDS  n_inputs

//declaring the leds (library)
CRGB leds[NUM_LEDS];

// Multiplexer control pins:
int muxPin1 = 11;
int muxPin2 = 10;
int muxPin3 = 9;
int muxPin4 = 8;
//int mux = 7;
int randNumber;


//set midi channel and note to 1
byte midiCh = 1;
byte note = 1;
byte cc = 1;

//inputs from the mux to the arduino
int sensorPin = 2;
int sensorPin2 = 3;
int sensorPin3 = 5;
int sensorPin4 = 6;
int tap = 0;

//array to put every value of every touch sensor inside of it
int touch[n_inputs] = {};
long total[n_inputs] = {0};

//flag array set to zero, this will be used in the algorythm
int flag[n_inputs] = {0} ;

int j = 0;

//cap. sensor library to track if sensor is touched or not
CapacitiveSensor capSense = CapacitiveSensor( 4, sensorPin  );
CapacitiveSensor capSense2 = CapacitiveSensor( 4, sensorPin2  );
CapacitiveSensor capSense3 = CapacitiveSensor( 4, sensorPin3  );
CapacitiveSensor capSense4 = CapacitiveSensor( 4, sensorPin4  );



void setup() {

  //staring serial communication
  Serial.begin (115200) ;
  //inserting led pin, num of leds and type of led strip
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  //led brightness
  FastLED.setBrightness(255);
  //clearing all leds when program starts
  FastLED.clear();
  FastLED.show();

  // Set multiplexer control pins pinMode:
  pinMode(muxPin1, OUTPUT);
  pinMode(muxPin2, OUTPUT);
  pinMode(muxPin3, OUTPUT);
  pinMode(muxPin4, OUTPUT);
  //creating a random number
  randNumber = random(NUM_LEDS);

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
    total[number] = map(touch[number], 100, 3000, 0, 5); // change value every time when moving it

  }
  else if (number < 48) {
    touch[number] = capSense3.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it
  }
  else if ( number < 64) {
    touch[number] = capSense4.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }
   //Serial.print(  total[number]);
  //Serial.print("  ");
  
  //calling the play function
   play(number);

}

// Main loop:
void loop() {
  //Serial.println(randNumber); 
  leds[randNumber] = CRGB::Blue;
  FastLED.show();
  // Make variables for for loops:
  for (int i = 0; i < n_inputs; i++) {
    readMuxSingle(i);
  }
  //Serial.println();
  delay(10);
}

void play(int i) {
  if (total[i] > 4 && flag[i] == 0 && i == randNumber)
  {
    flag[randNumber] = 1;
    if (j >= 28) {
      j = 0;
    }
    //sending note, velocity and channel to the midi and after 50ms turning it off
    MIDI.sendNoteOn(j, 127, midiCh);
    leds[randNumber] = CRGB(0, 0, 0);
    FastLED.show();
    delay(5000);
    MIDI.sendNoteOn(j, 0, midiCh);

    j++;
    flag[i] = 0;
    randNumber = random(NUM_LEDS);
    


  }

  //if sensor isnt pressed anymore put flag back to 0 in order to press again the sensor

}
