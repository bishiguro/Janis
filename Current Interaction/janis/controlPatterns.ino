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

void singleIncrementServo(int servo_num, int pos_max) {
	if (ifChangeState(servo_num, pos_max)) {
    changeDir(servo_num);
  }
	else {
    increment(servo_num);
  }
}

// void sweepToNinety(int sensor_num) {
//   int servo_num1 = sensor_num * 2;
//   int servo_num2 = servo_num1 + 1;
//   for (int s = 0; s<NUM_SERVOS; s++) {
//     if ((s == servo_num1) || (s == servo_num2))
//       janis.pos[s] = constrain(janis.pos[s] + 1, 0, 90);
//     else
//       janis.pos[s] = 0;
//   }
// }

void sweepToNinetySimple(int sensor_num) {
  int servo_num1 = sensor_num * 2;
  int servo_num2 = servo_num1 + 1;
  janis.pos[servo_num1] = constrain(janis.pos[servo_num1], 0, 90);
  janis.pos[servo_num2] = constrain(janis.pos[servo_num2], 0, 90);
}

void sweepToNinetyWithReset(int sensor_num) {
  int servo_num1 = sensor_num * 2;
  int servo_num2 = servo_num1 + 1;
  janis.pos[servo_num1] = constrain(janis.pos[servo_num1], 0, 90);
  janis.pos[servo_num2] = constrain(janis.pos[servo_num2], 0, 90);

  if (last_sensed != sensor_num) {
    int servo_num1 = last_sensed * 2;
    int servo_num2 = (last_sensed*2) + 1;
    janis.pos[servo_num1] = 0;
    janis.pos[servo_num2] = 0;
  }

  last_sensed = sensor_num;
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