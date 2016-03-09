#ifndef ShooterIntake_H
#define ShooterIntake_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Shooter.h"
#include "RollerArm.h"
#include <Constants.h>
#include <Encoder.h>
#include <VictorSP.h>

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
	Encoder *rollerArm;
	RollerArm *Rollerarm;
	VictorSP *Roller;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ShooterIntake(Constants *RickyRicardo);
	void InitDefaultCommand();
	void Update(bool IntakeButton, bool ArmedButton, bool ShootButton, bool ReleaseButton, bool CarryButton);
	void RollerInvert(bool OuttakeButton, bool IntakeButton);
};

#endif
