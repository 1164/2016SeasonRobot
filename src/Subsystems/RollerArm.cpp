#include "RollerArm.h"
//#include "../RobotMap.h"

RollerArm::RollerArm(Constants *Ethel) :
		Subsystem("RollerArm")
{
	constants = Ethel;
	RollerControl = new CANTalon(constants->Get("RollerArmControl"));
	lastIntakeButton = false;
	lastArmedButton = false;

	RollerControl->Set(0);
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
void RollerArm::Update(double joystick, bool IntakeButton, bool ArmedButton){
	double gain = constants->Get("RollerArmGain");
	RollerControl->SetControlMode(CANSpeedController::kPosition);
	RollerControl->Enable();
	if(IntakeButton == true && lastIntakeButton == false){
		RollerControl->Set(constants->Get("RollerEncPoint"));
	}
	if(ArmedButton == true && lastArmedButton == false){
		RollerControl->Set(constants->Get("RollerEncArmed"));
	}
	if(joystick > 0.05){
		RollerControl->Set(RollerControl->GetSetpoint() +(joystick * gain));
	}
	if(joystick < -0.05){
		RollerControl->Set(RollerControl->GetSetpoint() +(joystick * gain));
	}


	lastArmedButton = ArmedButton;
	lastIntakeButton = IntakeButton;


}

void RollerArm::Set(double setArm){
	RollerControl ->Set(setArm);
}
