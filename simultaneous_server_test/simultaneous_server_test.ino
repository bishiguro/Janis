/*flag_state_test_two
 * Now with two servos and sensors!
*/

#include <Servo.h>

const int POS_MAX = 90;  //how many increments it takes to get from one position to another
const int NUM_SERVOS = 2;
const int NUM_SENSORS = 2;

Servo servos[NUM_SERVOS];
int pos[NUM_SERVOS] = {0, 0};
int servoPins[NUM_SERVOS] = {3, 4};
int sensorPins[NUM_SENSORS] = {A4, A5};
int sensorValues[NUM_SENSORS] = {0, 0};

void setup()
{
  for (int i = 0; i < NUM_SERVOS; i++) { //loops through all sensors
    servos[i].attach(servoPins[i]);  // attaches the servo on pin 9 to the servo object
    servos[i].write(0);
  }
  Serial.begin(9600);
}

void writeToServo(int sensorNum) {
  sensorValues[sensorNum] = analogRead(sensorPins[sensorNum]);
  // int servoNum = (sensorNum*2) + 2;
  int servoNum = sensorNum;

  if ((sensorValues[sensorNum] > 150) && (pos[servoNum] < POS_MAX)) {
      pos[servoNum] += 1;
  }
  else if ((sensorValues[sensorNum] > 150) && (pos[servoNum] >= POS_MAX)) {
    pos[servoNum] = 90;
  }
  else {
    pos[servoNum] = 0;
  }
  servos[servoNum].write(pos[servoNum]);
}

void loop()
{
  for (int i = 0; i< NUM_SENSORS; i++) {
    writeToServo(i);
  }
  delay(10);                           // waits for the servo to get there
  Serial.println(pos[0]);
}
