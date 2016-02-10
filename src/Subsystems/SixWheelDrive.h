#ifndef SixWheelDrive_H
#define SixWheelDrive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotDrive.h>
#include <Joystick.h>
#include <Solenoid.h>

class SixWheelDrive: public Subsystem
{
private:
	RobotDrive *Drive;
	Talon *leftBack;
	Talon *rightBack;
	Talon *rightFront;
	Talon *leftFront;
	Talon *rightMid;
	Talon *leftMid;
	Joystick * Drivestick;
	Joystick *Operator
	Solenoid *shifter;
	bool ShifterTest;


public:
	SixWheelDrive();

	void arcadeDrive(float x, float y);

	void InitDefaultCommand();
};

#endif
