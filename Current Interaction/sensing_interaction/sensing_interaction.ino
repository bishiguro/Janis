//Shrinidhi Thirumalai, Bonnie Ishiguro, Charlie Mouton, Jason Yan
//Interaction for 12 paddles moving in response to your motion

//----------------------------------------------------------------------------Libraries and Packages----------------------------------------------------------------------
#include <Servo.h>
#include <servoStruct.h>
//-----------------------------------------------------------------------------Initializations---------------------------------------------------------------------------

const int POS_MAX = 90;  //how many increments it takes to get from one position to another
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;

Servo servos[NUM_SERVOS];
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int sensorPins[NUM_SENSORS] = {A5, A4, A3, A2, A1, A0};
int sensorValues[NUM_SENSORS] = {0, 0, 0, 0, 0, 0};
ServoUnit servoUnits[NUM_SERVOS];

ServoUnit createServo(int pin) {
  ServoUnit myServo;
  myServo.reverse = 0;
  myServo.pos = 0;
  myServo.pin = pin;
  return myServo;
}

//-----------------------------------------------------------------------------Helper Functions---------------------------------------------------------------------------

bool ifChangeState(int servoIndex) {
  //if a servo needs to change direction
  ServoUnit myServo = servoUnits[servoIndex];
  bool backward = ((myServo.reverse) && (myServo.pos > 0));
  bool forward = ((!myServo.reverse) && (myServo.pos < 90));
  return ! (forward || backward);
}

bool ifSensed(int sensorNum) {
  //if an object is sensed
  int threshold = 150;
  return (analogRead(sensorPins[sensorNum]) > threshold);
}

void writeToServos(int sensorNum, int servoPos) {
  //write position to corresponding servo pair, from the sensor number
  int servoPair[2] = {(sensorNum*2), (sensorNum*2) + 1};

  for (int i = 0; i < sizeof(servoPair); i++) {
    servoUnits[servoPair[i]].pos = servoPos;
    servos[servoPair[i]].write(servoUnits[servoPair[i]].pos);
  }
}

void whenSensed(int sensorNum) {
  //if state needs to be changed
  if (ifChangeState(sensorNum * 2)) {
    servoUnits[sensorNum].reverse = ! servoUnits[sensorNum].reverse;
  }
  //else, if moving forward
  else if (servoUnits[sensorNum].reverse) {
    writeToServos(sensorNum, servoUnits[sensorNum].pos - 1);
  }
  //else, if moving backward
  else {
    writeToServos(sensorNum, servoUnits[sensorNum].pos + 1);
  }
}

void whenNotSensed(int sensorNum) {
  //reset when nothing is sensed
  writeToServos(sensorNum, 0);
}

void updateServos(int sensorNum) {
  // if the sensor is reading a value
  if (ifSensed(sensorNum)) {
    whenSensed(sensorNum);
  }
  // if nothing is sensed
  else {
    whenNotSensed(sensorNum);
  }
}

//-----------------------------------------------------------------------------Main Loops---------------------------------------------------------------------------

void setup()
{
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoUnits[i] = createServo(servoPins[i]);
  }
  
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
  }

  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i< NUM_SENSORS; i++) {
    updateServos(i);
  }
  delay(10); // waits for the servo to get there
}
