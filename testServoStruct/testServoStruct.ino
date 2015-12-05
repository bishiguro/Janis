#include <Servo.h>
#include <servoStruct.h>

//servoUnit servo1;
//Servo servo2;

const int NUM_SERVOS = 12;
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
Servo servos[NUM_SERVOS];
servoUnit servoUnits[NUM_SERVOS];

servoUnit createServo(int pin) {
  servoUnit myServo;
  myServo.reverse = 0;
  myServo.pos = 0;
  myServo.pin = pin;
  return myServo;
}

void servoSetup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
  }
}

void servoWrite(servoUnit myServo, int pos) {
  myServo.pos = pos;
  
  servos[servoPins[myServo.pin]-2].write(pos);
}

void moveServo(servoUnit myServo) {
  if (myServo.reverse) {
    if (myServo.pos < 90) {
      servoWrite(myServo, myServo.pos - 1);
    }
    else {
      myServo.reverse = 1;
    }
  }
  else {
    servoWrite(myServo, myServo.pos + 1);
  }
}

void setup() 
{
  Serial.begin(9600);
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoUnits[i] = createServo(servoPins[i]); 
  }
  servoSetup();
} 

void loop() 
//main loop
{
  for (int i = 0; i < 90; i++) {
    servoWrite(servoUnits[5], i);
    delay(20);
    // Serial.print(servo1.pos);
  }
  for (int i = 90; i > 0; i--) {
    servoWrite(servoUnits[5], i);
    delay(20);
  }
}

