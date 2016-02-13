#include "ShooterIntake.h"
//#include "../RobotMap.h"

ShooterIntake::ShooterIntake(Constants *RickyRicardo) :
		Subsystem("ShoooterIntake")
{
		constants = RickyRicardo;
		shooter = new Shooter(constants);
		state = CARRY;
}

void ShooterIntake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterIntake::Update(bool IntakeButton, bool ArmedButton, bool ShootButton){
	switch(state){
		case CARRY:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("CARRYSetPoint"));
			//default state in which the other states may be accessed from
			//shooter in middle position(b)
			//roller down/off
			//intake user
			if (IntakeButton){
				state = INTAKE;
			}
			else if(ArmedButton){
				state = ARMED;
			}
			break;
		case INTAKE:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("INTAKESetPoint"));
			//activate when intake button pressed & continue when pressed once button release-> carry
			//shooter position fully down (a)
			//roller down
			//roller suck
			break;
		case ARMED:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("ARMEDSetPoint"));
			//activate when armed button is pressed, otherwise carry
			//lower shooter for prep to shoot
			//have roller down/off
			//intake used
			if (ShootButton && shooter->AtSetpoint()){
				state = SHOOT;
			}
			break;
		case SHOOT:
			//not sure how we are going to proceed with this// shooter->PIDSubsystem::SetSetpoint(constants->Get("SHOOTSetPoint"));
			//only from armed if shoot button pressed otherwise, carry
			//roller off
			//intake user
			//shooter launch
			//reset to carry position(b)->carry
			//keep roller down during whole process
			break;
		default: std::cout<<"default\n"; //no error
			state = CARRY;
			break;
	}


}


