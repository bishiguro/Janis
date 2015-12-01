/*Default Interaction

Description: A Pleasing wave pattern that runs while nobody is interacting with the installation 
Iteration 1: Simple wave runs forever (one paddle moves, followed by the next)
Iteration 2: Wave runs forever, but with random frequencies or amplitudes (still need to brainstorm what can randomly change)
Stretch Idea: Wave runs forever, but tells time/ reacts to time (There are 12 paddles and 12 hours, so something interesting could happen here> 
OR, perhaps like a cuckoo clock, a wave pattern appears on the hour, every hour)*/

//---------------------------------------------------------------Libraries and Packages---------------------------------------------------------------
#include <QueueArray.h>
#include <Servo.h>
// #include <Time.h>  //(http://playground.arduino.cc/code/time)
//perhaps look into Millis, which gives you time since board has run (https://www.arduino.cc/en/Reference/Millis)

//---------------------------------------------------------------Initializations---------------------------------------------------------------
long int CURRENT_TIME;
const int NUM_SERVOS = 12;
Servo servos[NUM_SERVOS];  // create servo object to control a servo 
int servoPins[NUM_SERVOS] = {9, 8, 11};         // servo 1 [NEED TO UPDATE]

//create structure for storing sensor events. [pin(where pin is the servo index, not the pin it corresponds to on the arduino), value]
typedef struct {
  int pin;
  int val;
} servoEvent;

//create queue for storing and deploying all sensor events
QueueArray <servoEvent> queue;

//---------------------------------------------------------------Helper Functions---------------------------------------------------------------
void move_forward(int servoIndex) {
//Move servo forward from 0 to 90 degrees
  for(int i = 0; i < 90; i+=1) { // turn 90 degrees so that the paddle appears thick
    servos[servoIndex].write(i);
    delay(10);
  }
  Serial.print("Moved: "); Serial.println(servoIndex);
  delay(20);
}

void move_backward(int servoIndex) {
//Move servo backwards from 90 to 0 degrees
  for(int i = 90; i >=0; i-=1) { // turn 90 degrees back so that the paddle appears thin
    servos[servoIndex].write(i);
    delay(10);
  }
  delay(20); 
}

void update_servos() {
//Release one event in the queue
  if (!queue.isEmpty()) {
    servoEvent event = queue.dequeue(); //pops last element
    move_forward(event.pin); //moves servo
  }
}

bool is_special_time() {
	//Check if time is special. If it is, return true
}

void add_time_pattern() {
	//Creates a sequence that happens for a special time, and adds it to the queue

}

void add_default_pattern() {
	//Creates a single cycle of some default pattern, and adds it to the queue
}

void empty_queue() {

}

//---------------------------------------------------------------Setup and Main Loop---------------------------------------------------------------
//Setup
void setup() {
  for (int i = 0; i < NUM_SERVOS; i++) { //loops through all sensors
      servos[i].attach(servoPins[i]);  // attaches the servo on pin 9 to the servo object  
  }
  Serial.begin(9600); 
} 

//Main loop.
void loop() {
//We need to do some major thinking on how time should govern this loop
//We still need to adjust so that it runs for the same length of time each loop. 
//We also need to make sure time_pattern and default_pattern don't enqueue way more than update_servos can dequeue with each loop. 
//Perhaps loop priorities, with time patterns having a high priority? Or we could just empty the entire queue when a "special time" happens (That's how the code is set up now)
	if (is_special_time()) {
		empty_queue();
		add_time_pattern();
	}
	else if (queue.isEmpty()) {
		add_default_pattern();
	}
	update_servos();
}
