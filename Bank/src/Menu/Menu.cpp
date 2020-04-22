#include "Menu.h"

#include <iostream>
#include <cstring>
#include <algorithm>

Menu::Menu(std::vector<int> legalCommands)
	: m_legalCommands(legalCommands)
{
	std::sort(m_legalCommands.begin(), m_legalCommands.end());
}


void Menu::ShowMenu() const
{
	std::cout << "\n\t\t###### Bank menu ######\n"
				<< "\t 1 - List customers\n"
				<< "\t 2 - Add new customer\n"
				<< "\t 3 - Delete customer\n"
				<< "\t 4 - List all accounts\n"
				<< "\t 5 - List all customer's accounts\n"
				<< "\t 6 - Add new account\n"
				<< "\t 7 - Delete an account\n"
				<< "\t 8 - Withdraw from an account\n"
				<< "\t 9 - Deposit to an account\n"
				<< "\t 10 - Transfer money from one account to another\n"
				<< "\t 11 - Display information about the bank\n"
				<< "\t 12 - Quit\n"
				<< "\t 13 - Show the menu\n";
}

int Menu::GetCommand() const
{
	int lowerBound = m_legalCommands.front();
	int upperBound = m_legalCommands.back();

	return SafetyInputIntegerInBounds(lowerBound, upperBound);
}


// private helper
int Menu::SafetyInputIntegerInBounds(const int lowerBound, const int upperBound) const
{
	int input;

	do
	{
		ShowMenu();

		std::cout << "\t your input : ";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cout << "error : invalid command, please try again\n";

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (input < lowerBound || input > upperBound);

	return input;
}







