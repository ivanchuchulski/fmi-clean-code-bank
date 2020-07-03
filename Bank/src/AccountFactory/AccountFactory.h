#pragma once

#include "Account/Account.h"
#include "Accounts/CurrentAccount.h"
#include "Accounts/PrivilegeAccount.h"
#include "Accounts/SavingsAccount.h"

class AccountFactory
{
public:
	AccountFactory()
	{}

	~AccountFactory()
	{}

	static Account* CreateAccount(AccountType accountType, std::string& ownerID);
};
