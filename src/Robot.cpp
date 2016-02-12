#include "WPILib.h"
#include <iostream>
#include <Joystick.h>
#include <TalonSRX.h>
#include <Talon.h>
#include <Speedcontroller.h>
#include <Constants.h>
#include <Subsystems/SixWheelDrive.h>


class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	Joystick *Drivestick;
	Constants *constants;
	Talon *launcher;
	SixWheelDrive *Drive;
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	void RobotInit()
	{

		constants = new Constants();
		Drivestick = new Joystick(0);
		lw = LiveWindow::GetInstance();
		launcher  = new Talon(4);

		Drive = new SixWheelDrive (constants);
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		/*Drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		Drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);*/
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		Drive->arcadeDrive(Drivestick->GetY(), Drivestick->GetX());
		//midRight->Set(rightFront->Get());

		//right trigger 7
		if (Drivestick->GetRawButton(constants->Get("shooterButton"))==true){
			//when button is pressed, motor moves. -Sep
			launcher -> Set(1);
		}else{
			//Stops the motor when button not pressed -Sep
			launcher->Set(0);
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
