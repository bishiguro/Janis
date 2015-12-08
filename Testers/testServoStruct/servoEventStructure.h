//Structure for ServoEvents in Queue. Needs to be a seperate .h file because of Arduino's compilation order/ 
//We need to include it as a library rather than define it in the code itself, so that they are compiled before our functions, which depend on this type/
struct servoEvent{
  int pin;
  int val;
  int pos;
  int timestamp;
};
