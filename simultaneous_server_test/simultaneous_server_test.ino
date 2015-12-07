/*flag_state_test_two
 * Now with two servos and sensors!
*/

#include <Servo.h>

const int fidelity = 90;  //how many increments it takes to get from one position to another
const int NUM_SERVOS = 2;
const int NUM_SENSORS = 2;
int pos1[fidelity];
int pos2[fidelity];

Servo servos[NUM_SERVOS];
int ticker[NUM_SERVOS] = {0, 0};
int servoPins[NUM_SERVOS] = {11, 12};
int sensorPins[NUM_SENSORS] = {A0, A1};
int sensorValues[NUM_SENSORS] = {0, 0};

int timeStarts[NUM_SERVOS] = {0, 0};      // time since movement : for dealing with millis() rollover look at https://www.baldengineer.com/arduino-how-do-you-reset-millis.html
boolean flagStates[NUM_SERVOS] = {false, false};  // false means accessible

void setup()
{
  for (int i = 0; i < NUM_SERVOS; i++) { //loops through all sensors
    servos[i].attach(servoPins[i]);  // attaches the servo on pin 9 to the servo object
  }
  for (int i = 0; i < fidelity; i += 1) {
    pos1[i] = fidelity - i;
    pos2[i] = fidelity - i;
  }
  Serial.begin(9600);
}

void loop()
{
  sensorValues[0] = analogRead(sensorPins[0]);
  sensorValues[1] = analogRead(sensorPins[1]);

    if (sensorValues[0] > 80) {
      if (ticker[0] < fidelity) {
        ticker[0] += 1;
      }
      servos[0].write(pos1[ticker[0]]);
    }
    else {
      servos[0].write(pos1[0]);
      ticker[0] = 0;
    }

    if (sensorValues[1] > 80) {
      if (ticker[1] < fidelity) {
        ticker[1] += 1;
      }
      servos[1].write(pos1[ticker[1]]);
    }
    else {
      servos[1].write(pos1[1]);
      ticker[1] = 0;
    }
    delay(15);                           // waits for the servo to get there
    Serial.println(ticker[0]);
  }
