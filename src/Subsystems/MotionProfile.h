/*
 * MotionProfile.h
 *
 *  Created on: Feb 16, 2016
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_MOTIONPROFILE_H_
#define SRC_SUBSYSTEMS_MOTIONPROFILE_H_

class MotionProfile {
public:
	MotionProfile(double AMax, double VMax);

private:
	double Amax;
	double Vmax;
	double t3;
	double t2;
	double t1;
	double V0;
	double a;
	double b;
	double c;
};

#endif /* SRC_SUBSYSTEMS_MOTIONPROFILE_H_ */
