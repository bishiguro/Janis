/*sense_and_move_v2
Don't read sensor values until finished with 0-90 sweep.
Sweep back to zero.

Queue is implemented, and multiple sensors/multiple servos implemented.
In each loop:
   Each sensor detects. If there is an event, it adds it to the queue. 
   Queue deploys an event

This is our most recent and most complex implentation, with an effective structure for multiple servos/sensors. 
Next steps are:
  1. to improve the queue deploying (partially complete the event and move on to the next, rather than waiting for completion)
  2. Reduce Sensor noise
  3. Create a default interaction (perhaps tell time, since we have 12 servos) */

//---------------------------------------------------------------Libraries and Packages---------------------------------------------------------------
#include <QueueArray.h>
#include <Servo.h>
#include <servoEventStructure.h> //our structure type definition


//---------------------------------------------------------------Initializations---------------------------------------------------------------
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // servo 1
Servo servos[NUM_SERVOS];  // create servo object to control a servo 

int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5}; // sensor 1
int sensorValues[NUM_SENSORS] = {0, 0, 0, 0, 0, 0};

int servoPos[NUM_SERVOS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//create queue for storing and deploying all sensor events
QueueArray <servoEvent> queue;

//---------------------------------------------------------------Functions---------------------------------------------------------------
//Setup
void setup() 
{
  for (int i = 0; i < NUM_SERVOS; i++) { //loops through all sensors
      servos[i].attach(servoPins[i]);  // attaches the servo on pin 9 to the servo object  
  }
  Serial.begin(9600); 
} 

//Helper Functions
void move_forward(int servoIndex, int interval) {
  for(int i = servoPos[servoIndex]; i < servoPos[servoIndex] + interval; i+=1) { // turn 90 degrees so that the paddle appears thick
    servos[servoIndex].write(i);
    servoPos[servoIndex] = i;
    delay(1);
  }
  // Serial.print("Moved: "); Serial.println(servoIndex);
  delay(1);
}

void move_backward(int servoIndex, int interval) {
  for(int i = servoPos[servoIndex]; i > servoPos[servoIndex] - interval; i-=1) { // turn 90 degrees back so that the paddle appears thin
    servos[servoIndex].write(i);
    servoPos[servoIndex] = i;
    delay(1);
  }
  delay(1); 
}

//bool if_sees_object() {
// returns if the sensor sees an object. Not implemented yet, but we want to eventually have this filter out some noise. Right now it's pretty noisy because it 'sees' an object even if only one sensor value is above 100.
//}

servoEvent create_event(int pin) {
  servoEvent event;
  event.pin = pin;
  event.val = sensorValues[pin];
  event.pos = servoPos[pin];
  event.timestamp = millis();
  return event;
}

void check_sensors() {
  //loop through all sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    //check sensor value
    sensorValues[i] = analogRead(sensorPins[i]);
    //if sensor sees something, create event and add to queue
    if (sensorValues[i] >= 100) {
      //create event to hold sensor pin and val (type is servoEvent struct)
      Serial.print("sensed on pin: "); Serial.println(i);
      //enqueue
      queue.enqueue(create_event(i));
    }
  }

}


void moveForPin(int pin) {
  int servoNums[] = {2*pin, (2*pin)+1}; //converts sensor to corresponding servos
  for (int i = 0; i < sizeof(servoNums); i++) {
    if (servoNums[i] < NUM_SERVOS) {
      move_forward(servoNums[i], 10);
    }
    if (servoPos[i] == 90) {
      move_backward(servoNums[i], 90);
    }
  }
}

void eventDequeue() {
  servoEvent event = queue.dequeue(); //pops last element
  if (servoPos[event.pin] != 90) {
    queue.enqueue(create_event(event.pin)); //adds next event to end of queue
  }
  moveForPin(event.pin);
  Serial.print("Queue size: "); Serial.println(queue.count());
  Serial.print("Moved: "); Serial.println(event.pin);
}

void update_servos() {
//if queue has an event, pop the first object, and move the servos that correspond to the sensor
  if (!queue.isEmpty()) {
    eventDequeue();    
  }
}

void loop() 
//main loop
{
  check_sensors();
  delay(1);
  update_servos();
}
