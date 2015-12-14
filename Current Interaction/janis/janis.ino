//Shrinidhi Thirumalai, Bonnie Ishiguro, Charlie Mouton, Jason Yan
//Interaction for 12 paddles moving in response to your motion

//----------------------------------------------------------------------------Libraries and Packages----------------------------------------------------------------------
#include <Servo.h>
#include <setup.h>
//-----------------------------------------------------------------------------Initializations---------------------------------------------------------------------------

//Already Included: POS_MAX, NUM_SERVOS, NUM_SENSORS
int servo_pins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int sensor_pins[NUM_SENSORS] = {A5, A4, A3, A2, A1, A0};

//State Variables
Servo servos[NUM_SERVOS];
State janis;
bool sensor_vals[NUM_SENSORS];

//------------------------Setup----------------------------------------
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
//--------------Get Sensor Input--------------------------------------
bool ifDetect() {
  //returns true if sensor_vals contains at least one true
  for (int i = 0; i <NUM_SENSORS; i++)
    if (sensor_vals[i]) return true;
  return false;
}

void getSensorInput() {
  //writes bool of if sensor sensed value or not, onto sensor_vals
  int threshold = 150;
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor_vals[i] = (analogRead(sensor_pins[i]) >= threshold);
  }
}
//----------------Update State--------------------------------------------
void updateSensorState( void (*f)(int) ) {
  //if a sensor sees something, run the given control function
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensor_vals[i])
      (*f)(i);
  }
}

void updateTimeState() {

}
//------------------Display State------------------------------------------
void displayState() {
  //write state to servos
  for (int i = 0; i < NUM_SERVOS; i++)
    servos[i].write(janis.pos[i]);
}

//-----------------------------------------------------------------Main Ardiono Loops---------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  memset(sensor_vals, 0, NUM_SENSORS);
  janis = initializeJanis();
}

void loop()
{
  getSensorInput();

  if (ifDetect())
    updateSensorState(sweepBackForthControl);
  else
    updateTimeState();
    
  displayState();
}