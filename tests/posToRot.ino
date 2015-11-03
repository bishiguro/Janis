#include <Servo.h> 

const int NUM_SERVOS = 6;

Servo servos[NUM_SERVOS];
int positions[NUM_SERVOS];
int pins[] = {9, 10, 11, 5, 6, 3};

void setup() 
{
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(pins[i]);
  }

  Serial.begin(9600);

  calibrate();
}

void servo_write(int servo_index, int pos) {
  servos[servo_index].write(pos);
  positions[servo_index] = pos;
}

void sweep(int servo_index, int final) {
  for (int i = positions[servo_index]; i <= final; i++) {
    servo_write(servo_index, i);
    delay(10);
  }
}

void loop()
{
  for (int i = 0; i < NUM_SERVOS; i++) {
    sweep(i, 90); // test sweep all servos to 90 degrees
  }
}

void calibrate() { // set servo positions to 0
  for (int i = 0; i < NUM_SERVOS; i ++) {
    sweep(i, 0); 
    delay(10);
  }
}

void posToRot(int ribbon, float pos) {
  if (pos <= 0.5) {
    sweep(ribbon, 0); // top servo
    sweep(ribbon+NUM_SERVOS/2, 90 * pos + 90); // bottom servo
    delay(10);
  }

  else if (pos > 0.5) {
    sweep(ribbon, 180 * pos); // top servo
    sweep(ribbon+NUM_SERVOS/2, 180); // bottom servo
    delay(10);
  }
}