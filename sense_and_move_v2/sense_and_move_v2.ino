/*sense_and_move_v2
Don't read sensor values until finished with 0-90 sweep.
Sweep back to zero.*/

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int pos = 0;              // variable to store the servo position
int sensorPin = A0;       // sensor 1
int servoPin = 7;         // servo 1
int sensorValue = 0;      // variable to store the value coming from the sensor
boolean sensing = true;   // boolean value, true if currerntly sensing
 
void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{ 
  Serial.println(sensorValue);
  if (sensing){
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  }
  
  //might need to add something in to delay and/or reset to zero to prevent jerkiness
  
  if(sensorValue > 80) {
    
    sensing = false;
    sensorValue = 0;
    
    for(int i = 0; i < 90; i+=1) {
      myservo.write(i);
      delay(10);
    }
    delay(20);
    for(int i = 90; i >=0; i-=1) {
      myservo.write(i);
      delay(10);
    }
    
    sensing = true;
  }
}

