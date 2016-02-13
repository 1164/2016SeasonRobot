#ifndef ShooterIntake_H
#define ShooterIntake_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Shooter.h"
#include <Constants.h>

#define CARRY	0
#define SHOOT 	2
#define INTAKE 	1
#define ARMED	3

class ShooterIntake: public Subsystem
{
private:
	int state;
	Constants *constants;
	Shooter *shooter;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ShooterIntake(Constants *RickyRicardo);
	void InitDefaultCommand();
	void Update(bool IntakeButton, bool PrepButton, bool ShootButton);
};

#endif
