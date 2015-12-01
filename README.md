# TwistedWaveInstallation
POE Final Project Fall 2015
	Shrinidhi Thirumalai
	Bonnie Ishiguro
	Charlie Mouton
	Jason Lan
	Meg McCauley

Simplest Code: 

	Sense and Move: Simplest deployment of single paddle moving if it detecs an object from a sensor

Control Schemes: 

	Sense Sweep 90: Similar to sense_and_move, but don't read sensor values until finished with 0-90 sweep, then sweep back to zero. This is the second implemetation of Sense_and_move, with major improvements

	Sense and Move w/ Delay: Similar to sense sweep 90, but now state dependent. Rather than moving to 90 and back if an object is detected, the paddle changes state depending on the state it is currently in.
		If 90, move to 0
		If 0, move to 90

	Proportional Control: The closer the object is to the paddle's sensor, the more it moves. Calibration is still necessary. Perhaps this will be more sensitive to finer interactions, but runs a higher risk of noise. It still needs to be tested in a queue structure.

Structure for multiple sensors/servos:

	Sense Sweep Back Forth:
		Queue is implemented(right now, only for Sense abnd Move w/ Delay control scheme), and multiple sensors/multiple servos implemented.
		In each loop:
		   Each sensor detects. If there is an event, it adds it to the queue. 
		   Queue deploys an event

		Sense Sweep back and forth is our most recent and most complex implentation, with an effective structure for multiple servos/sensors. We have yet to try this structure with other control schemes

Next steps are:
  1. to improve the queue deploying (partially complete the event and move on to the next, rather than waiting for completion)
  2. Reduce Sensor noise
  3. Create a default interaction (perhaps tell time, since we have 12 servos)




