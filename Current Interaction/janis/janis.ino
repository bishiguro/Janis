//Shrinidhi Thirumalai, Bonnie Ishiguro, Charlie Mouton, Jason Yan
//Interaction for 12 paddles moving in response to your motion

//----------------------------------------------------------------------------Libraries and Packages----------------------------------------------------------------------
#include <Servo.h>
#include <setup.h>
#include <Time.h>
#include <TimeLib.h>
//#include <DS1307RTC.h>
//-----------------------------------------------------------------------------Initializations---------------------------------------------------------------------------

//Already Included: POS_MAX, NUM_SERVOS, NUM_SENSORS
int servo_pins[NUM_SERVOS] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
int sensor_pins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5};

//State Variables
Servo servos[NUM_SERVOS];
State janis;
bool sensor_bools[NUM_SENSORS];
int not_sensed[NUM_SENSORS];

bool is_initializing;
bool sensing = false;
int num_sensed = 0;
int last_sensed = 0;
int num_default = 0;

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
  //returns true if sensor_bools contains at least one true
  for (int i = 0; i <NUM_SENSORS; i++)
    if (sensor_bools[i]) return true;
  return false;
}

void getSensorInput() {
  //writes bool of if sensor sensed value or not, onto sensor_bools
  int threshold = 200;
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor_bools[i] = (analogRead(sensor_pins[i]) >= threshold);
    
    //update not_sensed
    if (sensor_bools[i]) not_sensed[i] = 0;
    else if (not_sensed[i] < 100) not_sensed[i] ++;
  }
}
//----------------Update State--------------------------------------------
void updateSensorState( void (*f)(int) ) {
  //if a sensor sees something, run the given control function
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensor_bools[i])
      (*f)(i);
  }
}

void updateTimeState() {
  hourPaddle();
  fiveMinutePaddle();
}

void sweepDefault() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    sweepBackForthControl(i);
  }
}

void initializeTimeState() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    janis.pos[i] = map(i, 0, NUM_SERVOS, 0, 90);
  }
}

void initializeTimeStateInSteps() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    int finalpos = map(i, 0, NUM_SERVOS, 0, 90);

    //update positions in increments
    if (finalpos < janis.pos[i]) {
      int difference = janis.pos[i] - finalpos;
      janis.pos[i] = janis.pos[i] - difference/20;    
    }
    else {
      int difference = finalpos - janis.pos[i];
      janis.pos[i] = janis.pos[i] + difference/20; 
    }

    //if done initializing
    if (janis.pos[i] == finalpos) {
      is_initializing = false;
    }

  }
}

//------------------Display State------------------------------------------
void displayState() {
  //write state to servos
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(janis.pos[i]);
  }
}

void calibrate() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    janis.pos[i] = 0;
    //servos[i].write(0);
  }
}

void printState() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    Serial.println(janis.pos[i]);
  }
  Serial.println("===============================");
}
//-----------------------------------------------------------------Main Ardiono Loops---------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  initializeTime();
  memset(sensor_bools, 0, NUM_SENSORS);
  memset(not_sensed, 0, NUM_SENSORS);
  janis = initializeJanis();
  attachServos();

  calibrate();
  displayState();

  initializeTimeState();
  displayState();
}

void loop()
{
  getSensorInput();

  //Update Num_sensed and num_default
  if (ifDetect()) {
    if (num_sensed < 100) num_sensed ++;
    num_default = 0;
  }
  else {
    if (num_default < 100) num_default ++;
    num_sensed = 0;
  }

  //Change states if necessary
  if ((sensing) && (num_default > TIME_THRESHOLD)) {
    sensing = false;
    is_initializing = true;
  }
    
  else if ((!sensing) && (num_sensed > SENSE_THRESHOLD)) {
    sensing = true;
    is_initializing = true;
  }

  //If update Sensing Interaction
  if (sensing) {
    if (is_initializing) {
      calibrate();
      is_initializing = false;
    }
    else {
      updateSensorState(sweepToNinetyControl);
    }
    delay(1);
  }

  //If update Default Interaction
  if (!sensing) {
    if (is_initializing) {
      initializeTimeState();
      is_initializing = false;
    }
    sweepDefault();
    updateTimeState();
    delay(15);
  }

  //Display state
  displayState();
  delay(1);
}