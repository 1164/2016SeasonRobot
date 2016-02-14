#include "SixWheelDrive.h"
//#include "../RobotMap.h"

SixWheelDrive::SixWheelDrive(Constants *LucielleBall) :
		Subsystem("SixWheeelDrive")
{
	constants = LucielleBall;
	leftBack = new Talon(constants->Get("backLeftDrive"));
	rightBack  = new Talon(constants->Get("backRightDrive"));
	leftFront  = new Talon(constants->Get("frontLeftDrive"));
	rightFront  = new Talon(constants->Get("frontRightDrive"));
	leftMid = new Talon(constants->Get("leftMidDrive"));
	rightMid = new Talon (constants->Get("rightMidDrive"));
	leftBack->SetInverted(constants->Get("leftBackInvert"));
	leftMid->SetInverted(constants->Get("leftMidInvert"));
	leftFront->SetInverted(constants->Get("leftFrontInvert"));
	rightBack->SetInverted(constants->Get("rightBackInvert"));
	rightMid->SetInverted(constants->Get("rightMidInvert"));
	rightFront->SetInverted(constants->Get("rightFrontInvert"));
	Drive = new RobotDrive (leftFront, leftBack, rightFront, rightBack);
	shifter = new Solenoid(constants->Get("ShifterSolenoid"));
	ShifterTest = false;
	RightWheelEncoder = new Encoder(constants->Get("RightEncoderA"), constants->Get("RightEncoderB"));
	LeftWheelEncoder = new Encoder(constants->Get("LeftEncoderA"), constants->Get("LeftEncoderB"));
	Drive->SetSafetyEnabled(false);
	try {
		/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
		/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
		/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
		ahrs = new AHRS(SPI::Port::kMXP);
	} catch (std::exception ex ) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	if (ahrs){
		LiveWindow::GetInstance()->AddSensor("IMU", "Angle", ahrs);
	}
	}

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

	arcadeDrive(Y,X,ShifterTest);

}
void SixWheelDrive::arcadeDrive(float Y, float X, bool isHighGear){
	Drive->ArcadeDrive(Y, X, false);
	rightMid->Set(rightFront->Get());
	leftMid->Set(leftFront->Get());

	ShifterTest=isHighGear;

	shifter->Set(ShifterTest);
	ahrs->GetAngle();
}

