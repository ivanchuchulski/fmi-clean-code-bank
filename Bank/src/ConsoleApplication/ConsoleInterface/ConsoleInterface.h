#pragma once

#include "Menu/Menu.h"
#include "Menu/OptionCode/OptionCode.h"
#include "Customers/Customer.h"

class ConsoleInterface
{
public:
	ConsoleInterface();
	~ConsoleInterface() = default;

	void DisplayMenu();
	OptionCode GetOption();

	Customer InputCustomerDetails();
	std::string InputCustomerID();

	int InputAccountType();
	std::string InputAccountIBAN();
	double InputMoneyAmmount();

private:
	void IgnoreWhitespaces();
	std::string InputString();

private:
	Menu menu;

};
