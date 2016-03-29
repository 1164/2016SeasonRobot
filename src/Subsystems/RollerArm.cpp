#include "RollerArm.h"
//#include "../RobotMap.h"

RollerArm::RollerArm(Constants *Ethel) :
		Subsystem("RollerArm")
{
	constants = Ethel;
	RollerControl = new CANTalon(constants->Get("RollerArmControl"));

	//RollerControl->EnableZeroSensorPositionOnIndex(true, true);
	RollerControl->SetFeedbackDevice(CANTalon::QuadEncoder);
	RollerControl->SetPID(constants->Get("RollerArmControlP"), constants->Get("RollerArmControlI"), constants->Get("RollerArmControlD"));
	//RollerControl->SetCloseLoopRampRate(constants->Get("RCloseLoopRampRate"));
	RollerControl->SetIzone(constants->Get("RollerArmControlIzone"));
	//RollerControl->GetPinStateQuadIdx();
	//RollerControl->ConfigPeakOutputVoltage(constants->Get("RollerMaxVoltageDown"),constants->Get("RollerMaxVoltageUp"));

	//RollerControl->EnableZeroSensorPositionOnIndex(false, true);
}

double RollerArm::GetPosition() {
	RollerControl->ConfigPeakOutputVoltage(constants->Get("RollerMaxVoltageDown"),constants->Get("RollerMaxVoltageUp"));
	if (RollerControl->GetPinStateQuadIdx() == 0) {
		RollerControl->SetPosition(0);
	}
	return RollerControl->GetPosition();
}

void RollerArm::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void RollerArm::Update(double setpoint){
	RollerControl->SetControlMode(CANSpeedController::kPosition);
	RollerControl->Enable();
	RollerControl->Set(setpoint);
}

void RollerArm::Set(double setArm){
	RollerControl ->Set(setArm);
}
