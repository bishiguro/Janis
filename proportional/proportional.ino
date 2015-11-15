/*proportional*/

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 0;            // variable to store the servo position
int sensorPin = A0;     // sensor 1
int servoPin = 7;       // servo 1
int sensorValue = 0;    // variable to store the value coming from the sensor

void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue > 80){
    int servoValue = map(sensorValue, 0, 600, 0, 90);
    myservo.write(servoValue);
  }
  else{
    if (myservo.read() != 0) {
      myservo.write(0);
    }
  }
  delay(1);
}

