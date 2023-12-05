#include <Servo.h>
#include <Arduino.h>

int data = 0;
const int servoPose = 3; //kolik stavu má rameno
const int servoCount = 4; // počet serv

 Servo servo[4]; // pole pro serva 
const byte servoPins [] = {2,3,4,5}; //piny pro serva


// pin 2 - servo1 kleště (není v servoValues)
// pin 3 - servo2 velká vrchní nožka 1 ve servoValues
// pin 4 - servo3 prostřední točítko 2 ve servoValues
//pin 5 - servo4 spodní rotační 3 ve servoValues


int servoValues [servoPose] [3] = {
   {0,0,0}, // původní stav
   {119,112,45},
   {79,80,167},
}; // {20,167,80,79}


void setup() {
  Serial.begin(9600);
  for(int i = 0; i < servoCount;i++) {
  servo[i].attach(servoPins[i]);
  if(i > 0) servo[i].write(servoValues[0][i -1]);
}
}
 
void loop() {
  delay(500);
data = Serial.read();
data = data - '0';
//Serial.println(data);
if(data < servoPose && data > -1) {
for(int i = 1; i < servoCount;i++) {
  Serial.println(servoValues[data][i -1]);
 servo[i].write(servoValues[data][i -1]);

}
}
  
}

