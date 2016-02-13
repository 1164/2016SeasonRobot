#include "ShooterIntake.h"
//#include "../RobotMap.h"

ShooterIntake::ShooterIntake() :
		Subsystem("ShoooterIntake")
{

}

void ShooterIntake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterIntake::Update(bool IntakeButton, bool PrepButton, bool ShootButton){
	switch(state){
		case CARRY:
			//default state in which the other states may be accessed from
			//shooter in middle position(b)
			//roller down/off
			//intake user
			break;
		case INTAKE:
			//activate when intake button pressed & continue when pressed once button release-> carry
			//shooter position fully down (a)
			//roller down
			//roller suck
			break;
		case ARMED:
			//activate when armed button is pressed, otherwise carry
			//lower shooter for prep to shoot
			//have roller down/off
			//intake used

			break;
		case SHOOT:
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


