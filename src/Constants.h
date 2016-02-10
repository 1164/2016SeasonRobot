/*
 * Constants.h
 *
 *  Created on: Feb 3, 2016
 *      Author: neoadmin
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_
#include <string>
#include <unordered_map>
using namespace std;

class Constants {
private:
	unordered_map<string,double> map;
public:
	Constants();
	void reloadFile();

	double Get(string constantName);
};

#endif /* SRC_CONSTANTS_H_ */
