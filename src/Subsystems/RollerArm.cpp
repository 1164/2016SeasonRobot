#include "RollerArm.h"
//#include "../RobotMap.h"

RollerArm::RollerArm(Constants *Ethel) :
		Subsystem("RollerArm")
{
	constants = Ethel;
	RollerControl = new CANTalon(constants->Get("RollerArmControl"));

	RollerControl->SetPID(constants->Get("RollerArmControlP"), constants->Get("RollerArmControlI"), constants->Get("RollerArmControlD"));
	RollerControl->SetCloseLoopRampRate(constants->Get("RCloseLoopRampRate"));
	RollerControl->SetIzone(constants->Get("RollerArmControlIzone"));

}

void RollerArm::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void RollerArm::Update(double setpoint){

}
