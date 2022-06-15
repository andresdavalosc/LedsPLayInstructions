//libraries for the sensors, sounds(midi) and led
#include <CapacitiveSensor.h>
#include <MIDI.h>
#include <FastLED.h>

//starting the midi
MIDI_CREATE_DEFAULT_INSTANCE();

//defining the sensors inputs, led pin and nulber of leds
#define n_inputs 64
#define LED_PIN   13
#define NUM_LEDS  n_inputs

// Multiplexer control pins:
int muxPin1 = 11;
int muxPin2 = 10;
int muxPin3 = 9;
int muxPin4 = 8;

//set midi channel and note to 1
byte midiCh = 1;
byte note = 1;
byte cc = 1;

//inputs from the mux to the arduino
int sensorPin = 2;
int sensorPin3 = 3;
int sensorPin4 = 5;
int sensorPin2 = 6;

//tap to know how many times someone has tapped.
int tap = 0;

//declaring the leds (library)
CRGB leds[NUM_LEDS];

//array to put every value of every touch sensor inside of it
long touch[n_inputs] = {};
long total[n_inputs] = {0};

//flag array set to zero, this will be used in the algorythm
int flag[n_inputs] = {0} ;
//long StartValue = 0;

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
}

// Function for accessing individual multiplexer sensors. Input sensor number:
void readMuxSingle(int number) {
  digitalWrite(muxPin1, bitRead(number, 0));
  digitalWrite(muxPin2, bitRead(number, 1));
  digitalWrite(muxPin3, bitRead(number, 2));
  digitalWrite(muxPin4, bitRead(number, 3));


  //  int value = capSense.capacitiveSensor( sampleRate );
  //  return value;

  //storing ever sensor value to the touch and total array
  if (number < 16) {
    touch[number] = capSense.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }
  else if (  number > 15 && number < 32) {
    touch[number] = capSense2.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }
  else if (  number > 31 && number < 48) {
    touch[number] = capSense3.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }
  else if (  number > 47 && number < 64) {
    touch[number] = capSense4.capacitiveSensor( 30 );
    total[number] = map(touch[number], 100, 1000, 0, 5); // change value every time when moving it

  }


  //
 
 //Serial.print(  total[ number]);
//calling the draw function and passing the number variable
  Draw(number);

}

// Main loop:
void loop() {
  // Make variables for forloop:
  int i;

  for (i = 0; i < n_inputs; i++) {
    readMuxSingle(i);

  }
  //Serial.println();
  //delay(10);
}

void Draw(int i ) {
  if (total[i] > 4 && flag[i] == 0)
  {
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
    delay(10);
   // flag[i] = 0;

  //}

  //if sensor isnt pressed anymore put flag back to 0 in order to press again the sensor
  else if (total[i] < 9)
  {
    flag[i] = 0;
  }
  }
}
