#include "SixWheelDrive.h"
//#include "../RobotMap.h"


SixWheelDrive::SixWheelDrive(Constants *LucielleBall) :
		Subsystem("SixWheeelDrive")
{
	constants = LucielleBall;
	leftBack = new VictorSP(constants->Get("backLeftDrive")); //VictorSP
	rightBack  = new VictorSP(constants->Get("backRightDrive"));//VictorSP
	leftFront  = new VictorSP(constants->Get("frontLeftDrive"));//VictorSP
	rightFront  = new VictorSP(constants->Get("frontRightDrive"));//VictorSP
	leftMid = new VictorSP(constants->Get("leftMidDrive"));//VictorSP
	rightMid = new VictorSP(constants->Get("rightMidDrive"));//VictorSP
	leftBack->SetInverted(constants->Get("leftBackInvert")== 1);
	leftMid->SetInverted(constants->Get("leftMidInvert")== 1);
	leftFront->SetInverted(constants->Get("leftFrontInvert")== 1);
	rightBack->SetInverted(constants->Get("rightBackInvert")== 1);
	rightMid->SetInverted(constants->Get("rightMidInvert")== 1);
	rightFront->SetInverted(constants->Get("rightFrontInvert")== 1);
	Drive = new RobotDrive (leftFront, leftBack, rightFront, rightBack);
	shifter = new Solenoid(constants->Get("ShifterSolenoid"));
	ShifterTest = false;
	RightWheelEncoder = new Encoder(constants->Get("RightEncoderA"), constants->Get("RightEncoderB"));
	LeftWheelEncoder = new Encoder(constants->Get("LeftEncoderA"), constants->Get("LeftEncoderB"));
	Drive->SetSafetyEnabled(false);
	/*try {
		/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
		/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
		/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
		/*ahrs = new AHRS(SPI::Port::kMXP);
	} catch (std::exception ex ) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::GetInstance().ReportError(err_string.c_str());
	if (ahrs){
		LiveWindow::GetInstance()->AddSensor("IMU", "Angle", ahrs);
	}
	}*/

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
void SixWheelDrive::arcadeDrive(float Y, float X, bool isHighGear, bool isLowGear){

	if (isHighGear)//high gear
		ShifterTest = true;

	if (isLowGear)//low gear
		ShifterTest = false;

	if (ShifterTest){
		X=X*constants->Get("HighGearXGain");
		Y=Y*constants->Get("HighGearYGain");
	}
	else{
		X=X*constants->Get("LowGearXGain");
		Y=Y*constants->Get("LowGearYGain");
	}
	if (X<.05 && X>-.05){
		X=0;
	}
	if (Y<.05 && Y>-.05){
			Y=0;
	}


	arcadeDrive(Y,X,ShifterTest);
}
void SixWheelDrive::arcadeDrive(float Y, float X, bool isHighGear){
	// Ian's Cheezy drive algorithm
	// algorithm sets a constant difference between left and right drive
	// for all y settings difference is set by x axis.

	// Left and right speed are set for driving with the
	// + and - X and Y sets. This works in all cases until you get
	// a number input from joystick such as (.5,1) this would set the
	// leftSpeed = 1.5 rightSpeed = .5, We want constant different which should
	// be left = 1 right = 0 so we use the if's to catch this issue and
	// subtract the extra .5 from the left speed from the right speed
	double leftSpeed = Y + X;
	double rightSpeed = Y - X;

	if (leftSpeed > 1)	{
		rightSpeed = rightSpeed - (leftSpeed - 1);
		leftSpeed = 1;
	} else if (leftSpeed < -1)	{
		rightSpeed = rightSpeed - (leftSpeed + 1);
		leftSpeed = -1;
	} else if (rightSpeed > 1) {
		leftSpeed = leftSpeed - (rightSpeed - 1);
	} else if (rightSpeed < -1) {
		leftSpeed = leftSpeed - (rightSpeed + 1);
	}

	Drive->TankDrive(leftSpeed, rightSpeed, false);
	// End Ian's Cheezy algorithm

	rightMid->Set(rightFront->Get());
	leftMid->Set(leftFront->Get());

	ShifterTest=isHighGear;

	shifter->Set(ShifterTest);
}

