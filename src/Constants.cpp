/*
 * Constants.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: neoadmin
 */

#include <Constants.h>
#include <fstream>
#include <DriverStation.h>

Constants::Constants() {
	// TODO Auto-generated constructor stub
	reloadFile();
}


void Constants::reloadFile(){
	ifstream myfile("/home/lvuser/trialAndError.neo");
	if (myfile.is_open())
	{
		string line;
		double value;
		while(!myfile.eof()){
			myfile >> line >> value;
			map.insert (pair<string, double> (line, value));

		}
	}
	myfile.close();
}

double Constants::Get(string constantName){
	if (map.count(constantName)<=0){
		DriverStation::GetInstance().ReportError("Cannot find constantName "+constantName + "\n");
		return -1;
	}

	return map.at (constantName);
}
