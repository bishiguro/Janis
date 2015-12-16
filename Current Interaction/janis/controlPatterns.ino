//------Types of Control Patterns----------------------

void sweepBackForthControl(int sensor_num) {
  //continously sweep back and forth between 0 and 90
    if (ifChangeState(sensor_num*2, 90)) {
      changeDir(sensor_num*2);
      changeDir((sensor_num*2) + 1);
    }
    else {
      increment(sensor_num*2);
      increment((sensor_num*2) + 1);
    }
  }

void singleIncrementServo(int servo_num, int pos_max) {
	if (ifChangeState(servo_num, pos_max)) {
    changeDir(servo_num);
  }
	else {
    increment(servo_num);
  }
}

void proportionalControl(int sensor_num) {

}

void sweepToNinety(int sensor_num) {

}

//------Servo Control Helper Functions------------------

bool ifChangeState(int servo_num, int pos_max) {
  //if a servo needs to change direction
  bool backward_range = (janis.is_reverse[servo_num] && (janis.pos[servo_num]> 0));
  bool forward_range = ((!janis.is_reverse[servo_num]) && (janis.pos[servo_num] < pos_max));
  return ! (forward_range || backward_range);
}

void changeDir(int servo_num) {
  //changing direction
  janis.is_reverse[servo_num] = (! janis.is_reverse[servo_num] );
}

void increment(int servo_num) {
  //incrementing by one in the direction of state
  if (janis.is_reverse[servo_num])
    janis.pos[servo_num] -= 1;
  else
    janis.pos[servo_num] += 1;
}