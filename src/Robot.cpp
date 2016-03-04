#include "WPILib.h"
#include <iostream>
#include <Joystick.h>
#include <TalonSRX.h>
#include <Talon.h>
#include <VictorSP.h>
#include <Speedcontroller.h>
#include <Constants.h>
#include <Subsystems/SixWheelDrive.h>
#include "Subsystems/ShooterIntake.h"
#include <Solenoid.h>
#include <Timer.h>
#include "AHRS.h"

class Robot: public IterativeRobot
{

public:
	//Timer for motion profiler
	//Timer *Time;
	//double CurrentTime=0;

private:
	LiveWindow *lw = LiveWindow::GetInstance();
	Joystick *Drivestick;
	Joystick *Operatorstick;
	Constants *constants;

	VictorSP *RollerMotor;
	VictorSP *shooterMotor1;
	VictorSP *shooterMotor2;
	SixWheelDrive *Drive;
	ShooterIntake *ShootIntake;

	// Variables for Ian's implementation of dumb shooter.
	Timer *timer;
	bool lastShooterButton;
	bool shoot;
	//Timer for motion profiler
	//Timer *Time;
	//double CurrentTime=0;

	SendableChooser *chooser;
	Solenoid *solenoid;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;


	void RobotInit()
	{
		// Ian's dumb shooter init
		lastShooterButton = false;
		shoot = false;
		timer = new Timer();
		timer->Reset();

		constants = new Constants();
		Drivestick = new Joystick(0);
		Operatorstick = new Joystick(1);
		lw = LiveWindow::GetInstance();
		solenoid = new Solenoid(5);

		Drive = new SixWheelDrive (constants);
		ShootIntake = new ShooterIntake (constants);

		RollerMotor = new VictorSP(constants->Get("RollerMotor"));

		shooterMotor1 = new VictorSP(constants->Get("shooterMotor1"));
		shooterMotor2 = new VictorSP(constants->Get("shooterMotor2"));

		shooterMotor1->SetInverted(constants->Get("shooterMotor1Invert") == 1);
		shooterMotor2->SetInverted(constants->Get("shooterMotor2Invert") == 1);

		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		//Timer for the motion profiler
		//double CurrentTime=0;
		//double Time;
		//Timer Time;


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
		Drive->arcadeDrive(Drivestick->GetAxis((Joystick::AxisType)constants->Get("DriveAxisY")),
				Drivestick->GetAxis((Joystick::AxisType)constants->Get("DriveAxisX")),
				Drivestick->GetRawButton(constants->Get("HighShiftButton")),
				Drivestick->GetRawButton(constants->Get("LowShiftButton")));
		//midRight->Set(rightFront->Get());

		RollerMotor->Set(Operatorstick->GetAxis((Joystick::AxisType)constants->Get("RollerMotorY")), 0);

	//	Operatorstick->GetAxis((Joystick::AxisType)constants->Get("RollerAControl")) && RollerArm::RollerControl;



	}

	void TestPeriodic()
	{
		lw->Run();
	}

};

START_ROBOT_CLASS(Robot)
