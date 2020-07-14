#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <map>

#include "ConsoleApplication/ConsoleInterface/OptionCode/OptionCode.h"

class Menu
{
public:
	Menu();
	~Menu() = default;

	void ShowMenu();
	bool IsValidOption(int command);

private:
	void initializeOptions();

private:
	std::map<int, std::string> legalOptions;
};


#endif // !MENU_H






