#include "SixWheelDrive.h"
//#include "../RobotMap.h"

SixWheelDrive::SixWheelDrive() :
		Subsystem("ExampleSubsystem")
{
	leftBack = new Talon(2);
	rightBack  = new Talon(1);
	leftFront  = new Talon(3);
	rightFront  = new Talon(Constants->Get("frontRightDrive"));
	leftMid = new Talon(5);
	rightMid = new Talon (6);
	Drivestick = new Joystick(0);
	Operator = new Joystick(8);
	Drive = new RobotDrive (leftFront, leftBack, rightFront, rightBack);
	shifter = new Solenoid(7);
	ShifterTest = false;

}

void SixWheelDrive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//precision speed
}

void SixWheelDrive::arcadeDrive(float Y, float X){
	Drive->ArcadeDrive(Y, X, false);
	// do stuff
	rightMid->Set(rightFront->Get());
	leftMid->Set(leftFront->Get());

	if (Drivestick->GetRawButton(7))//high gear
		ShifterTest = true;

	if (Drivestick->GetRawButton(5))//low gear
		ShifterTest = false;

	shifter->Set(ShifterTest);

}
