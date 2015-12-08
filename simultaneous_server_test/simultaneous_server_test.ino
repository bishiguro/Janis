/*flag_state_test_two
 * Now with two servos and sensors!
*/

#include <Servo.h>

const int POS_MAX = 90;  //how many increments it takes to get from one position to another
const int NUM_SERVOS = 6;
const int NUM_SENSORS = 3;

Servo servos[NUM_SERVOS];
int pos[NUM_SERVOS] = {0, 0, 0, 0, 0, 0};
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7};
int sensorPins[NUM_SENSORS] = {A6, A5, A4};
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
  int servoNum1 = sensorNum * 2;
  int servoNum2 = sensorNum1 + 1;

  if ((sensorValues[sensorNum] > 150) && (pos[servoNum1] < POS_MAX)) {
    pos[servoNum1] += 1;
    pos[servoNum12 += 1;
  }
  else if ((sensorValues[sensorNum] > 150) && (pos[servoNum1] >= POS_MAX)) {
    pos[servoNum1] = 90;
    pos[servoNum12 = 90;
  }
  else {
    pos[servoNum1] = 0;
    pos[servoNum12 = 0;
  }

  servos[servoNum1].write(pos[servoNum1]);
  servos[servoNum2.write(pos[servoNum2);
}

void loop()
{
  for (int i = 0; i< NUM_SENSORS; i++) {
    writeToServo(i);
  }
  delay(10);                           // waits for the servo to get there
  Serial.println(pos[0]);
}
