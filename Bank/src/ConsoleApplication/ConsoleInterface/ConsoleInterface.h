#pragma once

#include "Menu/Menu.h"
#include "OptionCode/OptionCode.h"
#include "Customers/Customer.h"
#include "Account/Account.h"
#include "Accounts/CurrentAccount/CurrentAccount.h"
#include "Accounts/PriviligeAccount/PrivilegeAccount.h"
#include "Accounts/SavingsAccount/SavingsAccount.h"

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

private:
	void IgnoreWhitespaces();
	std::string InputString();
	int GetIntegerFromString(std::string& str);
	double GetDoubleFromString(std::string& str);

private:
	Menu menu;

};
