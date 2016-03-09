#ifndef SixWheelDrive_H
#define SixWheelDrive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotDrive.h>
#include <Joystick.h>
#include <Solenoid.h>
#include <Encoder.h>
#include "../Constants.h"
#include <VictorSP.h>
const double EncoderReset = 0;
//#include <Talon.h>
#include "AHRS.h"

class SixWheelDrive: public Subsystem
{
private:
	RobotDrive *Drive;
	VictorSP *leftBack; //VictorSP
	VictorSP *rightBack;//VictorSP
	VictorSP *rightFront;//VictorSP
	VictorSP *leftFront;//VictorSP
	VictorSP *rightMid;//VictorSP
	VictorSP *leftMid;//VictorSP
	Solenoid *shifter;
	Encoder *RightWheelEncoder;
	Encoder *LeftWheelEncoder;
	bool ShifterTest;
	Constants *constants;
	AHRS *ahrs;


public:
	SixWheelDrive(Constants *LucielleBall);

	void arcadeDrive(float x, float y, bool isHighGear, bool isLowGear);
	void arcadeDrive(float x, float y, bool isHighGear);
	long LeftEncoder();
	long RightEncoder();

	void InitDefaultCommand();

};

#endif
