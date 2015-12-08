# TwistedWaveInstallation
POE Final Project Fall 2015
	Shrinidhi Thirumalai
	Bonnie Ishiguro
	Charlie Mouton
	Jason Lan
	Meg McCauley

Current Working Interaction: 
	Code is sensing_interaction, under the Current Interaction folder

Past Interactions: (Queue structure has been deleted, for now.)

	Sense Sweep 90: Similar to sense_and_move, but don't read sensor values until finished with 0-90 sweep, then sweep back to zero. This is the second implemetation of Sense_and_move, with major improvements

	Sense and Move w/ Delay: Similar to sense sweep 90, but now state dependent. Rather than moving to 90 and back if an object is detected, the paddle changes state depending on the state it is currently in.
		If 90, move to 0
		If 0, move to 90

	Proportional Control: The closer the object is to the paddle's sensor, the more it moves. Calibration is still necessary. Perhaps this will be more sensitive to finer interactions, but runs a higher risk of noise.

Next steps are:
  1. Test different interactions
  2. Time telling default interaction (skeleton code, using old queue structure is in Current Interaction folder)
  3. Filter and calibrate sensors





