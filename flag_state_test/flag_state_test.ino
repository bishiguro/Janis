/*flag_state_test
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int servoPin = 11;         // servo 1
int sensorPin = A0;        // sensor 1
int sensorValue = 0;
int timeStart = 0;       // time since movement : for dealing with millis() rollover look at https://www.baldengineer.com/arduino-how-do-you-reset-millis.html
boolean flagState = false;  // false means accessible

void setup()
{
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop()
{
  //  for(int i = 0; i < 90; i+=1){
  //    myservo.write(i);
  //    delay(20);
  //  }
  sensorValue = analogRead(sensorPin);

  if (sensorValue > 80 && !flagState) {
    if (myservo.read() != 90) {
      timeStart = millis();
      flagState = true;
    }
    myservo.write(90);
  }
  if (millis() >= timeStart + 1000) {
    flagState = false;                //one second later (the approximate amount of time it takes to move the servo), release the servo
  }
  if (sensorValue <= 80 && !flagState) {
    myservo.write(0);
  }
  Serial.print("flagState: ");
  Serial.println(flagState);
  Serial.print("millis: ");
  Serial.println(millis());
  Serial.print("timeStart: ");
  Serial.println(timeStart);
}
