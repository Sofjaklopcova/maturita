#include <Servo.h>
#include <Arduino.h>

const int min= 2;  //
const int max = 160; //

bool end;
int data = 0;
int serialData =0;

bool changeMode;
int mode;
const int servoPose = 6; //kolik stavu má rameno
const int servoCount = 4; // počet serv

 Servo servo[4]; // pole pro serva 
const byte servoPins [] = {2,3,4,5}; //piny pro serva


// pin 2 - servo1 kleště (není v servoValues)
// pin 3 - servo2 velká vrchní nožka 1 ve servoValues
// pin 4 - servo3 prostřední točítko 2 ve servoValues
//pin 5 - servo4 spodní rotační 3 ve servoValues

//první nižší doleva
// druhé nižší nahorů

// servo0 20

 int servoValues [13] [3] = {
   {20,50,20},  //puvodni stav 
   {170,80,45}, //dole sběr kuličky cast1
   {123,113,45}, //dolu sběr kuličky cast2
   {170,80,45},  //vhozeni kuličky nahorů cast1
   {170,80,86}, // vhozeni kuličky nahorů cast2
   {120,34,15}, //ne cast1
   {120,34,90},  //ne cast2
   {160,72,120},  // ano cast1
   {105,65,120},  //ano cast2
   {168,20,30}, //tanecek cast1
   {143,121,30}, //tanecek cast2
   {158,50,136}, //uklona cast1
   {123,130,133},  //uklona cast2
};

int servoMoves [servoPose] [3] = {
  {2,1,500}, //dolu ke kulice 1
  {2,3,500}, //nahoru ke kulice 2
  {5,5,700}, //ne  3
  {5,7,1000}, //ano  4 
  {5,9,660},  //tanecek 5
  {3,11,1000}, //uklona
};

void move(int data) {
  int cycle = 0;
for(int j = 0 ; j < servoMoves[data][0];j++) {
for(int i = 1; i < servoCount;i++) servo[i].write(servoValues[(servoMoves[data][1])+cycle][i -1]);
cycle++;
if(cycle > 1) cycle=0;
if(j == (servoMoves[data][0] -1)) {
  if(data == 0 || data == 1) {
  changeMode = true;
  mode = data;
 }
   end = true;
  Serial.begin(9600);
}
delay(servoMoves[data][2]);
  }
}



void setup() {
  Serial.begin(9600);
  for(int i = 0; i < servoCount;i++) {
  servo[i].attach(servoPins[i]);
 // if(i > 0) servo[i].write(servoValues[0][i -1]);
 //else servo[i].write(150);
}
end = true;
changeMode = false;
}
 
void loop() {
 
   if(end == true) {
   // Serial.println("vstup povolen");
        String read = Serial.readString();
 serialData = read.toInt();
 //Serial.println(changeMode);


 if((serialData < servoPose && serialData > 0 && changeMode == false) ||
  (serialData < max && serialData > min && changeMode == true)) {
Serial.println(serialData);
 if(changeMode == false) data = serialData -1;
 if(changeMode) data = map(serialData, min,max,5,170);
   end = false;
    Serial.end();
 }
   
   }

   if(end == false) {
if(changeMode) {
servo[0].write(data);
Serial.println(data);
delay(500);
if((data < 30 && mode == 0) || (data > 50 && mode == 1)) {
 if(mode == 1) move(5);
 if(mode == 0) {
  end = true;
  Serial.begin(9600);
 }
   changeMode = false;
}
else {
  end = true;
Serial.begin(9600);
}

}

else if (changeMode == false) {
move(data);
   }
}
}

