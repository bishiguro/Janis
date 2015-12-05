//---------------------------------------------------------------Libraries---------------------------------------------------------------
#include <Servo.h>
#include <servoStruct.h>
#include <QueueArray.h>
#include <servoEventStructure.h>

//servoUnit servo1;
//Servo servo2;

//---------------------------------------------------------------Initializations---------------------------------------------------------------
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;

int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
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
    delay(2);
  }
}

void sweepBackward(int servoIndex, int interval) {
  int pos = servoUnits[servoIndex].pos;
  for (int i = pos; i > pos + interval; i -- ) {
    servoWrite(servoIndex, i);
    delay(2);
  }
}

void moveServo(int servoIndex) {
  servoUnit myServo = servoUnits[servoIndex];
  if ((myServo.reverse) && (myServo.pos > 0)) {
    // sweepForward(servoIndex, 5);
    servoWrite(servoIndex, myServo.pos + 5);
    Serial.print(" in reverse ");
  }
  else if ((!myServo.reverse) && (myServo.pos < 90)) {
    // sweepBackward(servoIndex, 5);
    servoWrite(servoIndex, myServo.pos - 5);
    Serial.print(" forward " );
  }
  else{
    servoUnits[servoIndex].reverse = ! servoUnits[servoIndex].reverse;
    Serial.print(" change state ");
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
  Serial.print("Creating pattern");
  // for (int i = 0; i < NUM_SENSORS; i++) {
  for (int i = 2; i < 7; i++) {
      //check sensor value
      queue.enqueue(create_event(i));
  //   }
  // for (int i = NUM_SENSORS; i > 0; i--) {
  for (int i = 2; i < 7; i++) {
      //check sensor value
      queue.enqueue(create_event(i));
    }
  }
}

void eventDequeue() {
  servoEvent event = queue.dequeue(); //pops last element
  Serial.print("dequeued :"); Serial.println(event.pin);
  // moveForPin(event.pin);
  int pos = servoUnits[event.pin - 2].pos;
  moveServo(event.pin);

  //readd to end
  if (pos < 90) {
    queue.enqueue(create_event(event.pin)); //adds next event to end of queue
  }

  //debugging
  Serial.print("Queue size: "); Serial.println(queue.count());
  Serial.print("Moved: "); Serial.println(event.pin);
}

void update_servos() {
  Serial.print("Updating Servos");
//if queue has an event, pop the first object, and move the servos that correspond to the sensor
  if (!queue.isEmpty()) {
    eventDequeue();
  }
}


void loop() 
//main loop
{
  if (queue.isEmpty()) {
    create_pattern();
  }
  // delay(1);
  update_servos();
  // moveServo(2);
  // Serial.print(servoPos[1]);
}