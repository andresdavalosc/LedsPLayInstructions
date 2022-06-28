# DIY

in this page you can see the process of the project how we managed to let it work and test it at ritmica and heder. Also you can see how i managed to let a sound play when you press the sensor and also how i made the pcb and why it didnt work at the end. 

### Step1: testing the leds

When we decided after the brainstorm what the prototype would do or sound i needed to test first the LED since it was a long time ago i worked with LED. Here you can see how i control the led strip y using the FastLED library.

 <p align="center">
<figure class="video_container">
  <iframe width="700" height="400" src="" frameborder="0" allowfullscreen="true"> </iframe>
</figure>

### Step2: testing the capacitive sensor

I used the capacitive library to test the capacitive sensor and see how it works. The problem in this library is that if you want to use a 64capacitive sensor you will need a lot of repeating code and we don't want that. So what I used are multiplexer to fix this and defining 4 capacitive sensor inputs and a store it in a array. 


### Step3: testing the midi

To test the midi you need several things. First you need to use the midi library and the code I used. Secondly you need all the apps for communication. Loopmidi to create port also hairless MIdI program to make communication from the Arduino to the music program. Thirdly we need the music program. I used Ableton live 11. Here you can search for a drum rack and in every field, you put a piano sound with different sounds. So when you press a sensor it will send it to the Arduino and the Arduino will send it to the hairless program and this will send it to the ability to program. In the code you can see that I write  MIDI.sendNoteOn(i, 127, midiCh);this is the part where I send the note I ( could ben1, 2, 3, etc) to music program. 

YouTube tutorial(min 10:55): https://youtu.be/JZ5yPdoPooU


### step5: building the project

For the prototype, we cut each LED and put it in a row. We do is 8 time, now we have 8 rows. The most important is to connect each Data out(DOUT) to the Data in (DIN) of the next LED. On the backside, we glued 2 cover wires 1 is ground and the other is 5 volt. We do this for each row. After gluing everything we solder all the ground wires on the backside to each other and all the 5v wires to each other. Each ground and 5v of the LED should be soldered to these wires. Warning don't solder the ground or the 5v next to DOUT of the LED to the 5v and ground wires. These shouldn’t be connected to anything 


#### Step6: multiplexer 

For the multiplexer, I will show you the connection. All the sensors should be connected to the 16 inputs of the 4 multiplexers. Because 4x16 = 64. The outputs (4) of this multiplexer we connect to the Arduino 

 //inputs from the mux to the arduino
 int sensorPin = 2;
 int sensorPin3 = 3;
 int sensorPin4 = 5; 
 int sensorPin2 = 6;
 
these outputs should be connected also to pin 4 with a resistor. 

these outputs are defined in the capacitive library. All the control pins (s0, s1, s2, s3 or A, B, C, D) should be connected in parallel and these connections should be connected to the Arduino in these inputs.


 // Multiplexer control pins:
 int muxPin1 = 11;
 int muxPin2 = 10;
 int muxPin3 = 9; 
 int muxPin4 = 8;
 
  

For more questions email me at andres.davalos1@gmail.com