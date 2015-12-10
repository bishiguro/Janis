#include <Servo.h>

const int POS_MAX = 90;  //how many increments it takes to get from one position to another
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;

struct State{
  // Servo servo;
  int pos[12];
  bool is_reverse[12];
};
