//Global Variables
const int POS_MAX = 90;
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;
const int MIN_SENSE = 5;

//State Structure
struct State{
  // Servo servo;
  int pos[NUM_SERVOS];
  bool is_reverse[NUM_SERVOS];
};
