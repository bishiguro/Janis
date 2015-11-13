/*sense_and_move*/

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
 
void setup() 
{ 
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue < 80){
    myservo.write(90);
  }
  else{
    myservo.write(180);
  }
} 

