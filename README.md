# Autonomous_car

This project is divided into two stages

**First stage:**  

In the first stage it is presented the transformation of an usual RC car to an Arduino RC car.
Thinking about how to start this project I thought it would be easier if a bought a RC car chasis able to withstand added weight and with an already functional steering system and  motor... Big mistake!
The problem: The motor was not powerful enough for the added weight and the steering system did not work as expected, so I had to had to buy a new motor and to include a workaround for the steering system in the Arduino code.
The car chosen is a Luctan S912 which has 29 cm of lenght and 26.5 cm of width (scale 1/12). The total weight including the Jetson nano and batteries is 2241 g

Items:  
1 Battery 3300 mah (14.8V) For the Jetson Nano  
1 Battery 2200 mah (11.1V) For the car  
1 Arduino UNO  
1 Receiver FS-ia6  
2 HC-SR04 Ultrasonic sensors  
1 Boost converter (5-32V) For the Jetson Nano  
MC33886 Motor driver (L298N is not well suited)  
Aluminium plate with 25 cm of lenght and 16 cm of width  
4 new shock absorbers  

**Second stage:**  

In this stage it will be presented how to include an Jetson Nano into our set up and the development of ML model, for the the autonomous driving. (Coming soon)



