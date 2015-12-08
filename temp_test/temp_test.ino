/*temp_test
*/

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
int servoPin = 11;         // servo 1

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
  if (millis() % 10000 < 5000){
    myservo.write(90);
  }
  Serial.println("loop");
  if (millis() % 10000 >= 5000){
    myservo.write(0);
  }
}
