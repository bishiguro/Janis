/*sense_and_move
Simplest deployment of single paddle moving if it detecs an object from a sensor*/

//---------------------------------------------------------------Initializations---------------------------------------------------------------
#include <Servo.h> 
 
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
  sensorValue = analogRead(sensorPin); //read sensor value
  Serial.println(sensorValue); //print value for debugging
  if(sensorValue < 80){ //80 is ballpark value for when an object is reliably detected
    myservo.write(90);
  }
  else{
    myservo.write(180); //180 is default
  }
} 

