From Arduino's website:

Arduino is an open-source electronics prototyping platform based
on flexible, easy-to-use hardware and software. It's intended for
artists, designers, hobbyists, and anyone interested in creating
interactive objects or environments.

For more information, refer to the documentation and website at:
http://www.arduino.cc/

Parts of this library were modeled off of the included Arduino
Stepper library (ver. 0.4), originally written by Tom Igoe.
See the Arduino Stepper library for details.

This library is released into the public domain.

#############################################################

      GeckoStepper Library, v0.1 (Arduino-Compatible)

      Author: Christopher Whiting, June 2011

#############################################################

This library provides a means of controlling a GeckoDriver
type motor driver using the Arduino open-source platform.
The library was tested using a US Digital MD1 motor driver
The available methods are listed below.

Please send comments, questions, or suggestions by using
the contact form at http://physics.homelinux.com/



#=============================

             METHODS

#=============================

###
Create a GeckoStepperobject:

GeckoStepper(int steprev, int microstep, int stepPin, int dirPin, int disablePin)
	steprev - steps per revolution of the motor itself
	microstep - microstep resolution of stepper driver (10 = 1/10 microstep)
	stepPin - step pin on Arduinio hardware to driver
	dirPin - direction pin on Arduino hardware to driver
	disablePin - disable pin on Arduino hardware to driver

###
Set speed in RPMs of motor movement:

int setSpeed(long rpm)
	rpm - motor movement speed, in rotations per minute

	returns: the time to delay between steps (step_delay)

###
Move motor by a specified number of steps

int step(int steps, int dir)
	steps - move motor by this many steps
	dir - move motor in this direction [CW|CCW]

	returns: number of steps moved

###
Steps the motor by one step

void stepMotor(void)

###
Move motor by 90 or 180 degrees

int move90(int dir), move180(int dir)
	dir - move motor in this direction [CW|CCW]

	returns: number of steps moved

###
Move the motor by a specified number of degrees

int moveDeg(int degrees, int dir)
	degrees - move motor by this many degrees
	dir - movethe motor inthis direction [CW|CCW]

	returns: number of steps moved

###
Disable the motor drive

void disable(int disable)
	disable - set the driver's disable status [TRUE|FALSE]
		- disable=TRUE, driver is disabled

	returns: void (for now...)
	NOTE: this function does  not seem  to work under current test setup

###
Get thelibrary version

int version(void)
	returns: the library version