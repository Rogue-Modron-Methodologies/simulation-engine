#ifndef CONSULEMENU_H
#define CONSOLEMENU_H

#include <iostream>
#include <iomanip>
#include "ConsoleColor.h"
#include "Menu.h"

class ConsoleMenu : public Menu {

public:
	int displayMenu(std::vector<std::string> prompts) {
		unsigned int i = 0;
		for (; i < prompts.size(); ++i)
			std::cout << i + 1 << ") " << prompts[i] << std::endl;
		std::cout << i + 1 << ") Exit\n";
		return getValidInput(1, (int)prompts.size() + 1);
	}


	template <class T>	// get a pair of valid parameters
	void setParams(T low, T high, std::string prompt = "") {
		cin.ignore();
		if (prompt.length() > 0)
			std::cout << prompt << std::endl;
		setParam1(getValidInput(low, high));
		if (prompt.length() > 0)
			std::cout << prompt << std::endl;
		setParam2(getValidInput(low, high));
	}

	void setStringInput(std::string prompt = "") {
		cin.ignore();
		std::string temp;
		if (prompt.length() > 0)
			std::cout << prompt << std::endl;
		std::getline(std::cin, temp);
		setString(temp);
		clearScreen();
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
				std::cout << "\nMust be between " << low << " and " << high << ". Please try again.\n";
				validInput = false;
			}
			else
				validInput = true;
		} while (!validInput);
		clearScreen();
		return temp;
	}
};
#endif CONSOLEMENU_H
