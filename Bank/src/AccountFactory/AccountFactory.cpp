#include "AccountFactory/AccountFactory.h"

Account* AccountFactory::CreateAccount(AccountType accountType, std::string& ownerID)
{
	switch (accountType)
	{
	case AccountType::CurrentAccount:
		return new CurrentAccount(ownerID);
		break;

	case AccountType::SavingsAccount:
		return new SavingsAccount(ownerID);
		break;
	case AccountType::PrivileAccount:
		return new PrivilegeAccount(ownerID);
		break;

	default:
		throw std::exception("account addition failed : invalid account type\n");
		break;
	}

}