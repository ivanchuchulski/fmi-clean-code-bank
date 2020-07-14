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
	try
	{
		std::string line;
		int command;

		std::cout << "choose your command : ";
		line = InputString();
		
		command = GetIntegerFromString(line);

		if (!menu.IsValidOption(command))
		{
			throw std::exception("error : your command is not a valid option\n");
		}

		return static_cast<OptionCode>(command);
	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

std::string ConsoleInterface::InputCustomerID()
{
	std::cout << "enter customer id : ";

	return InputString();
}

std::string ConsoleInterface::InputCustomerName()
{
	std::cout << "enter customer name : ";

	return InputString();
}

std::string ConsoleInterface::InputCustomerAddress()
{
	std::cout << "enter customer address : ";

	return InputString();
}

AccountType ConsoleInterface::InputAccountType()
{
	std::string inputLine;
	int accountTypeAsInt;

	std::cout << "enter account type : ";

	inputLine = InputString();

	accountTypeAsInt = GetIntegerFromString(inputLine);

	return static_cast<AccountType>(accountTypeAsInt);
}

std::string ConsoleInterface::InputAccountIBAN()
{
	std::cout << "enter account IBAN : ";

	return InputString();
}

double ConsoleInterface::InputMoneyAmmount()
{
	std::string inputLine;
	double moneyAmmount;

	std::cout << "enter money ammount: ";

	inputLine = InputString();

	moneyAmmount = GetDoubleFromString(inputLine);

	return moneyAmmount;
}

void ConsoleInterface::PrintSupportedAccountTypes()
{
	std::cout << "Supported account types : \n";
	std::cout << "Current Account : " << static_cast<int>(AccountType::CurrentAccount) << '\n';
	std::cout << "Savings Account : " << static_cast<int>(AccountType::SavingsAccount) << '\n';
	std::cout << "Privilige Account : " << static_cast<int>(AccountType::PrivileAccount) << '\n';
}

void ConsoleInterface::PrintCustomerDetails(const Customer& customer) const
{
	std::cout << customer;
}

void ConsoleInterface::PrintAccountDetails(const Account* const account) const
{
	account->DisplayAccount(std::cout);
}

void ConsoleInterface::DisplaySuccessMessege(const std::string messege)
{
	std::cout << messege;
}

void ConsoleInterface::DisplayErrorMessege(const std::string messege)
{
	std::cerr << messege;
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

int ConsoleInterface::GetIntegerFromString(std::string& str)
{
	const char* pointer = str.c_str();
	char* end;

	int stringConvertedToInteger = std::strtol(pointer, &end, 10);
	
	if (*end)
	{
		throw std::exception("error : input must be integer\n");
	}

	return stringConvertedToInteger;
}

double ConsoleInterface::GetDoubleFromString(std::string& str)
{
	const char* pointer = str.c_str();
	char* end;

	double stringConvertedToDouble = std::strtod(pointer, &end);

	if (*end)
	{
		throw std::exception("error : input must be floating point number");
	}

	return stringConvertedToDouble;
}
