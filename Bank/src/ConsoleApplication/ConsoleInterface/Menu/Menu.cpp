#include "Menu.h"

#include <iostream>
#include <cstring>
#include <algorithm>

Menu::Menu()
	: legalOptions()
{
	initializeOptions();
}


void Menu::ShowMenu()
{
	std::cout << "\n###### Bank menu ######\n";
	for (auto& option : legalOptions) 
	{
		std::cout << option.first << " - " << option.second << "\n";
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

// private methods
void Menu::initializeOptions()
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




