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

	std::string InputString();
	AccountType InputAccountType();
	double InputMoneyAmmount();

	void PrintSupportedAccountTypes();
	void PrintCustomerDetails(const Customer& customer) const;
	void PrintAccountDetails(const Account* const account) const;
	
	void DisplayMessage(const std::string messege);
	void DisplayErrorMessage(const std::string errorMessege);

private:
	void IgnoreWhitespaces();
	int GetIntegerFromString(std::string& str);
	double GetDoubleFromString(std::string& str);

private:
	Menu menu;

};
