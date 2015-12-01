/*Proportional Control
The closer the object is to the paddle's sensor, the more it moves. Calibration is still necessary*/

//---------------------------------------------------------------Libraries and Packages---------------------------------------------------------------
#include <Servo.h> 

//---------------------------------------------------------------Initializations--------------------------------------------------------------- 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 0;            // variable to store the servo position
int sensorPin = A0;     // sensor 1
int servoPin = 7;       // servo 1
int sensorValue = 0;    // variable to store the value coming from the sensor

//---------------------------------------------------------------Functions---------------------------------------------------------------
void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue > 80){ //80 is ballpark value for when an object is reliably detected
    int servoValue = map(sensorValue, 0, 600, 0, 90); //maps sensor's values proportionally to degrees between 0 and 90
    myservo.write(servoValue);
  }
  else{
    if (myservo.read() != 0) { //if no value is read, move to 0 (This fidgets around constantly, needs some editing)
      myservo.write(0);
    }
  }
  delay(1);
}

