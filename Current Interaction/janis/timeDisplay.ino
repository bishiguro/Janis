#include <Time.h>

int prev_hour;
int prev_minute;
int prev_second;


void initializeTime() {
	setTime(1,30,0,12,17,2015);
}

void printTime() { // update the clock
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) { // Arduino example function for displaying the time in hh:mm:ss format
  Serial.print(":");
  if(digits < 10) {
    Serial.print('0');
  Serial.print(digits);
  }
}

void hourPaddle() {
	int curr_hour = hourFormat12();
	if (curr_hour != prev_hour) {
		janis.pos[prev_hour - 1] = 0;
	}
	janis.pos[curr_hour-1] = 90; // hold the hour paddle at 90 deg
}

void fiveMinutePaddle() {
	int curr_minute = minute();
	if (curr_minute != prev_minute) {
		janis.pos[prev_minute/5] = 45;
	}

	if((hourFormat12()-1) != (curr_minute/5)) { // prioritize the hour over the minute
		singleIncrementServo(curr_minute/5, 90);
	}
	for (int i = curr_minute/5 - 1; i >= 0; i--) { // rotate all preceding minute paddles
		singleIncrementServo(i, 90);
	}
}