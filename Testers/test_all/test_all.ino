/*copied from sense_sweep-90
 * simplified to move all the servos one by one with no sensor input
 * Dec. 4, 2015
*/

//---------------------------------------------------------------Initializations---------------------------------------------------------------
#include <Servo.h>

const int NUM_SERVOS = 12;  //took out 11 because the servo is spent :(

Servo servos[NUM_SERVOS];
int servo_pins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

int servoPos[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//---------------------------------------------------------------Functions---------------------------------------------------------------
void setup()
{

  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servo_pins[i]);
  }
  Serial.begin(9600);
}

void loop()
{
  // for (int s = 0; s < NUM_SERVOS; s += 1) {
  //   for (int i = 0; i < 90; i += 1) {
  //     servos[s].write(i);
  //     delay(10);
  //   }
  // }
}
