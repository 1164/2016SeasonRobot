#ifndef RollerArm_H
#define RollerArm_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <CANTalon.h>
#include <Constants.h>

class RollerArm: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Constants *constants;
	CANTalon *RollerControl;
public:
	RollerArm(Constants *Ethel);
	void InitDefaultCommand();
	void Update(double setpoint);
};

#endif
