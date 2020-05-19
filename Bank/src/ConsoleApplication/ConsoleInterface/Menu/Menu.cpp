#include "Menu.h"

#include <iostream>
#include <cstring>
#include <algorithm>

Menu::Menu()
	: legalOptions()
{
	initOptions();
}


void Menu::ShowMenu()
{
	//std::cout << "\n\t\t###### Bank menu ######\n"
	//	<< "\t 1 - List customers\n"
	//	<< "\t 2 - Add new customer\n"
	//	<< "\t 3 - Delete customer\n"
	//	<< "\t 4 - List all accounts\n"
	//	<< "\t 5 - List all customer's accounts\n"
	//	<< "\t 6 - Add new account\n"
	//	<< "\t 7 - Delete an account\n"
	//	<< "\t 8 - Withdraw from an account\n"
	//	<< "\t 9 - Deposit to an account\n"
	//	<< "\t 10 - Transfer money from one account to another\n"
	//	<< "\t 11 - Display information about the bank\n"
	//	<< "\t 12 - Quit\n"
	//	<< "\t 13 - Show the menu\n";

	std::cout << "\n\t\t###### Bank menu ######\n";
	for (auto& option : legalOptions) 
	{
		std::cout << "\t" << option.first << " - " << option.second << "\n";
	}
}

bool Menu::IsValidOption(int command)
{
	for (auto& option : legalOptions)
	{
		if(option.first == command) 
		{
			return true;
		}
	}

	return false;
}

// private
void Menu::initOptions()
{
	legalOptions.insert({ static_cast<int>(OptionCode::AddCustomer), "Add customer" });
	legalOptions.insert({ static_cast<int>(OptionCode::DeleteCustomer), "Delete customer" });
	legalOptions.insert({ static_cast<int>(OptionCode::AddAccount), "Add account" });
	legalOptions.insert({ static_cast<int>(OptionCode::DeleteAccount), "Delete account" });

	legalOptions.insert({ static_cast<int>(OptionCode::ListCustomers), "List customers" });
	legalOptions.insert({ static_cast<int>(OptionCode::ListAllCustomersAccount), "List All Customers Account" });
	legalOptions.insert({ static_cast<int>(OptionCode::ListAccounts), "List accounts" });
	legalOptions.insert({ static_cast<int>(OptionCode::BankInformation), "Bank Information" });

	legalOptions.insert({ static_cast<int>(OptionCode::Withdraw), "Withdraw from account" });
	legalOptions.insert({ static_cast<int>(OptionCode::Deposit), "Deposit to account" });
	legalOptions.insert({ static_cast<int>(OptionCode::Transfer), "Transfer between accounts" });

	legalOptions.insert({ static_cast<int>(OptionCode::Help), "Display help" });
	legalOptions.insert({ static_cast<int>(OptionCode::Quit), "Quit" });
}




