//------Types of Control Patterns----------------------

void sweepBackForthControl(int sensor_num) {
  //ccontinously sweep back and forth between 0 and 90
  int servo_pair[] = {(sensor_num * 2), (sensor_num * 2) + 1};
  for (int i = 0; i < sizeof(servo_pair); i ++) {
  	singleIncrementServo(i, 90);
  }
}

void singleIncrementServo(int servo_num, int pos_max) {
	if (ifChangeState(servo_num, pos_max))
  		changeDir(servo_num);
	else
  		increment(servo_num);
}

void proportionalControl(int sensor_num) {

}

void sweepToNinety(int sensor_num) {

}