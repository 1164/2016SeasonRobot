#ifndef SixWheelDrive_H
#define SixWheelDrive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotDrive.h>
#include <Joystick.h>
#include <Solenoid.h>
#include <Encoder.h>
#include <Constants.h>
const double EncoderReset = 0;

class SixWheelDrive: public Subsystem
{
private:
	RobotDrive *Drive;
	VictorSP *leftBack;
	VictorSP *rightBack;
	VictorSP *rightFront;
	VictorSP *leftFront;
	VictorSP *rightMid;
	VictorSP *leftMid;
	Joystick * Drivestick;
	Solenoid *shifter;
	Encoder *RightWheelEncoder;
	Encoder *LeftWheelEncoder;
	bool ShifterTest;
	Constants *constants;



public:
	SixWheelDrive(Constants *LucielleBall);

	void arcadeDrive(float x, float y);
	long LeftEncoder();
	long RightEncoder();

	void InitDefaultCommand();
};

#endif
