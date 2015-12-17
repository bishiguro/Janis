//Global Variables
const int POS_MAX = 90;
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;
const int SENSE_THRESHOLD = 10;
const int TIME_THRESHOLD = 80;

//State Structure
struct State{
  // Servo servo;
  int pos[NUM_SERVOS];
  bool is_reverse[NUM_SERVOS];
};
