#include "Shooter.h"
//#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include <Timer.h>



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
	shootedIndex = new DigitalInput(constants->Get("shootedDigitalIndex"));
	motorTimer = new Timer;
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

bool Shooter::AtSetpoint(){
	return false;
}

double Shooter::ReturnPIDInput()
{
	if (shooterIndex->Get()){
		shooterEncoder->Reset();
	}
	if (shootedIndex->Get()){
		shooterMotor1->Set(-127);
		shooterMotor2->Set(-127);
	}
	return shooterEncoder->Get();
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
}

void Shooter::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	shooterMotor1->Set(output);
	shooterMotor2->Set(output);
}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}
