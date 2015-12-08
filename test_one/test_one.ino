/*copied from sense_sweep-90
 * simplified to move one servo with no sensor input
 * Dec. 4, 2015
 * Meg
*/

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
int servoPin = 12;         // servo 1

void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{
  for(int i = 0; i < 90; i+=1){
    myservo.write(i);
    delay(20);
  }
}
