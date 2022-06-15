# fails during the project

It's really important to read this document, the most important of all this documentation is to not make the same mistake we made. On this page, I will tell you which mistakes we made and how to prevent them from not making the same mistake, this could be a hardware mistake I made our software also tips to not getting stuck while doing the project. 

# arduino

One of the most important pieces of advice I can give you was not to work with the Arduino. The mistake I made is to work with this and continue working with it till the end. The Arduino has 1 core and isn't capable to do 2 tasks at the same time, for this we need a multicore microcontroller. The esp32 is an option but you can explore further and see its C++ compatible to program it as well. 

while doing the sweeper game I found out it's not possible to let the animation run and sense the touch sensor.

# Nets

while I didn't have enough experience with the capacitive sensor library I still thought the net would work since I saw a similar project on the Internet. I've been months testing it and it gave me a good result but sadly for me while putting 64 nets beneath the board it didn't work because there was a lot of interference. I would say to not spend a lot of time with this and skip the nets I used. I would prefer just to buy some existing capacitive sensor chips and place them. What you also could do is use ir sensors and try it out, You will need to change the code. I would recommend just going with the already existing chip and test id since they are qualified for this kind of stuff. If you still think the nets are still an option just consider it a lot of work soldering the cables to the net and also playing the little squares beneath it since it cannot touch the LEDs. 

# Soldering

Soldering took a lot of time while doing the project 

# multiplexer
# Pcb
# code
