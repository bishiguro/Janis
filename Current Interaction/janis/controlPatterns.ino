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

void inverseSweepBackForthControl(int sensor_num) {
  //continously sweep back and forth between 0 and 90, if not sensed

  int servo1 = (sensor_num * 2);
  int servo2 = (sensor_num * 2) + 1;
  for (int i = 0; i < NUM_SERVOS; i ++) {
    if ((i != servo1) && (i != servo2)) singleIncrementServo(i, 90);
  }
}


void sweepToNinetyControl(int sensor_num) {
  sweepToNinety(sensor_num);
  resetNinety(10); //amount of cycles required of not sensed before it resets
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

void singleIncrementServo(int servo_num, int pos_max) {
  if (ifChangeState(servo_num, pos_max)) {
    changeDir(servo_num);
  }
  else {
    increment(servo_num);
  }
}

void sweepToNinety(int sensor_num) {
  int servo_num1 = sensor_num * 2;
  int servo_num2 = (sensor_num * 2) + 1;
  janis.pos[servo_num1] = constrain(janis.pos[servo_num1] + 1, 0, 90);
  janis.pos[servo_num2] = constrain(janis.pos[servo_num2] + 1, 0, 90);
}

void resetNinety(int time_to_reset) {
  for (int s = 0; s <NUM_SENSORS; s++) {
    if (not_sensed[s] > time_to_reset) {
      janis.pos[s*2] = 0;
      janis.pos[(s*2) + 1] = 0;
    }
  }
}