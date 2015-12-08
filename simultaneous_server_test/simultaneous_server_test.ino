#include <Servo.h>

const int POS_MAX = 90;  //how many increments it takes to get from one position to another
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;

Servo servos[NUM_SERVOS];
int pos[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int sensorPins[NUM_SENSORS] = {A5, A4, A3, A2, A1, A0};
int sensorValues[NUM_SENSORS] = {0, 0, 0, 0, 0, 0};

void setup()
{
  for (int i = 0; i < NUM_SERVOS; i++) { //loops through all sensors
    servos[i].attach(servoPins[i]);  // attaches the servo on pin 9 to the servo object
    servos[i].write(0);
  }
  Serial.begin(9600);
}

void getServoResponse(int sensorNum) {
  sensorValues[sensorNum] = analogRead(sensorPins[sensorNum]);
  int servoNum = sensorNum * 2;

  if ((sensorValues[sensorNum] > 150) && (pos[servoNum] < POS_MAX)) {
    writeToServo(servoNum, pos[servoNum] + 1);
  }
  else if ((sensorValues[sensorNum] > 150) && (pos[servoNum] >= POS_MAX)) {
    writeToServo(servoNum, 90);
  }
  else {
    writeToServo(servoNum, 0);
  }
}

void writeToServo(int servoNum, int servoPos) {
  pos[servoNum] = servoPos;
  pos[servoNum + 1] = servoPos;

  servos[servoNum].write(pos[servoNum]);
  servos[servoNum + 1].write(pos[servoNum + 1]);
}

void loop()
{
  for (int i = 0; i< NUM_SENSORS; i++) {
    getSensorResponse(i);
  }
  delay(10);                           // waits for the servo to get there
  Serial.println(pos[0]);
}
