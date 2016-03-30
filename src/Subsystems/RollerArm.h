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
	bool lastIntakeButton;
	bool lastArmedButton;
	bool lastUpButton;
	bool lastDownButton;
	double CurrentSetPoint;

	bool upState;
public:
	RollerArm(Constants *Ethel);
	void InitDefaultCommand();
	void Update(double joystick, bool IntakeButton, bool ArmedButton, bool DownButton, bool UpButton);
	double GetPosition();
	void Set(double setArm);
	CANTalon *RollerControl;
};

#endif
