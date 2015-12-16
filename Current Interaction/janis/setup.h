//Global Variables
const int POS_MAX = 90;
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;
const int MIN_SENSE = 5;

//State Structure
struct State{
  // Servo servo;
  int pos[12];
  bool is_reverse[12];
};
