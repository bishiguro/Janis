/*sense_and_move_v2
Don't read sensor values until finished with 0-90 sweep.
Sweep back to zero.

Queue is implemented, and multiple sensors/multiple servos implemented.
In each loop:
   Each sensor detects. If there is an event, it adds it to the queue. 
   Queue deploys an event

This is our most recent and most complex implentation, with an effective structure for multiple servos/sensors. 
Next steps are:
  1. to improve the queue deploying (partially complete the event and move on to the next, rather than waiting for completion)
  2. Reduce Sensor noise
  3. Create a default interaction (perhaps tell time, since we have 12 servos) */

//---------------------------------------------------------------Libraries and Packages---------------------------------------------------------------
#include <QueueArray.h>
#include <Servo.h>


//---------------------------------------------------------------Initializations---------------------------------------------------------------
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // servo 1
Servo servos[NUM_SERVOS];  // create servo object to control a servo
int servoPos[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5}; // sensor 1
int sensorValues[NUM_SENSORS] = {0, 0, 0, 0, 0, 0};

//---------------------------------------------------------------Functions---------------------------------------------------------------

//Helper Functions
void move_forward(int servoIndex, int interval) {
  //move servo forwards the given interval
  for(int i = servoPos[servoIndex]; i < servoPos[servoIndex] + interval; i+=1) { // turn 90 degrees so that the paddle appears thick
    servos[servoIndex].write(i);
    servoPos[servoIndex] = i;
    delay(1);
  }
  // Serial.print("Moved: "); Serial.println(servoIndex);
  delay(1);
}


void check_and_print_sensors() {
  //loop through all sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    //check sensor value
    sensorValues[i] = analogRead(sensorPins[i]);
    //if sensor sees something, create event and add to queue
    Serial.print("|  "); Serial.print(sensorValues[i]); Serial.print("  |");
    }
  Serial.println("");
  delay(200);
}


void test_all() {
  for (int s = 0; s < NUM_SERVOS; s += 1) {
    for (int i = 0; i < 90; i += 1) {
      servos[s].write(i);
      delay(10);
    }
  }
}

void calibrate() {
// set all servo positions to zero
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(0);
  }
}

void attachServos() {
  for (int i = 0; i < NUM_SERVOS; i++) { //loops through all sensors
    servos[i].attach(servoPins[i]);  // attaches the servo on pin 9 to the servo object  
  }
}

//-----------------------------------------------------------Main Arduino Functions-------------------------------------------------------------------------

//Setup
void setup() 
{
  attachServos();
  Serial.begin(9600);
  calibrate();

} 


void loop() 
//main loop
{
  // calibrate();
  // delay(20);
  // test_all();
  check_and_print_sensors();
}

