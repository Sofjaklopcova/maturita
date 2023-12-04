#include <Servo.h>
#include <Arduino.h>

Servo myservo; 
Servo myservo2; 
Servo myservo3;  // create servo object to control a servo
Servo myservo4; 

// twelve servo objects can be created on most boards

int pos = 3;    // variable to store the servo position

void setup() {
  myservo.attach(2);
  myservo2.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(4);
  myservo4.attach(5);
}
 

void loop() {

  
myservo.write(20); 
  myservo2.write(167); 
  myservo3.write(80); 
  myservo4.write(79); 

 /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  } 
  */
}

