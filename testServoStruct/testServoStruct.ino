//---------------------------------------------------------------Libraries---------------------------------------------------------------
#include <Servo.h>
#include <servoStruct.h>
#include <QueueArray.h>
#include <servoEventStructure.h>

//servoUnit servo1;
//Servo servo2;

//---------------------------------------------------------------Initializations---------------------------------------------------------------
// const int NUM_SERVOS = 12;
const int NUM_SERVOS = 6;
const int NUM_SENSORS = 6;

// int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7};
Servo servos[NUM_SERVOS];
servoUnit servoUnits[NUM_SERVOS];

int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5}; // sensor 1
int sensorValues[NUM_SENSORS] = {0, 0, 0, 0, 0, 0};

//create queue for storing and deploying all sensor events
QueueArray <servoEvent> queue;

//---------------------------------------------------------------Functions---------------------------------------------------------------

servoUnit createServo(int pin) {
  servoUnit myServo;
  myServo.reverse = 0;
  myServo.pos = 0;
  myServo.pin = pin;
  return myServo;
}

void servoSetup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
  }
}

void servoWrite(int servoIndex, int pos) {
  servos[servoIndex].write(pos);
  servoUnits[servoIndex].pos = pos;
}

void sweepForward(int servoIndex, int interval) {
  int pos = servoUnits[servoIndex].pos;
  for (int i = pos; i < pos + interval; i ++ ) {
    servoWrite(servoIndex, i);
    delay(1);
  }
}

void sweepBackward(int servoIndex, int interval) {
  int pos = servoUnits[servoIndex].pos;
  for (int i = pos; i > pos - interval; i -- ) {
    servoWrite(servoIndex, i);
    delay(2);
  }
}

void moveServo(int servoIndex) {
  servoUnit myServo = servoUnits[servoIndex];
  if ((myServo.reverse) && (myServo.pos > 0)) {
    sweepBackward(servoIndex, 5);
    // servoWrite(servoIndex, myServo.pos - 1);
    // Serial.print("BACKWARD");
  }
  else if ((!myServo.reverse) && (myServo.pos < 90)) {
    sweepForward(servoIndex, 5);
    // servoWrite(servoIndex, myServo.pos + 1);
    // Serial.print("FORWARD");
  }
  else{
    servoUnits[servoIndex].reverse = ! servoUnits[servoIndex].reverse;
    // Serial.print("STATE CHANGE");
  }
}

servoEvent create_event(int pin) {
  servoEvent event;
  event.pin = pin;
  event.val = sensorValues[pin];
  event.pos = servoUnits[event.pin - 2].pos;
  event.timestamp = millis();
  Serial.print("created event on pin: "); Serial.println(pin);
  return event;
}

void create_pattern() {
  // Serial.print("Creating pattern");
  // for (int i = 0; i < NUM_SENSORS; i++) {
  for (int i = 2; i <= 7; i++) {
      queue.enqueue(create_event(i));
    }
  // for (int i = NUM_SENSORS; i > 0; i--) {
  for (int i = 6; i > 2; i--) {
      queue.enqueue(create_event(i));
    }
  }

void eventDequeue() {
  servoEvent event = queue.dequeue(); //pops last element
  // Serial.print("dequeued :"); Serial.println(event.pin);
  // moveForPin(event.pin);
  int pos = event.pos;
  moveServo(event.pin);

  //readd to end
  if ((pos < 90) && (pos > 0)) {
    queue.enqueue(create_event(event.pin)); //adds next event to end of queue
  }

  //debugging
  // Serial.print("Queue size: "); Serial.println(queue.count());
  // Serial.print("Moved: "); Serial.println(event.pin);
}

void update_servos() {
//if queue has an event, pop the first object, and move the servos that correspond to the sensor
  if (!queue.isEmpty()) {
    eventDequeue();
  }
}

void setup() 
{
  Serial.begin(9600);
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoUnits[i] = createServo(servoPins[i]);
  }
  servoSetup();
}

void loop() 
//main loop
{
  if (queue.isEmpty()) {
    create_pattern();
  }
  update_servos();

  // for (int i = 0; i < 90; i++) {
  //   servoWrite(5, i);
  //   servoWrite(5, i);
  //   delay(20);
  //   // Serial.print(servo1.pos);
  // }
  // for (int i = 90; i > 0; i--) {
  //   servoWrite(5, i);
  //   servoWrite(5, i);
  //   delay(20);

  // }
}