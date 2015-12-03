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

//---------------------------------------------------------------Initializations---------------------------------------------------------------
const int NUM_SERVOS = 12;
const int NUM_SENSORS = 6;
Servo servos[NUM_SERVOS];  // create servo object to control a servo 
int servoPins[NUM_SERVOS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};         // servo 1
int sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5};       // sensor 1
int sensorValues[NUM_SENSORS] = {0};      // variable to store the value coming from the sensor

//create structure for storing sensor events. [pin(where pin is the servo index, not the pin it corresponds to on the arduino), value]
typedef struct {
  int pin;
  int val;
} sensorEvent;

//create queue for storing and deploying all sensor events
QueueArray <sensorEvent> queue;

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
void move_forward(int servoIndex) {
  for(int i = 0; i < 90; i+=1) { // turn 90 degrees so that the paddle appears thick
    servos[servoIndex].write(i);
    delay(10);
  }
  // Serial.print("Moved: "); Serial.println(servoIndex);
  delay(20);
}

void move_backward(int servoIndex) {
  for(int i = 90; i >=0; i-=1) { // turn 90 degrees back so that the paddle appears thin
    servos[servoIndex].write(i);
    delay(10);
  }
  delay(20); 
}

//bool if_sees_object() {
// returns if the sensor sees an object. Not implemented yet, but we want to eventually have this filter out some noise. Right now it's pretty noisy because it 'sees' an object even if only one sensor value is above 100.
//}

void check_sensors() {
  //loop through all sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    //check sensor value
    sensorValues[i] = analogRead(sensorPins[i]);
    //if sensor sees something, create event and add to queue
    if (sensorValues[i] >= 100) {
      //create event to hold sensor pin and val (type is SensorEvent struct)
      sensorEvent event;
      event.pin = i;
      Serial.print("sensed on pin: "); Serial.println(event.pin);
      event.val = sensorValues[i];

      //enqueue
      queue.enqueue(event);
    }
  }

}

void update_servos() {
//if queue has an event, pop the first object, and move the servos that correspond to the sensor
  if (!queue.isEmpty()) {
    sensorEvent event = queue.dequeue(); //pops last element
    
    int servoNums[] = {2*event.pin, (2*event.pin)+1}; //converts sensor to corresponding servos
    Serial.print("Queue size: "); Serial.println(queue.count());
    Serial.print("Moved: "); Serial.println(event.pin);

    //moves servos
    for (int i = 0; i < sizeof(servoNums); i++) {
      if (servoNums[i] < NUM_SERVOS) {
        move_forward(servoNums[i]);
        move_backward(servoNums[i]);
      }
    }
  }
}

void loop() 
//main loop
{
  check_sensors();
  delay(1);
  update_servos();
}
