#include <Servo.h>
#include <Arduino.h>

const int min = 2;
const int max = 320;

bool end;
int data = 0;
int serialData =0;

int x = 0;
const int servoPose = 3; //kolik stavu má rameno
const int servoCount = 4; // počet serv

 Servo servo[4]; // pole pro serva 
const byte servoPins [] = {2,3,4,5}; //piny pro serva


// pin 2 - servo1 kleště (není v servoValues)
// pin 3 - servo2 velká vrchní nožka 1 ve servoValues
// pin 4 - servo3 prostřední točítko 2 ve servoValues
//pin 5 - servo4 spodní rotační 3 ve servoValues

//první nižší doleva
// druhé nižší nahorů



int servoValues [7] [3] = {
   {20,50,20},
   {119,112,45}, //dole sběr kuličky
   {167,80,79},  //vhozeni kuličky nahorů
   {120,34,15}, //ne part1 
   {120,34,105},  //ne part2
   {160,72,90},  // ano part1
   {105,65,90}   //ano part2

};

int servoMoves [servoPose] [3] = {
  {2,1,2000}, //nahoru dolluu
  {5,3,700}, //ne
  {5,5,1000}, //ano
  
  


};



void setup() {
  Serial.begin(9600);
  for(int i = 0; i < servoCount;i++) {
  servo[i].attach(servoPins[i]);
  //if(i > 0) servo[i].write(servoValues[0][i -1]);
}
end = true;
}
 
void loop() {
 
   if(end == true) {
      Serial.println("vstup povolen");

           serialData= Serial.read();
 serialData = serialData - '0';
 Serial.println(serialData);
 if((serialData < servoPose +1 || serialData > 0 +1) && serialData != -49 ) {
   end = false;
    data = serialData;
    Serial.println(data);
    Serial.end();
 }
   }
  

   if(end == false) {
int cycle = 0;

for(int j = 0 ; j < servoMoves[data -1][0];j++) {
for(int i = 1; i < servoCount;i++) {

  //Serial.println(servoValues[data][i -1]);
 servo[i].write(servoValues[(servoMoves[data -1][1])+cycle][i -1]);
 //if(cycle ==1 && i == 2) delay(500);
 //if(cycle == 0 && i == 3) delay(500);0

}

cycle++;
if(cycle > 1) cycle=0;

if(j == (servoMoves[data][0] -1)) {
   end = true;
  Serial.begin(9600);

}
delay(servoMoves[data -1][1]);

  }


   }


//x = map(x, min,max,10,170);
//servo[0].write(x);

}

