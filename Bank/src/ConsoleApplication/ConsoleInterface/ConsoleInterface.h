#pragma once

#include "Menu/Menu.h"
#include "Menu/OptionCode/OptionCode.h"
#include "Customers/Customer.h"
#include "Account/Account.h"
#include "Accounts/CurrentAccount.h"
#include "Accounts/PrivilegeAccount.h"
#include "Accounts/SavingsAccount.h"

class ConsoleInterface
{
public:
	ConsoleInterface();
	~ConsoleInterface() = default;

	void DisplayMenu();
	OptionCode GetOption();

	std::string InputCustomerID();
	std::string InputCustomerName();
	std::string InputCustomerAddress();

	AccountType InputAccountType();
	std::string InputAccountIBAN();
	double InputMoneyAmmount();

	void PrintSupportedAccountTypes();
	
	void DisplaySuccessMessege(const std::string messege);
	void DisplayErrorMessege(const std::string messege);

	void PrintException(const std::exception& exception);

private:
	void IgnoreWhitespaces();
	std::string InputString();
	bool IsStringInteger(std::string& str);

private:
	Menu menu;

};
