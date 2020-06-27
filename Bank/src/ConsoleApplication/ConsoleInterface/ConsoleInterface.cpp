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


std::string ConsoleInterface::InputCustomerID()
{
	std::string	customerID;

	IgnoreWhitespaces();

	std::cout << "enter customer id : ";
	customerID = InputString();

	return customerID;
}

std::string ConsoleInterface::InputCustomerName()
{
	std::string	custmerName;

	IgnoreWhitespaces();

	std::cout << "enter customer name : ";
	custmerName = InputString();

	return custmerName;
}

std::string ConsoleInterface::InputCustomerAddress()
{
	std::string	customerAddress;

	IgnoreWhitespaces();

	std::cout << "enter customer address : ";
	customerAddress = InputString();

	return customerAddress;
}

AccountType ConsoleInterface::InputAccountType()
{
	int accountTypeAsInt;

	IgnoreWhitespaces();

	std::cout << "enter account type : ";
	std::cin >> accountTypeAsInt;

	return static_cast<AccountType>(accountTypeAsInt);
}

std::string ConsoleInterface::InputAccountIBAN()
{
	return std::string();
}

double ConsoleInterface::InputMoneyAmmount()
{
	return 0.0;
}

void ConsoleInterface::PrintException(const std::exception& exception)
{
	std::cerr << "error from console interface\n";
	std::cerr << exception.what();
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
