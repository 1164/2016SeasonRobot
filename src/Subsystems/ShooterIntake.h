#ifndef ShooterIntake_H
#define ShooterIntake_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Shooter.h"
#include "Shooter.cpp"
#include "RollerArm.h"
#include "RollerArm.cpp"
#include <Constants.h>
#include <Encoder.h>

#define CARRY	0
#define SHOOT 	2
#define INTAKE 	1
#define ARMED	3
#define RELEASE	4

class ShooterIntake: public Subsystem
{
private:
	int state;
	Constants *constants;
	Shooter *shooter;
	Encoder *rollerEncodeIn;
	Encoder *rollerArm;
	RollerArm *Rollerarm;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ShooterIntake(Constants *RickyRicardo);
	void InitDefaultCommand();
	void Update(bool IntakeButton, bool ArmedButton, bool ShootButton, bool ReleaseButton, bool CarryButton);
};

#endif
