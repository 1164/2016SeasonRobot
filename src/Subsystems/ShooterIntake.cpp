#include "ShooterIntake.h"
//#include "../RobotMap.h"

ShooterIntake::ShooterIntake(Constants *RickyRicardo) :
		Subsystem("ShoooterIntake")
{
		constants = RickyRicardo;
		shooter = new Shooter(constants);
		state = CARRY;
		rollerEncodeIn = new Encoder(constants->Get("RollerEncoderInA"), constants->Get("RollerEncoderInB"));
		rollerArm = new Encoder(constants->Get("RollerEncoderArmA"), constants->Get("RollerEncoderArmB"));
}

void ShooterIntake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterIntake::Update(bool IntakeButton, bool ArmedButton, bool ShootButton, bool ReleaseButton, bool CarryButton){
	switch(state){
		case CARRY:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("CARRYSetPoint"));

			//default state in which the other states may be accessed from (done)
			//shooter in middle position(b) (done/setpoint)
			//roller up/off
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
			//roller mid to down
			//roller suck
			break;
		case ARMED:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("ARMEDSetPoint"));
			//activate when armed button is pressed, otherwise carry
			//lower shooter for prep to shoot
			//have roller mid/off
			//intake used
			if (ShootButton && shooter->AtSetpoint()){
				state = SHOOT;
			}
			break;
		case SHOOT:
			//not sure how we are going to proceed with this// shooter->PIDSubsystem::SetSetpoint(constants->Get("SHOOTSetPoint"));
			//only from armed if shoot button pressed otherwise, carry
			//roller off/mid
			//intake user
			//shooter launch
			//reset to carry position(b)->carry
			break;
		case RELEASE:
			//roller goes down to mid to down
			//roller inverts the roller motor
			//shooter into intake position

			break;
		default: std::cout<<"default\n"; //no error
			state = CARRY;
			break;
	}


}


