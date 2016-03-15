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
#include "Subsystems/Shooter.h"
#include <Solenoid.h>
#include <Timer.h>
#include "AHRS.h"
#include <Encoder.h>

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
	SixWheelDrive *Drive;
	//ShooterIntake *ShootIntake;


	Shooter *shooter;

	SendableChooser *chooser;
	Solenoid *solenoid;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	Encoder *RollerEncoder;


	void RobotInit()
	{
		constants = new Constants();
		shooter = new Shooter(constants);
		Drivestick = new Joystick(0);
		Operatorstick = new Joystick(1);
		lw = LiveWindow::GetInstance();
		solenoid = new Solenoid(5);

		Drive = new SixWheelDrive (constants);
		//ShootIntake = new ShooterIntake (constants);

		RollerMotor = new VictorSP(constants->Get("RollerMotor"));

		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		//Timer for the motion profiler
		//double CurrentTime=0;
		//double Time;
		//Timer Time;
		RollerEncoder = new Encoder(constants->Get("RollerEncoderArmA"), constants->Get("RollerEncoderArmB"));

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

		RollerMotor->Set(Operatorstick->GetAxis((Joystick::AxisType)constants->Get("RollerMotorY")) * .5, 0);
		if (Operatorstick->GetRawButton(constants->Get("shooterButton"))){
			shooter->Fire();
			DriverStation::GetInstance().ReportError("FIRE!!!!!!RUN!!!!");
		}
		else{
			shooter->Stop();
		}

	//	Operatorstick->GetAxis((Joystick::AxisType)constants->Get("RollerAControl")) && RollerArm::RollerControl;

		//ShooterMoving

			//Shooter::shooterMotor1->Set(Operatorstick->GetAxis((Joystick::AxisType)1)/4.0);
			//Shooter::shooterMotor2->Set(Operatorstick->GetAxis((Joystick::AxisType)1)/4.0);

	}

	void DisabledPeriodic()
	{
		char *Rollerencoder = new char[255];
		char *Breakbeamy = new char[255];
		char *stringy = new char[255];

		sprintf(stringy, "ShooterEnc: %d\n", (int)shooter->ReadEncoder());
		DriverStation::GetInstance().ReportError(stringy);
		sprintf(Breakbeamy, "ShooterIndex: %d\n", 2);
		DriverStation::GetInstance().ReportError(Breakbeamy);
		sprintf(Rollerencoder, "rollerEncoder: %d\n", RollerEncoder->Get());
		DriverStation::GetInstance().ReportError(Rollerencoder);

		if(Drivestick->GetRawButton(11) || Drivestick->GetRawButton(12)){
			DriverStation::GetInstance().ReportError("Button Press Registered");
		}

		//experimental code -sep
		//to see if shooter is in reset position
		/*

		 if(shooterIndex->Get()){
			if(ShooterReset){
				ShooterReset = false;
			} else {
				ShooterReset = true;
			}
		}
	*/
	}

	void TestPeriodic()
	{
		lw->Run();
	}

};

START_ROBOT_CLASS(Robot)
