//------Types of Control Patterns----------------------

void sweepBackForthControl(int sensor_num) {
  //ccontinously sweep back and forth between 0 and 90
  int servo_pair[] = {(sensor_num * 2), (sensor_num * 2) + 1};
  for (int i = 0; i < sizeof(servo_pair); i ++) {
    if (ifChangeState(servo_pair[i]))
      changeDir(servo_pair[i]);
    else
      increment(servo_pair[i]);
  }
}

void proportionalControl(int sensor_num) {

}

void sweepToNinety(int sensor_num) {

}