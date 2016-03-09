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
	//Encoder *shooterEncoder;
	VictorSP *shooterMotor1;
	VictorSP *shooterMotor2;
	//DigitalInput *shooterIndex;
	//DigitalInput *shootedIndex;
	Timer *motorTimer;

public:
	Shooter(Constants *ILoveLucy);
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	bool AtSetpoint();


};

#endif
