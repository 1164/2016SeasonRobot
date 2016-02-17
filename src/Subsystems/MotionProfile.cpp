/*
 * MotionProfile.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: neoadmin
 */

#include <Subsystems/MotionProfile.h>
#include <iostream>


MotionProfile::MotionProfile(double AMax, double VMax) {
	// TODO Auto-generated constructor stub
	Amax = AMax;
	Vmax = VMax;
	t1 = 0;
	t2 = 0;
	t3 = 0;
	V0 = 0;

}
