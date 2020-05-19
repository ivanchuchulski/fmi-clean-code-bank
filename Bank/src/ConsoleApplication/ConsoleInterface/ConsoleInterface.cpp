#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface()
	:	menu()
{}


void ConsoleInterface::DisplayMenu()
{
	menu.ShowMenu();
}

OptionCode ConsoleInterface::GetOption()
{
	do
	{
		int command;

		std::cin >> command;

		if (menu.IsValidOption(command)) {
			return static_cast<OptionCode>(command);
		}

	} while (true);
}

Customer ConsoleInterface::InputCustomerDetails()
{
	std::string	customerName;
	std::string	customerAddress;

	IgnoreWhitespaces();

	std::cout << "enter customer name : ";
	customerName = InputString();

	std::cout << "enter customer address : ";
	customerAddress = InputString();

	return Customer(customerName, customerAddress);
}

// private methods
void ConsoleInterface::IgnoreWhitespaces()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string ConsoleInterface::InputString()
{
	std::string str;

	//std::cin.clear();
	//std::cin.sync();
	std::getline(std::cin, str);

	return str;
}
