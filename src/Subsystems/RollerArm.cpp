#include "RollerArm.h"
//#include "../RobotMap.h"

RollerArm::RollerArm(Constants *Ethel) :
		Subsystem("RollerArm")
{
	constants = Ethel;
	RollerControl = new CANTalon(constants->Get("RollerArmControl"));

	RollerControl->SetPID(constants->Get("RollerControlP"), constants->Get("RollerControlI"), constants->Get("RollerControlD"), constants->Get("RollerControlF"));
	RollerControl->SetCloseLoopRampRate(constants->Get("RCloseLoopRampRate"));
	RollerControl->SetIzone(constants->Get("RollerControlIzone"));

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
