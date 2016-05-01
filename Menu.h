#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <iomanip>
#include <Box2D\Box2D.h>

class Menu
{
	double param1;
	double param2;

public:
	int MainMenu() 	{
		std::cout << "Simulation Options\n";
		std::cout << "1) Run with current options. \n";
		std::cout << "2) View current options. \n";
		std::cout << "3) Change current options. \n";
		std::cout << "4) Randomize Options. \n";
		std::cout << "5) Exit.\n";
		return getValidInput(1, 5);
	}

	int currentOptionMenu() {
		std::cout << "Options Menu\n";
		std::cout << "1) Gravity Options\n";
		//std::cout << "2) \n";
		//std::cout << "3) \n";
		//std::cout << "4) \n";
		//std::cout << "5) \n";
		//std::cout << "6) \n";
		//std::cout << "7) \n";
		//std::cout << "8) \n";
		std::cout << "2) Exit with no changes. \n";
		return getValidInput(1, 2);	
	}

	// get a pair of valid parameters
	template <class T>
	void setParams(T low, T high, std::string prompt = "") {
		if (prompt.length() > 0) std::cout << prompt << std::endl;
		param1 = getValidInput(low, high);
		param2 = getValidInput(low, high);
	}

	double getParam1() { return param1; }

	double getParam2() { return param2; }

private:
	// Validate Input
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

		return temp;
	}
};
#endif // MENU_H
