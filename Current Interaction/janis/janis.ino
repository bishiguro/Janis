//Shrinidhi Thirumalai, Bonnie Ishiguro, Charlie Mouton, Jason Yan
//Interaction for 12 paddles moving in response to your motion

//----------------------------------------------------------------------------Libraries and Packages----------------------------------------------------------------------
#include <Servo.h>
#include <setup.h>
//-----------------------------------------------------------------------------Initializations---------------------------------------------------------------------------

Servo servos[NUM_SERVOS];
int servo_pins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int sensor_pins[NUM_SENSORS] = {A5, A4, A3, A2, A1, A0};
State janis;
int sensor_vals[NUM_SENSORS];


//-----------------------------------------------------------------------------Main Loops---------------------------------------------------------------------------
State initializeJanis() {
  State janis;
  memset(janis.pos, 0, NUM_SERVOS);
  memset(janis.is_reverse, 0, NUM_SERVOS);
  return janis;
}

void attachServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servo_pins[i]);
    servos[i].write(0);
  }
}

void setup()
{
  Serial.begin(9600);
  memset(sensor_vals, 0, NUM_SENSORS);
  janis = initializeJanis();
}

void getSensorInput() {

}

void updateSensorState() {

}

void updateTimeState() {

}

void displayState() {
  
}

void loop()
{
  getSensorInput();

  if ifDetect() {
    updateSensorState();
  }
  else {
    updateTimeState();
  }

  displayState();
}