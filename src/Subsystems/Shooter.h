#ifndef Shooter_H
#define Shooter_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include <Constants.h>
#include <Encoder.h>
#include <VictorSP.h>
#include <DigitalInput.h>
#include <Timer.h>

class Shooter: public PIDSubsystem
{
private:
	Constants *constants;
	Encoder *shooterEncoder;
	VictorSP *shooterMotor1;
	VictorSP *shooterMotor2;
	DigitalInput *shooterIndex;
	Timer *motorTimer;

public:
	Shooter(Constants *ILoveLucy);
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	long ReadEncoder();
	bool Fire();
	void Stop();
	void InitDefaultCommand();
	bool AtSetpoint();


};

#endif
