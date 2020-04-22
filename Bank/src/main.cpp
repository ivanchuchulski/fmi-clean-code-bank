/*
	-oop hw3 bank
	-compiled with : Visual C++ with std:c++17

*/

#include <iostream>
#include <string>
#include <array>

#include "Customers/Customer.h"
#include "Accounts/CurrentAccount.h"
#include "Accounts/SavingsAccount.h"
#include "Accounts/PrivilegeAccount.h"
#include "Bank/Bank.h"
#include "Menu/Menu.h"


void IgnoreWhitespaces()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string InputString()
{
	std::string str;

	//std::cin.clear();
	//std::cin.sync();
	std::getline(std::cin, str);

	return str;
}

int main() 
{
	bool stop = false;
	int command;
	std::vector<int> commandList = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Menu bankMenu(commandList);
	Bank* bank = new Bank("Bright finances", "Sofia");

	do 
	{
		//bankMenu.ShowMenu();
		command = bankMenu.GetCommand();
		IgnoreWhitespaces();

		switch (command)
		{
			// list customers
			case 1 :
			{
				bank->ListCustomers();
				break;
			}

			// add customer
			case 2 :
			{
				std::string	customerName;
				std::string	customerAddress;

				std::cout << "enter customer name : ";
				customerName = InputString();

				std::cout << "enter customer address : ";
				customerAddress = InputString();

				bank->AddCustomer(customerName, customerAddress);
				break;
			}

			// delete customer
			case 3 :
			{
				std::string customerIDToDelete;
				
				std::cout << "Enter a customerID to delete : ";
				customerIDToDelete = InputString();

				bank->DeleteCustomer(customerIDToDelete);
				break;
			}

			// list all accounts
			case 4 :
			{
				bank->ListAccounts();
				break;
			}

			// list all customer's accounts
			case 5 :
			{
				std::string customerID;

				std::cout << "enter customerID to view all of it's accounts : ";
				customerID = InputString();

				bank->ListCustomerAccount(customerID);
				break;
			}

			// add new account
			case 6 :
			{
				int accountType = 0;
				std::string customerID;

				bank->PrintSupportedAccountTypes();

				std::cout << "enter a account type : ";
				std::cin >> accountType;

				IgnoreWhitespaces();

				std::cout << "enter existing customerID for the new account : ";
				customerID = InputString();

				bank->AddAccount(customerID, static_cast<AccountType>(accountType));
				break;
			}

			// delete account
			case 7 :
			{
				std::string ibanToDelete;

				std::cout <<  "enter account IBAN to delete : ";
				ibanToDelete = InputString();

				bank->DeleteAccount(ibanToDelete);
				break;
			}

			// withdraw from account
			case 8 :
			{
				int ammountToWithdraw = 0;
				std::string ibanToWithdrawFrom;

				std::cout << "enter amount to withdraw from the account : ";
				std::cin >> ammountToWithdraw;
				
				IgnoreWhitespaces();

				std::cout << "enter account IBAN to withdraw from : ";
				ibanToWithdrawFrom = InputString();

				bank->WithdrawFromAccount(ibanToWithdrawFrom, ammountToWithdraw);
				break;
			}

			// deposit to account
			case 9 :
			{
				int depositAmmount = 0;
				std::string sourceIBAN;

				std::cout << "enter amount to deposit to the account : ";
				std::cin >> depositAmmount;

				IgnoreWhitespaces();

				std::cout << "enter account iban to deposit to : ";
				sourceIBAN = InputString();

				bank->DepositToAccount(sourceIBAN, depositAmmount);
				break;
			}

			// trasfer
			case 10 :
			{
				int transferAmmount = 0;
				std::string sourceIBAN;
				std::string destinationIBAN;

				std::cout << "enter amount to transfer : ";
				std::cin >> transferAmmount;

				IgnoreWhitespaces();

				std::cout << "enter account iban to withdraw from : ";
				sourceIBAN = InputString();

				std::cout << "enter account iban to deposit to : ";
				destinationIBAN = InputString();

				bank->Transfer(sourceIBAN, destinationIBAN, transferAmmount);
				break;
			}

			// display bank info
			case 11 :
			{
				bank->DisplayBank();
				break;
			}

			// quit the menu
			case 12 :
			{
				stop = true;
				break;
			}

			// show menu again
			case 13 :
			{
				bankMenu.ShowMenu();
				break;
			}
		}
	} while (!stop);

	std::cout << "exiting...\n";

	Bank* someOtherBank = new Bank(*bank);

	someOtherBank->DisplayBank();

	// free dynamic memory
	delete bank;
	delete someOtherBank;

	/*tests*/
/*
{
	std::array<std::string, 5> IDs_test = { "#012","#123", "#234", "#345", "#456" };
	std::array<std::string, 6> Names_test = { "Kolyo" ,"Dragan", "Petkan", "Vladimir", "Darina", "Anton" };
	std::array<std::string, 6> Addresses_test = { "Sofia", "Varna", "Plovdiv", "New York", "London", "Moscow" };
	std::array<std::string, 5> Ibans_test = { "BG_01_23", "BG_12_34","BG_45_43", "EN_01_23", "RU_56_78" };


	Customer c1 = Customer(IDs_test[0], Names_test[0], Addresses_test[0]);

	CurrentAccount a1(500, IDs_test[0], Ibans_test[0]);

	SavingsAccount s1(1000, IDs_test[1], Ibans_test[1], 5.5f);

	PrivilegeAccount pr1(2500, IDs_test[2], Ibans_test[2], 500);

	std::cout << a1 << std::endl;
	a1.DisplayAccount();

	std::cout << s1 << std::endl;
	s1.DisplayAccount();

	std::cout << pr1 << std::endl;
	pr1.DisplayAccount();

	Bank KTB_bank("KTB", "Sofia", 10);

	KTB_bank.AddCustomer(c1.GetID(), c1.GetName(), c1.GetAddress());
	KTB_bank.AddAccount(acc::AccountTypes::ACurrentAccount, a1.GetBalance(), a1.GetOwnerID(), a1.GetIban());

	KTB_bank.ListAccounts();

	KTB_bank.ListCustomers();

	KTB_bank.DisplayBank();
}
*/

	return 0;
}