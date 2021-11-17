#include "NewPing.h"

// Ultrasonic sensor

#define t_pin_fro    8
#define echo_pin_fro 9
#define t_pin_bac    7 
#define echo_pin_bac 6
#define MAX_DISTANCE 400 // distance in mm

NewPing sonar_f(t_pin_fro,echo_pin_fro, MAX_DISTANCE);
NewPing sonar_b(t_pin_bac,echo_pin_bac, MAX_DISTANCE);

float dist_f;
float dist_b;

//Motor A (Speed)
int in1 = 10; 
int in2 = 5;
int RC2 = 4;


//Motor B (Direction)
int in3 = 11; 
int in4 = 3;
int RC1 = 2;

// To activate human control (to implement)
int RC3 = A2;


int Ang = A0; // angle

int deadzA = 30; // In case of fluctuations in the signal!
int deadzB = 20; // In case of fluctuations in the signal!

void setup() {
  Serial.begin(9600);   // 9600 is the baud rate (transference speed)
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(Ang, INPUT);
}
void loop() {
  int ch_1 = pulseIn(RC1,HIGH,25000); // Direction  
  float Angle = analogRead(Ang);
  Angle = map(Angle- 531,-531,492,-190,190);
  int ch_3 = pulseIn(RC3,HIGH,25000); // Direction trick     
  int ch_2 = pulseIn(RC2,HIGH,25000); // Speed 
  int val_1 = dirPWM(ch_1);  
  int val_2 = pulsetoPWM(ch_2)*0.4;  // Only 40% of the total speed
// direction section
  float vel = 0;
  if (abs(val_1 - Angle) < deadzA){
    vel = 0;
    digitalWrite(in3,LOW); // Digital
    analogWrite(in4,vel);  // Digital
  }  
  else if (val_1 < Angle + deadzA){
    vel = 0.7*abs(val_1 + Angle);
    digitalWrite(in3,LOW);  // Digital
    analogWrite(in4,vel);      
  }
  else if (val_1 > Angle - deadzA){
    vel = 0.75*abs(val_1 - Angle);
    digitalWrite(in4,LOW);  // Digital
    analogWrite(in3,vel);      
  }
  else{
    vel = 0;
    digitalWrite(in4,LOW); // Digital
    digitalWrite(in3,LOW);  // Digital      
  }

// Ultrasonic sensors
dist_f = sonar_f.ping_cm(); //9 cm limit front
dist_b = sonar_b.ping_cm(); // 5 cm limit back
  
// To change the polarity in the speed motor  
  if (val_2 < -35){
    digitalWrite(in1,LOW);  // Digital
    analogWrite(in2,abs(val_2));  
  }
  else if (val_2 > 35) {
    digitalWrite(in2,LOW);  // Digital
    analogWrite(in1,val_2);      
  }
  else{
    digitalWrite(in2,LOW); // Digital
    digitalWrite(in1,LOW);  // Digital  
  }

  delay(2);  //2 ---- 500 sonar
  //Serial.print(dist_f);
  //Serial.print('\t');
  //Serial.print(dist_b);
  //Serial.print('\t');
  //Serial.print(ch_2);
  //Serial.print('\t');
  //Serial.print(val_2); 
  //Serial.print('\t');
  //Serial.print(Angle); 
  //Serial.print('\t');
  //Serial.print(vel);      
  //Serial.print('\n');

}  

// Function to transform the pulse to a PWM signal (motor controler signal)
int pulsetoPWM(int pulse) {
  if (pulse > 950) {
    pulse = map(pulse,950,2050,-550,550); 
    pulse = constrain(pulse,-255,255);
  } 
  else{
    pulse = 0;
  }
  if (abs(pulse) <= deadzB){
    pulse = 0;
  }
  return pulse;
}

// Function to transform the pulse to a PWM signal (direction controler signal)
int dirPWM(int pulse) {
  if (pulse > 950) {
    pulse = map(pulse,950,2050,-550,550); 
    pulse = constrain(pulse,-180,180);
  }
  else{
    pulse = 0;
  }
  if (abs(pulse) <= deadzA){
    pulse = 0;
  }
  return pulse;
}
