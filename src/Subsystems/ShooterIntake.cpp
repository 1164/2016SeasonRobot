#include "ShooterIntake.h"
#include "RollerArm.h"

//#include "../RobotMap.h"

ShooterIntake::ShooterIntake(Constants *RickyRicardo) :
		Subsystem("ShoooterIntake")
{
		constants = RickyRicardo;
		shooter = new Shooter(constants);
		RollerMotor = new VictorSP(constants->Get("RollerMotor"));
		Rollerarm = new RollerArm(constants);

		flipper1 = new Solenoid(constants->Get("flipper1"));
		flipper2 = new Solenoid(constants->Get("flipper2"));

		state = CARRY;
		shooterEncoder = new Encoder(constants->Get("shooterEncoderA"), constants->Get("shooterEncoderB"));
}

void ShooterIntake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterIntake::Update(bool IntakeButton, bool ArmedButton, bool ShootButton, bool DownRollButton, bool UpRollButton, double RollerAxis){
	int lastState = state;
	Rollerarm->Update(RollerAxis, IntakeButton, ArmedButton,DownRollButton, UpRollButton);
	switch(state){
		case CARRY:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("CARRYSetPoint"));
			shooter->PIDSubsystem::Enable();

			// double solenoid needs reverse output on the two outputs if it's output is
			// incorrect make flipperOut in the .neo file the inverse of what it is 0 or 1.
			// INTAKE is the only state with a different NOT signs on the output
			flipper1->Set(constants->Get("flipperOut"));
			flipper2->Set(!constants->Get("flipperOut"));

			//Rollerarm->Update(constants->Get("rollerEncPoint"));

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
			//shooter->PIDSubsystem::SetSetpoint(constants->Get("INTAKESetPoint"));
			shooter->PIDSubsystem::Disable();
			shooter->Intake();

			// double solenoid needs reverse output on the two outputs if it's output is
			// incorrect make flipperOut in the .neo file the inverse of what it is 0 or 1.
			// INTAKE is the only state with a different NOT signs on the output
			flipper1->Set(!constants->Get("flipperOut"));
			flipper2->Set(constants->Get("flipperOut"));
			//activate when intake button pressed & continue when pressed once button release-> carry
			//shooter position fully down (a)... break beam sensor
			//roller mid to down...rotary encoder...break beam sensor
			//roller suck...rotary encoder...motor:VictorSP
			if(!IntakeButton){
				state = CARRY;
				//IF intake button released, revert to carry.
			}
			break;
		case ARMED:
			shooter->PIDSubsystem::SetSetpoint(constants->Get("ARMEDSetPoint"));
			shooter->PIDSubsystem::Enable();


			// double solenoid needs reverse output on the two outputs if it's output is
			// incorrect make flipperOut in the .neo file the inverse of what it is 0 or 1.
			flipper1->Set(constants->Get("flipperOut"));
			flipper2->Set(!constants->Get("flipperOut"));
			//lower shooter for prep to shoot
			//have roller mid/off...rotary encoder...break beam sensor

			if (ShootButton && shooter->AtSetpoint()){
				state = SHOOT;
			}
			if(!ArmedButton){
				state = CARRY;
			}
			break;
		case SHOOT:
			shooter->PIDSubsystem::Disable();
			//Rollerarm->Update(constants->Get("RollerEncArmed"));

			// double solenoid needs reverse output on the two outputs if it's output is
			// incorrect make flipperOut in the .neo file the inverse of what it is 0 or 1.
			flipper1->Set(constants->Get("flipperOut"));
			flipper2->Set(!constants->Get("flipperOut"));

			//not sure how we are going to proceed with this
			//only from armed if shoot button pressed otherwise, carry
			//roller off/mid...rotary encoder...break beam sensor
			//intake user
			//shooter launch

			if (shooter->Fire()){
				state = CARRY;
				}
			break;

		default: std::cout<<"default\n"; //no error
			state = CARRY;
			break;
	}
	if (state != lastState){
		shooter->ResetPID();
	}
}
