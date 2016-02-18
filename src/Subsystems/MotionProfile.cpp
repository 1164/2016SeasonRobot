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
	a = 0;
	b = 0;
	c = 0;

	t3 = Amax/Vmax;
	t1 = (Vmax-V0)/Amax;

	a = Amax/2;

	/*GetX(double t);
	if (t<= t1){
		Xa(t);
	}

	if (t1<t<=t2){
		Xb(t-t1)+Xa(t1);
	}

	if (t2<t<=t3){
		Xc(t-t1-t2)+Xa(t1)+Xb(t2);
	}

	if (t>t3){
		distance;
	}

*/
}
