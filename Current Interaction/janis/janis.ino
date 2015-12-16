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
int servo_pins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int sensor_pins[NUM_SENSORS] = {A5, A4, A3, A2, A1, A0};

//State Variables
Servo servos[NUM_SERVOS];
State janis;
bool sensor_vals[NUM_SENSORS];

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
  //returns true if sensor_vals contains at least one true
  for (int i = 0; i <NUM_SENSORS; i++)
    if (sensor_vals[i]) return true;
  return false;
}

void getSensorInput() {
  //writes bool of if sensor sensed value or not, onto sensor_vals
  int threshold = 200;
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
  printTime();
  if(timeStatus() == timeSet) {
    hourPaddle();
    fiveMinutePaddle();
  }
  else {
    Serial.println("The time has not been set.");

  }
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
  //setupRTC();
  memset(sensor_vals, 0, NUM_SENSORS);
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
    if (num_sensed < 20) num_sensed ++;
    num_default = 0;
  }
  else {
    if (num_default < 20) num_default ++;
    num_sensed = 0;
  }

  //Change states if necessary
  if ((sensing) && (num_default > THRESHOLD)) {
    sensing = false;
    is_initializing = true;
  }
    
  else if ((!sensing) && (num_sensed > THRESHOLD)) {
    sensing = true;
    is_initializing = true;
  }

  //If update Sensing Interaction
  if (sensing) {
    if (is_initializing) {
      calibrate();
      is_initializing = false;
    }
    else updateSensorState(sweepBackForthControl);
    delay(5);
  }

  //If update Default Interaction
  if (!sensing) {
    if (is_initializing) initializeTimeStateInSteps();
    else sweepDefault();
    sweepDefault();
    delay(15);
  }

  //Display state
  displayState();
  delay(2);
}