#include <Servo.h>
#include <servoStruct.h>

servoUnit servo1;
Servo servo2;

servoUnit createServo(int pin) {
  Servo servo;
  servo.attach(pin);
  servo.write(0);

  servoUnit myServo;
  myServo.servo = servo;

  myServo.reverse = 0;
  myServo.pos = 0;
  myServo.pin = pin;
  return myServo;
}

void servoWrite(servoUnit myServo, int pos) {
  myServo.pos = pos;
  myServo.servo.write(pos);
  Serial.print(myServo.servo.read());
}

void move(servoUnit myServo) {
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
  servoUnit servo1 = createServo(3);
  servo2.attach(3);
} 

void loop() 
//main loop
{
  for (int i = 0; i < 90; i++) {
    servoWrite(servo1, i);
    servo2.write(i);
    delay(20);
    // Serial.print(servo1.pos);
  }
  for (int i = 90; i > 0; i--) {
    servoWrite(servo1, i);
    servo2.write(i);
    delay(20);
  }
}

