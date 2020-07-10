#pragma once

#include "Account/Account.h"
#include "Accounts/CurrentAccount/CurrentAccount.h"
#include "Accounts/PriviligeAccount/PrivilegeAccount.h"
#include "Accounts/SavingsAccount/SavingsAccount.h"

class AccountFactory
{
public:
	AccountFactory()
	{}

	~AccountFactory()
	{}

	static Account* CreateAccount(AccountType accountType, std::string& ownerID);
};
