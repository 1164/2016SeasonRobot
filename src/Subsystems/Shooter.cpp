#include "Shooter.h"
//#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include <Timer.h>
#include "PIDController.h"
#include <memory>



Shooter::Shooter(Constants *ILoveLucy) :
		PIDSubsystem("Shooter", 1.0, 0.0, 0.0)
{
	constants = ILoveLucy;
	shooterEncoder = new Encoder(constants->Get("shooterEncoderA"), constants->Get("shooterEncoderB"));
	shooterMotor1 = new VictorSP(constants->Get("shooterMotor1"));
	shooterMotor2 = new VictorSP(constants->Get("shooterMotor2"));

	shooterMotor1->SetInverted(constants->Get("shooterMotor1Invert") == 1);
	shooterMotor2->SetInverted(constants->Get("shooterMotor2Invert") == 1);

	GetPIDController()->SetPID(constants->Get("shooterPGain"), constants->Get("shooterIGain"), constants->Get("shooterDGain"));
	shooterIndex = new DigitalInput(constants->Get("shooterDigitalIndex"));
	motorTimer = new Timer;
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

bool Shooter::AtSetpoint(){
	return abs(GetSetpoint()-GetPosition()) < constants->Get("shooterDeadband");
}

double Shooter::ReturnPIDInput()
{

	return ReadEncoder();

	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
}
long Shooter::ReadEncoder()
{
	if (!shooterIndex->Get()){
		shooterEncoder->Reset();
	}
	return shooterEncoder->Get();
}
bool Shooter::Fire()
{
	if (ReadEncoder()<=constants->Get("shooterShootPoint")){
		shooterMotor1->Set(0);
		shooterMotor2->Set(0);
		DriverStation::GetInstance().ReportError("Stopped");
		return true;
	}
	else{
		shooterMotor1->Set(1);
		shooterMotor2->Set(1);
		DriverStation::GetInstance().ReportError("Shooting");
		return false;
	}


}
bool Shooter::Intake()
{
	if (shooterIndex->Get()==1){
		shooterMotor1->Set(-.1);
		shooterMotor2->Set(-.1);
		return false;
	}
	else{
		ReadEncoder(); //reads the above function in order to reset the encoder
		Stop();
		return true;
	}
}

void Shooter::Stop() {
	shooterMotor1->Set(0);
	shooterMotor2->Set(0);
}

void Shooter::ResetPID() {
	//PIDSubsystem::GetPIDController();
	PIDSubsystem::GetPIDController()->Reset();
}

void Shooter::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	output = -output;
	if (output > .3) {
		shooterMotor1->Set(.3);
		shooterMotor2->Set(.3);
	} else if (output < -.1){
		shooterMotor1->Set(-.1);
		shooterMotor2->Set(-.1);
	}else{
		shooterMotor1->Set(output);
		shooterMotor2->Set(output);
	}

}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}
