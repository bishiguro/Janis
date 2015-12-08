/*sense_move_w_delay
Similar to sense_and_move, but now state dependent. Rather than moving to 90 and back if an object is detected, the paddle changes state depending on the state it 
is currently in.
If 90, move to 0
If 0, move to 90
*/


//---------------------------------------------------------------Initializations---------------------------------------------------------------
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
int pos = 0;          // variable to store the servo position
int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int on = 0;           // set to 1 during state change


//---------------------------------------------------------------Functions---------------------------------------------------------------
void setup() 
{ 
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
void loop() 
{ 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if((sensorValue < 80) && (on == 0)){ //80 is ballpark value for if an event is detected. On is state of paddle
    myservo.write(90); //move paddle
      if(on == 0){
        Serial.println("on");
        delay(1000);
        on = 1; //update state
      }
  }
  if((sensorValue > 80)&&(on == 1)){ //80 is ballpark value for if an event is detected. On is state of paddle
    myservo.write(180); //move paddle
      if(on == 1){
        Serial.println("off");
        delay(1000);
        on = 0; //update state
      }
  }
} 

