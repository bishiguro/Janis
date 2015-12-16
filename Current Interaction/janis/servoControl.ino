//------Servo Control Helper Functions------------------

bool ifChangeState(int servo_num, int max_pos) {
  //if a servo needs to change direction
  bool backward_range = (janis.is_reverse[servo_num] && (janis.pos[servo_num]> 0));
  bool forward_range = ((!janis.is_reverse[servo_num]) && (janis.pos[servo_num] < max_pos));
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