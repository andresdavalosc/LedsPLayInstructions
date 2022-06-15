# fails during the project

It's really important to read this document, the most important of all this documentation is to not make the same mistake we made. On this page, I will tell you which mistakes we made and how to prevent them from not making the same mistake, this could be a hardware mistake I made our software also tips to not getting stuck while doing the project. 

# arduino

One of the most important pieces of advice I can give you was not to work with the Arduino. The mistake I made is to work with this and continue working with it till the end. The Arduino has 1 core and isn't capable to do 2 tasks at the same time, for this we need a multicore microcontroller. The esp32 is an option but you can explore further and see its C++ compatible to program it as well. 

while doing the sweeper game I found out it's not possible to let the animation run and sense the touch sensor.

# Nets

while I didn't have enough experience with the capacitive sensor library I still thought the net would work since I saw a similar project on the Internet. I've been months testing it and it gave me a good result but sadly for me while putting 64 nets beneath the board it didn't work because there was a lot of interference. I would say to not spend a lot of time with this and skip the nets I used. I would prefer just to buy some existing capacitive sensor chips and place them. What you also could do is use ir sensors and try it out, You will need to change the code. I would recommend just going with the already existing chip and test id since they are qualified for this kind of stuff. If you still think the nets are still an option just consider it a lot of work soldering the cables to the net and also playing the little squares beneath it since it cannot touch the LEDs. 

# Soldering

Soldering took a lot of time while doing the project so I would avoid this kind of work. I would suggest making a PCB on time and implementing everything in it. It took us weeks to finally solder everything. by everything I mean soldering the VCC and GND wire to every led, soldering the data pin from one led to the other, and the cables to the touch sensor. The main reason to avoid this is that you're never sure when they are stuck together or not. even when we thought everything was soldered 1 wire always desolder from the net or led. So if you want to avoid a lot of stress work just make a PCB or just use connectors from one side of the LEDto the other side. 

# multiplexer

the multiplexer had some issues and didn't work as I wanted to work. I first tried to do a 1:64 conversion by using a 4x 1:16 multiplexer and a 1x 1:4 multiplexer and connecting them. but this didn't work so I just used the 1:64 multiplexer and for every output (4) I connected it to the Arduino. if you're trying to do the same and got some problem I would just suggets 1 thing, check every connection and see if some cables aren't loose or disconnected, and please do it good because if you do it quickly like me you could oversee the problem. You can notice this problem when you're looking in the serial monitor of the Arduino to the sensor and you touch 1 but two sensors increase the value.  but I repeat if you want to avoid this problem make a PCB and just solder the multiplexer on it. 

# PCB
When I tried to make a PCB I encountered problems, problems I could fix but because I made the PCB late I couldn't fix it on time. The problem where the footprint of the multiplexer I found on kicad wasn't the right size and I noticed it when it already was printed. So please measure on kicad (or whatever you're using) the size of the component and see if it really could fit on the board. The PCB machine school had isn't that good and professional so it was really difficult to solder everything since it was really small I would say to make the path bigger or just order from jlc PCB they are more professional. Also when you want to use the bottom at the top you need via's and to connect those two you need Voltera Rivets or a tiny copper wire and solder it. This is difficult and not efficient so you need to be aware of this. Volterra Rivets are not available at school so you need to buy them. Overall I would just suggest buying it from china on time because you need to test it and improve it. 

# code
