/*sense_and_move_v2
Don't read sensor values until finished with 0-90 sweep.
Sweep back to zero.*/

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
int servoPin = 9;         // servo 1

int sensorPin = A0;       // sensor 1
int sensorValue = 0;      // variable to store the value coming from the sensor

void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  
  if(sensorValue > 100) { // if the sensor detects an object
    for(int i = 0; i < 90; i+=1) { // turn 90 degrees so that the paddle appears thick
      myservo.write(i);
      delay(10);
    }
    delay(20);
    
    for(int i = 90; i >=0; i-=1) { // turn 90 degrees back so that the paddle appears thin
      myservo.write(i);
      delay(10);
    }
    delay(20);
  }
}