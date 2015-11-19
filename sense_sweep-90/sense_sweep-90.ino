/*sense_sweep-90
Don't read sensor values until finished with 0-90 sweep.
Sweep back to zero.*/

#include <Servo.h> 

const int NUM_SERVOS = 1;
const int NUM_SENSORS = 1;

//Servo myservo;  // create servo object to control a servo 
//int servoPin = 9;         // servo 1

Servo servos[NUM_SERVOS];
int servo_pins[] = {9};

int sensor_pins[] = {A0};
int sensor_values = {0};

//int sensorPin = A0;       // sensor 1
//int sensorValue = 0;      // variable to store the value coming from the sensor

boolean zero_start = true;

void setup() 
{ 
  //myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servo_pins[i]);
  }
  
  Serial.begin(9600);
} 
 
void loop() 
{
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor_values[i] = analogRead(sensor_pins[i]);
  }
  //sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  
  if(sensorValue > 100) { // if the sensor detects an object

    if (zero_start) {
      for(int i = 0; i < 90; i+=1) { // turn 90 degrees so that the paddle appears thick
        myservo.write(i);
        delay(10);
      }
      delay(20);
      
    }
    else {
      for(int i = 90; i >=0; i-=1) { // turn 90 degrees back so that the paddle appears thin
        myservo.write(i);
        delay(10);
      }
      delay(20); 
    }
    zero_start = !zero_start;
  }
}
