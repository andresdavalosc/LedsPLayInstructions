# **improvements & recommendations**

#### **intro**
in this chapter i will tell you what you should improve and how ( in my perspectif at least ) you can still think by yourself and figure it out how to improve it aswell. These are just tips to help you. 

#### **hardware**
Since the touch sensors and other things like the Arduino didn't work well I've been thinking of a solution to improve it. firstly, to make it possible to add some games and at the same time touch the sensor. For this you need a microcontroller with multiple cores so that you can process 2 things at the same time. Unfortunately, the Arduino has a single core and cannot be used to provide games like whack a mole or sweeper since you need to do the sweeper animation and also track the touched tile. I would recommend testing or to investigate more about the esp32(dual core). You should avoid any Arduino microcontrollers. 

Now about the sensors, the sensors could be improved by using a sensor ic ( integrated circuit). You have many chips that can be used for this but in my eyes, the cap1203 is the best one cap1203 but this has only 3 inputs if you want 8 or even 15 inputs for the sensors you should look at the cap1298 or MTCH 6102-I. instead of soldering every sensor to the table, you can make a big PCB with the chip. by doing this you don't need the capacitive sensor library anymore and the multiplexer since this ic works with i2c communication.

To improve the games we need extra hardware, in my point of view, you can implement a buzzer or vibration motor to make it more attractive and give the children feedback. my recommendation is to use first the pre-made PCB vibration motor to test it and afterward, you can implement it in a PCB sketch or in the sensor tile you're making.

#### **code**
The code is now specially written for the hardware I'm using. The algorithm I used to make the game will be probably the same so you should look at it and try to understand it. To improve the code you should look first at the hardware you decided to make and remove the libraries you're not using. I'm sure you shouldn't remove the FastLed library since the LEDs need that library to work. I don't know if the code is compatible with the esp32 but I think it is. The library that maybe doesn't work with the esp32 is the midi library. 