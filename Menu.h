#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <Box2D\Box2D.h>
#include "ConsoleColor.h"

class Menu
{
	double param1;
	double param2;

public:
	int displayMenu(std::vector<std::string> prompts) 	{	
		unsigned int i = 0;
		for ( ; i < prompts.size(); ++i)
			std::cout << i + 1 << ") "<< prompts[i] << std::endl;
		std::cout << i + 1 << ") Exit\n";
		return getValidInput(1, (int)prompts.size() + 1);
	}
	double getParam1() { return param1; }
	double getParam2() { return param2; }
	template <class T>	// get a pair of valid parameters
	void setParams(T low, T high, std::string prompt = "") {
		if (prompt.length() > 0) 
			std::cout << prompt << std::endl;
		param1 = getValidInput(low, high);
		if (prompt.length() > 0) 
			std::cout << prompt << std::endl;
		param2 = getValidInput(low, high);
	}

private:
	void clearScreen() {	
		std::cout << "\x1B[2J\x1B[H";  // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	}
	template <class T>
	T getValidInput(T low, T high)
	{
		T temp;
		bool validInput = true;
		do {
			std::cin >> temp;
			if (std::cin.fail() || temp < low || temp > high)
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout  << "\nMust be between " << low << " and " << high << ". Please try again.\n";
				validInput = false;
			}
			else
				validInput = true;
		} while (!validInput);
		clearScreen();
		return temp;
	}
};
#endif // MENU_H
