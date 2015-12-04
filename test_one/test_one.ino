/*copied from sense_sweep-90
 * simplified to move one servo with no sensor input
 * Dec. 4, 2015
 * Meg
*/

//---------------------------------------------------------------Initializations---------------------------------------------------------------
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
int servoPin = 9;         // servo 1

int sensorPin = A0;       // sensor 1
int sensorValue = 0;      // variable to store the value coming from the sensor

//---------------------------------------------------------------Functions---------------------------------------------------------------
void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{
  for(int i = 0; i < 90; i+=1){
    myservo.write(i);
    delay(40);
  }
}
