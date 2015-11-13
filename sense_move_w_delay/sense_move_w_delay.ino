/*sense_move_w_delay*/

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;          // variable to store the servo position
int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int on = 0;           // set to 1 during state change
 
void setup() 
{ 
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if((sensorValue < 80) && (on == 0)){
    myservo.write(90);
      if(on == 0){
        Serial.println("on");
        delay(1000);
        on = 1;
      }
  }
  if((sensorValue > 80)&&(on == 1)){
    myservo.write(180);
      if(on == 1){
        Serial.println("off");
        delay(1000);
        on = 0;
      }
  }
} 

