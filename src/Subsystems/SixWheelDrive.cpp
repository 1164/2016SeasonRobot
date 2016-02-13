#include "SixWheelDrive.h"
//#include "../RobotMap.h"

SixWheelDrive::SixWheelDrive(Constants *LucielleBall) :
		Subsystem("ExampleSubsystem")
{
	constants = LucielleBall;
	leftBack = new VictorSP(constants->Get("backLeftDrive"));
	rightBack  = new VictorSP(constants->Get("backRightDrive"));
	leftFront  = new VictorSP(constants->Get("frontLeftDrive"));
	rightFront  = new VictorSP(constants->Get("frontRightDrive"));
	leftMid = new VictorSP(constants->Get("leftMidDrive"));
	rightMid = new VictorSP (constants->Get("rightMidDrive"));
	Drivestick = new Joystick(0);
	Drive = new RobotDrive (leftFront, leftBack, rightFront, rightBack);
	shifter = new Solenoid(7);
	ShifterTest = false;
	RightWheelEncoder = new Encoder(constants->Get("RightEncoderA"), constants->Get("RightEncoderB"));
	LeftWheelEncoder = new Encoder(constants->Get("LeftEncoderA"), constants->Get("LeftEncoderB"));

}

void SixWheelDrive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//precision speed
}

long SixWheelDrive::LeftEncoder(){



	return LeftWheelEncoder->Get();
}
long SixWheelDrive::RightEncoder(){


	return RightWheelEncoder->Get();
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
