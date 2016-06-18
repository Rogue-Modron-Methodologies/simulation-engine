#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <Box2D\Box2D.h>
#include "ConsoleColor.h"

class Menu {
private:
	double param1;
	double param2;
	std::string stringInput;

public:
	double getParam1() { return param1; }
	double getParam2() { return param2; }
	std::string getString() { return stringInput; }

protected:
	virtual int displayMenu(std::vector<std::string> prompts) = 0;
	void setParam1(double p1) { param1 = p1; }
	void setParam2(double p2) { param2 = p2; }	
	void setString(std::string in) { stringInput = in; }
};
#endif // MENU_H
