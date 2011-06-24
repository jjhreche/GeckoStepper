/*
	GeckoStepper.cpp - Library for GeckoDrive type stepper driver
					   US Digital MD1 driver is similar (test unit)
	Author: Christopher Whiting, June 2011
			http://physics.homelinux.com

	Parts of this library were modeled off of the included Arduino
	Stepper library (ver. 0.4), originally written by Tom Igoe.
	See the Arduino Stepper library for details.

	Released into the public domain.
*/

#include "GeckoStepper.h"

static const int VERSION = 1;

/*
	Constructor
	Sets the pins which control the motor (i.e. control the motor driver)
	Sets motor and motor driver parameters
*/
GeckoStepper::GeckoStepper(int steprev, int microstep, int stepPin, int dirPin, int disablePin){
	//pins for motor control
	this->_stepPin = stepPin;
	this->_dirPin = dirPin;
	this->_disablePin = disablePin;
	
	//set pins on microcontroller
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(disablePin, OUTPUT);
	
	this->_step_number = 0;			//step the motor is on
	this->_rpm = 0;					//motor speed (rpm)
	this->_dir = 0;					//motor direction
	this->_last_step_time = 0;		//timestamp (ms) of the last step taken
	this->_steprev = steprev;		//steps per revolution of the motor itself
	this->_microstep = microstep;	//microstep setting of motor driver, e.g. microstep = 1/10 --> 10
}

/*
	Set speed in revolutions per minute (rpm)
*/
int GeckoStepper::setSpeed(long rpm){
	this->_rpm = rpm;
	this->_step_delay = 60L * 1000L / (this->_steprev * this->_microstep) / _rpm;
	return this->_step_delay;
}

/*
	Moves the motor by the specified number of steps
	Direction specified by CW or CCW, defined by looking at shaft end-on
*/
int GeckoStepper::step(int steps, int dir){
	this->_dir = dir;
	this->_steps = steps;
	int _steps_left = steps; //number of steps to move
	
	// decrease number of steps by one after move one step
	while(_steps_left > 0){
		//check _step_delay, if speed not set yet, must set to 1
		if(_step_delay == 0) { _step_delay = 1; }
		//move only if the correct delay has passed
		if(millis() - this->_last_step_time >= this->_step_delay){
			//get timestamp of the step
			this->_last_step_time = millis();
			//increase or decrease step number depending on direction
			//CW
			if(this->_dir == 1){
				this->_step_number++;
				//if moved the user-specified number of steps, reset to zero
				if(this->_step_number == this->_steps){
					this->_step_number = 0;
				}
				digitalWrite(this->_dirPin, LOW);
				stepMotor();
			//CCW
			} else if(this->_dir == -1) {
				if(this->_step_number == 0){
					this->_step_number = this->_steps;
				}
				digitalWrite(this->_dirPin, HIGH);
				stepMotor();
				this->_step_number--;
			}
			//decrease the steps left
			_steps_left--;
		}
				
	}
	return this->_steps;
}

/*
	Steps motor by one step
*/
void GeckoStepper::stepMotor(void){
	digitalWrite(this->_stepPin, HIGH);
	digitalWrite(this->_stepPin, LOW);
}

/*
	Move motor 90 degrees
*/
int GeckoStepper::move90(int dir){
	this->_dir = dir;
	int stepsToMove = (this->_steprev * this->_microstep)/4;
	this->step(stepsToMove, _dir);
	return stepsToMove;
}

/*
	Move motor 180 degrees
*/
int GeckoStepper::move180(int dir){
	this->_dir = dir;
	int stepsToMove = (this->_steprev * this->_microstep)/2;
	this->step(stepsToMove, _dir);
	return stepsToMove;
}

/*
	Move n degrees
*/
int GeckoStepper::moveDeg(float degrees, int dir){
	this->_degrees = degrees;
	this->_dir = dir;
	int stepsToMove = (int)(this->_degrees/(360.0/(this->_steprev * this->_microstep))) + 1;
	this->step(stepsToMove, _dir);
	return stepsToMove;
}

/*
	Enable/disable motor
*/
void GeckoStepper::disable(int disable){
	this->_disable = disable;
	if(this->_disable == TRUE){
		digitalWrite(_disablePin, HIGH);
	}
	else if(this->_disable == FALSE){
		digitalWrite(_disablePin, LOW);
	}
}

/*
	Version of library
*/
int GeckoStepper::version(void){
	return VERSION;
}
