/*
 * Constants.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: neoadmin
 */

#include <Constants.h>
#include <fstream>

Constants::Constants() {
	// TODO Auto-generated constructor stub
	reloadFile();
}


void Constants::reloadFile(){
	ifstream myfile("trialAndError.neo");
	if (myfile.is_open())
	{
		string line;
		double value;
		while(myfile.eof()){
			myfile >> line >> value;
			map.insert (pair<string, double> (line, value));

		}
	}
}

double Constants::Get(string constantName){
	return map.at (constantName);
}
