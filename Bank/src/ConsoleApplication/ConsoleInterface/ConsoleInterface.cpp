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
		std::string line;

		std::cout << "\tyour choice : ";
		line = InputString();

		char* end;
		int command = std::strtol(line.c_str(), &end, 10);

		if (*end)
		{
			DisplayErrorMessege("error : wrong command, commands must be integers, please try again\n");
			continue;
		}

		if (menu.IsValidOption(command))
		{
			return static_cast<OptionCode>(command);
		}
		else
		{
			DisplayErrorMessege("error : command out of range, please try again\n");
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

void ConsoleInterface::PrintSupportedAccountTypes()
{
	std::cout << "Supported account types : \n";
	std::cout << "Current Account : " << static_cast<int>(AccountType::CurrentAccount) << '\n';
	std::cout << "Privilige Account : " << static_cast<int>(AccountType::PrivileAccount) << '\n';
	std::cout << "Savings Account : " << static_cast<int>(AccountType::SavingsAccount) << '\n';
}

void ConsoleInterface::DisplaySuccessMessege(const std::string messege)
{
	std::cout << messege;
}

void ConsoleInterface::DisplayErrorMessege(const std::string messege)
{
	std::cerr << messege;
}

void ConsoleInterface::PrintException(const std::exception& exception)
{
	std::cerr << "error from console interface\n";
	std::cerr << exception.what();
}

// private methods
void ConsoleInterface::IgnoreWhitespaces()
{
	//std::cin.clear();
	//std::cin.sync();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string ConsoleInterface::InputString()
{
	std::string str;

	std::getline(std::cin, str);

	return str;
}

bool ConsoleInterface::IsStringInteger(std::string& str)
{
	const char* pointer = str.c_str();
	char* end;

	int converted = std::strtol(pointer, &end, 10);
	
	if (*end)
	{
		return false;
	}
	else
	{
		return true;
	}
}
