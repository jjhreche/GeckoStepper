/*
	GeckoStepper.h - Library for Gecko type stepper driver
					 US Digital MD1 driver is similar (test unit)
	Author: Christopher Whiting, June 2011
			http://physics.homelinux.com

	Parts of this library were modeled off of the included Arduino
	Stepper library (ver. 0.4), originally written by Tom Igoe.
	See the Arduino Stepper library for details.

	Released into the public domain.
*/

#ifndef GeckoStepper_h

#define GeckoStepper_h

#include "WProgram.h"

#define CW 1
#define CCW -1
#define TRUE 1
#define FALSE 0

class GeckoStepper {
	public:
		// Constructors:
		GeckoStepper(int steprev, int microstep, int stepPin, int dirPin, int disablePin);
		
		// speed setter method:
		int setSpeed(long rpm);					//returns step delay in ms
		
		// move method:
		int step(int steps, int dir);			//returns steps moved
		
		// move 90 degrees
		int move90(int dir);					//returns steps moved
		
		// move 180 degrees
		int move180(int dir);					//returns steps moved
		
		// move n degrees
		int moveDeg(float degrees, int dir);	//returns steps moved
		
		// step method - steps motor by one step given direction
		void stepMotor(void);
		
		// enable/disable method
		void disable(int disable);
		
		// version:
		int version(void);						//returns version number
		
	private:
		//motor and driver parameters
		int _steprev;				//steps per revolution of motor itself
		int _microstep;				//microstep of driver e.g. microstep = 1/10 --> 10
		int _disable;				//enable/disable motor status
		
		// motor pins
		int _stepPin;				//step pin
		int _dirPin;				//direction pin
		int _disablePin;			//disable pin
		
		long _rpm;					//speed
		unsigned long _step_delay;	//delay between steps (ms), based on speed
		int _steps;					//steps to move
		int _dir;					//looking at end of shaft (end of motor by label), LOW = CW = 1, HIGH = CCW = -1
		long _last_step_time;		//timestamp in ms of when the last step was taken
		int _step_number;			//step the motor is on
		float _degrees;				//used to specify number of degrees to move
		
};

#endif