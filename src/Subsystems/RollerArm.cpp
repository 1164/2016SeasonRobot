#include "RollerArm.h"
#include <cmath>
//#include "../RobotMap.h"

RollerArm::RollerArm(Constants *Ethel) :
		Subsystem("RollerArm")
{
	constants = Ethel;
	RollerControl = new CANTalon(constants->Get("RollerArmControl"));
	lastIntakeButton = false;
	lastArmedButton = false;
	lastUpButton = false;
	lastDownButton = false;
	upState = false;
	CurrentSetPoint = 0.0;

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
void RollerArm::Update(double joystick, bool IntakeButton, bool ArmedButton, bool DownButton, bool UpButton){
	double gain = constants->Get("RollerArmGain");
	RollerControl->SetControlMode(CANSpeedController::kPosition);
	RollerControl->Enable();
	if(IntakeButton == true && lastIntakeButton == false){
		//RollerControl->Set(constants->Get("RollerEncPoint"));
		CurrentSetPoint = constants->Get("RollerEncPoint");
		upState = false;
	}
	if(ArmedButton == true && lastArmedButton == false){
		//RollerControl->Set(constants->Get("RollerEncArmed"));
		CurrentSetPoint = constants->Get("RollerEncArmed");
		upState = false;
	}
	if(DownButton == true && lastDownButton == false){
		//RollerControl->Set(constants->Get("RollerEncDown"));
		CurrentSetPoint = constants->Get("RollerEncDown");
		upState = false;
	}
	if(UpButton == true && lastUpButton == false){
		RollerControl->SetControlMode(CANSpeedController::kPercentVbus);
		RollerControl->Set(constants->Get("RollerUpSpeed"));

		upState = true;
	}
	if(joystick > 0.1){
		//RollerControl->Set(RollerControl->GetSetpoint() +(joystick * gain));
		CurrentSetPoint = CurrentSetPoint + (joystick * gain);
		//upState = false;
	}
	if(joystick < -0.1){
		//RollerControl->Set(RollerControl->GetSetpoint() +(joystick * gain));
		CurrentSetPoint = CurrentSetPoint + (joystick * gain);
		//upState = false;
	}

	if (upState) {
		RollerControl->SetControlMode(CANSpeedController::kPercentVbus);
		RollerControl->Set(constants->Get("RollerUpSpeed"));
		if ( RollerControl->GetPinStateQuadIdx() == 0) {
			upState = false;
			RollerControl->Set(0);
			CurrentSetPoint = 0;
		}

	} else {
		RollerControl->SetControlMode(CANSpeedController::kPosition);
		CurrentSetPoint = fmax(0.0, CurrentSetPoint);
		CurrentSetPoint = fmin(CurrentSetPoint, 40000);
		RollerControl->Set(CurrentSetPoint);
	}

	lastArmedButton = ArmedButton;
	lastIntakeButton = IntakeButton;
	lastUpButton = UpButton;
	lastDownButton = DownButton;
}

void RollerArm::Set(double setArm){
	RollerControl ->Set(setArm);
}
