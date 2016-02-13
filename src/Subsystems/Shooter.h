#ifndef Shooter_H
#define Shooter_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"

class Shooter: public PIDSubsystem
{
public:
	Shooter();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
};

#endif
