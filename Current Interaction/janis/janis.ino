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
bool sensor_vals[NUM_SENSORS];


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
  int threshold;
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor_vals[i] = (analogRead(sensor_pins[i]) > threshold);
  }
}

bool ifDetect() {
  for (int i = 0; i <NUM_SENSORS; i++)
    if (sensor_vals[i]) return true;
  return false;
}

bool ifChangeState(int servo_num) {
  //if a servo needs to change direction
  bool backward_range = (janis.is_reverse[servo_num] && (janis.pos[servo_num]> 0));
  bool forward_range = ((!janis.is_reverse[servo_num]) && (janis.pos[servo_num] < 90));
  return ! (forward_range || backward_range);
}

void changeDir(int servo_num) {
  janis.is_reverse[servo_num] = (! janis.is_reverse[servo_num] );
}

void increment(int servo_num) {
  if (janis.is_reverse[servo_num])
    janis.pos[servo_num] -= 1;
  else
    janis.pos[servo_num] += 1;
}

void sweepBackForthControl(int sensor_num) {
  int servo_pair[] = {(sensor_num * 2), (sensor_num * 2) + 1};
  for (int i = 0; i < sizeof(servo_pair); i ++) {
    if (ifChangeState(servo_pair[i]))
      changeDir(servo_pair[i]);
    else
      increment(servo_pair[i]);
  }
}

void updateSensorState() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensor_vals[i]) sweepBackForthControl(i);
  }
}

void updateTimeState() {

}

void displayState() {
  for (int i = 0; i < NUM_SERVOS; i++)
    servos[i].write(janis.pos[i]);
}

void loop()
{
  getSensorInput();

  if (ifDetect())
    updateSensorState();
  else
    updateTimeState();

  displayState();
}