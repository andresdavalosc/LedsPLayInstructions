# code

On this page, you can look at the codes and follow step by step what every line code does. those codes were built for the hardware I used, here's a list of hardware I used. 
* 4x 16 multiplexer
* 64 touch sensors
* 64 LEDs

The codes are available on Github and here. the codes are written for the Arduino and have comments to know what each line does. 
I wrote 4 codes. 

* draw game - code
* sweeper - code
* whack a mole - code
* song - code



since for 2 (sweeper and whack a mole) them, I didn't use the capacitor sensor library they look different. first, the draw game. 

# drawgame
These are the library needed for everything i used for the project. 

    //libraries for the sensors, sounds(midi) and led
    #include <CapacitiveSensor.h>
    #include <MIDI.h>
    #include <FastLED.h>

this line is needed to start the midi communication, without this it won't work

    //starting the midi
    MIDI_CREATE_DEFAULT_INSTANCE();

We define the number of inputs here, leds and the pin where the led is connected. for intance if you want to connect 8 sensor you just should change n_inputs to 8.

    //defining the sensors inputs, led pin and nulber of leds
    #define n_inputs 64
    #define LED_PIN   13
    #define NUM_LEDS  n_inputs

these are the pins where you send 0 and 1 to the multiplexer. these are outputs and not inputs of the arduino 

    // Multiplexer control pins:
    int muxPin1 = 11;
    int muxPin2 = 10;
    int muxPin3 = 9;
    int muxPin4 = 8;    

this is a very inmportant piece of code. here we define the vhannel and note to 1. the arduino is going to communicate with the live ableton 11 program trough channel 1.

    //set midi channel and note to 1
    byte midiCh = 1;
    byte note = 1;
    byte cc = 1;

these are the pins the output from the multiplexer is connected to, these pins are used for the capacitive library.

    //inputs from the mux to the arduino
    int sensorPin = 2;
    int sensorPin3 = 3;
    int sensorPin4 = 5;
    int sensorPin2 = 6;

tap counter to see how many times someone had touched the led and declared the LEDs

    //tap to know how many times someone has tapped.
    int tap = 0;
    //declaring the leds (library)
    CRGB leds[NUM_LEDS];

I created an array that is n_inputs long so that means that every time you give n_inputs a value this value will also be the length of the touch and total array. touch[] is an empty array at the beginning while total[] is filled with zeros. 

    //array to put every value of every touch sensor inside of it
    long touch[n_inputs] = {};
    long total[n_inputs] = {0};

I used a flag to see when someone has pressed a touch sensor. I used this in the algorithm I wrote at the end of the code. 

    //flag array set to zero, this will be used in the algorythm
    int flag[n_inputs] = {0} ;

sensor pins are the ones connected to the output of the multiplexer and input of the Arduino. the Arduino reads the input and passes it to the capacitive sensor library and this converted value will be stored in AppSense,sapSense2,capSense3, etc. All these pins need also to be connected to pin 4 in the Arduino, you can see the process on project page.

    //cap. sensor library to track if sensor is touched or not
    CapacitiveSensor capSense = CapacitiveSensor( 4, sensorPin  );
    CapacitiveSensor capSense2 = CapacitiveSensor( 4, sensorPin2  );
    CapacitiveSensor capSense3 = CapacitiveSensor( 4, sensorPin3  );
    CapacitiveSensor capSense4 = CapacitiveSensor( 4, sensorPin4  );

Setup is where we set everything up. you can see we start with the serial communication set on 115200. is this important to let it work with the midi library, after that, we set up the fast led library by adding some information like led type, input pin of the LEDs, number of LEDs, and the color order like GRB or RGB. After this, we set up the brightness of the led min is 0 and max 255. We follow this line by clearing everything. We do this because we need to be sure the previous LED of the program is completely removed. We put FastLED.show to make this possible otherwise it won't work. In the end, we declare the multiplexer pins as an output since these are binary codes the Arduino sends to the multiplexer. 

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

Next is the main loop. We declare i for the for loop. the for loop consist of the number of inputs. the loop will do i+1 every time is less than the number of inputs. I am going to be sent as a parameter to the readMuxSingle() function.

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

readMuxSingle function is going to pass this i value as a number to digital write. inside the digital write, we have bitread, this is going to read the number value and return it as a binary code. For example, you have bitRead(5,0). this will read number 5 as a binary code. this will be 0101, after this, it will pick the index 0 of this number so in this case 1. if I write this bitRead(5,3) it will take index 3 so 0 because 0 is the third one in 0101. so basically what digitalWrite(muxPin1, bitRead(number, 0)); is going to do is write to muxPin1 index 0 of number. 

    void readMuxSingle(int number) {
    digitalWrite(muxPin1, bitRead(number, 0));
    digitalWrite(muxPin2, bitRead(number, 1));
    digitalWrite(muxPin3, bitRead(number, 2));
    digitalWrite(muxPin4, bitRead(number, 3));

Here we put all the values we got returned from the multiplexer to the Arduino and store them in the touch array after this we use the map function to remove the high values we got returned and store them in smaller values. this is better to see which sensors were pressing. 

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

if you want to debug and see those values you can use Serial print
 
    //Serial.print(  total[ number]);

After we store everything we call the draw function where we are going to make the LEDs turn on and change color as also the sounds. 

    //calling the draw function and passing the number variable
    Draw(number);

inside the draw function is the algorithm. when the touch we pressed is higher than 4 and the flag is 0 then we continue and send to the Ableton live program a note(i this note changes for every sensor) on channel 1 with volume 127 and after  50ms it will turn off, the tap will increase with 1 and depending what the state of the tap is a led with color will turn on. Since we only have 4 colors we have 4 cases. After the 4th case tap will be set again to zero. Since we put a flag to 1 at the beginning of the if statement the sensor won't send a tone or change color anymore. you need to release the sensor and press it again to change the color. This is because of having an if else statement where we say that if it's released again flag will be turned back to 0.

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
        //flag[i] = 0;

    else if (total[i] < 4)
    {
        flag[i] = 0;
    }
    }

# sweeper 

first, we include the library and define the data pin and number of LEDs. After that we make an array of r[] inside here we write 0,8,16,24,48,etc. the reason for this is that later on, we take this number to create a line for the sweeper. randNumber is created to store the random number we're going to use. 

    //include led library and define the number of leds and pin of input for the leds
    #include <FastLED.h>
    #define DATA_PIN    13
    #define NUM_LEDS    64
    CRGB leds[NUM_LEDS];
    int r[9] = {0, 8, 16, 24, 32, 40, 48, 56, 64};
    long randNumber;
    //change the delay number
    int _delay = 500;

this setup is almost the same as the draw game. the only difference is the baud rate, random function, and fill_solid. the random function gives randNumber a random number to start with. the first fill_solid tells that every 64 led needs to be blue. the second one chooses a random LED from the random function and gives it the color (0,200,33) 

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

main loop

    void loop() {

    for (int l = 7; l > 0; l--) {
        draw(l);
    }
    leds[randNumber] = CRGB(0, 30, 200);
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

inside the loop, we make the animation with an forloop. the forloop decrease by -1  till l is not greater than 0. this l value we send to the draw function. After this, we chose the led and give it back the blue color. After this, we give randNumber another random value.

    for (int l = 7; l > 0; l--) {
    draw(l);
    }
    leds[randNumber] = CRGB(0, 30, 200);
    randNumber = random(NUM_LEDS);

now we're going to do the same but instead of decreasing, we're going to increase till it's lower than 7. After that, we choose the chosen led and give it back the blue color. Now we do delay -2 to make the sweeper go faster. 

    for (int i = 0; i < 7; i++) {
        draw(i);
    }
    FastLED.show();
    leds[randNumber] = CRGB(0, 30, 200);
    randNumber = random(NUM_LEDS);
    _delay -= 2;
    Serial.println(_delay);
    }

in this function, we draw the sweeper by using fill_solid. we tell this library in which row we're going to draw by using r[i]. 

example: fill_solid( leds + r[0], 8, CRGB(220, 37, 127));
r[0] = row 0 because int r[0] = {0, 8, 16, 24, 32, 40, 48, 56, 64};  = 0
8 = how many leds are going to be turned on, in this case 8 
CRGB(220, 37, 127) = turn it in color red

After this, we use fill_solid to turn another led into another color.

    void draw(int i) {

    fill_solid( leds + r[i], 8, CRGB(220, 37, 127));
    FastLED.delay(_delay);
    fill_solid( leds + r[i], 8, CRGB(0, 30, 200));
    //give the new chosen led another color
    leds[randNumber] = CRGB(255, 180, 0);
    }

# whack a mole
This game isn't working with the sensors either. and is programmed to be a demo. 

here we declare and define everything. also, we declare a 2d array to store 2 colors inside of it. 

    //include the library and define the color, order num of leds , randNumber, r_change, etc.
    #include <FastLED.h>
    #define COLOR_ORDER GRB
    #define NUM_LEDS    64
    CRGB leds[NUM_LEDS];
    long randNumber;
    long r_change;
    int r_color=0;
    //put the color values in a 2d array
    int color[2][3]={{220, 37, 127},{255, 180, 0},};

everything is here the same as the other ones, the only difference is that here we define r_change to store a random variable from 0 to 15

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

first, we give random led a color. it's all depending on which value r_color had. if r_color is 0 we give it this color 220, 37, 127 otherwise this is 255, 180, 0. after the delay this led turns back to blue, the background color. after this randNumber and r_change got a new random number. If r_color is 1 ( the color kids are not supposed to press) the function game over will be called. If r_change is bigger or equal then 10 r_color will be changed to 1, this is a way to led the Arduino to decide when the wrong color will be shown on the screen.  

    void loop() { 
    leds[randNumber] = CRGB(color[r_color][0], color[r_color][1], color[r_color][2]) ;
    //fill_solid( leds+randNumber, 1,CRGB(color[r_color][0], color[r_color][1], color[r_color][2]));
    FastLED.show();
    FastLED.delay(1500);
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

when game over is called a game over animation will be shown on the table. After 2seconds the background will be blue again and the game starts again. 
    void gameover(){
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(220, 37, 127);
        FastLED.delay(50);
    }
    FastLED.show();
    FastLED.delay(2000);
    fill_solid( leds, NUM_LEDS, CRGB::Blue);

    }   
# song

Since most of the code is the same as the draw game I won't talk about this part. Go to the drawgame page and read everything there. 

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
    play(number);

    }

Everything is the same as the draw game. The only different thing is. Here I chose a random led and turn it blue.  if you want more explanation go to the draw game page and read the explanation. 

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

if the touch is greater than 4 ( it means someone has touched it) and the flag is 0 and the randNumber is equal to i then it means someone has pressed the led that turned blue. If it is pressed then the flag is turned to 1, send a tone to channel 1 of the midi, turn the led off, wait 5 seconds, and turns the midi off. j increases the value till it's 28 then it's going to reset back to 0. After all, this randNumber will be given another random number.

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


# Extra

to let the midi work you need to be sure the baud rate is set up to 115200 and all the Serial print lines need to be placed in comments otherwise, the communication will fail. 