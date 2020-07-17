#include "AccountList/AccountList.h"
#include <exception>


AccountList::AccountList(const AccountList& other)
	: accounts()
{
	CopyAccounts(other.accounts);
}

AccountList::~AccountList()
{
	ClearAccounts();
}

AccountList& AccountList::operator=(const AccountList& other)
{
	if (this != &other)
	{
		ClearAccounts();
		CopyAccounts(other.accounts);
	}

	return *this;
}

void AccountList::AddAccount(Account* account)
{
	accounts.emplace_back(account);
}

void AccountList::DeleteAccount(const std::string& IBAN)
{
	account_iterator accountPosition = GetAccountPosition(IBAN);

	if (accountPosition == end())
	{
		throw std::exception("error : account doesn't exist\n");
	}

	auto accountIndexInVector = accountPosition - accounts.begin();

	delete accounts[accountIndexInVector];

	accounts.erase(accountPosition);
}

void AccountList::DeleteAllCustomersAccounts(const std::string& customerName)
{
	for (size_t i = 0; i < accounts.size(); i++)
	{
		if (accounts[i]->AccountOwnedByCustomer(customerName))
		{
			delete accounts[i];

			accounts.erase(accounts.begin() + i);
		}
	}
}

void AccountList::Clear()
{
	ClearAccounts();
}

bool AccountList::Empty() const
{
	return accounts.empty();
}

Account* AccountList::GetAccount(const std::string& IBAN)
{
	account_iterator accountPosition = GetAccountPosition(IBAN);

	if (accountPosition == end())
	{
		throw std::exception("error : such account is not opened\n");
	}

	return *accountPosition;
}

const Account* AccountList::GetAccount(const std::string& IBAN) const
{
	account_const_iterator accountPosition = GetAccountPosition(IBAN);

	if (accountPosition == end())
	{
		throw std::exception("error : such account is not opened\n");
	}

	return *accountPosition;
}

account_iterator AccountList::begin()
{
	return accounts.begin();
}

account_iterator AccountList::end()
{
	return accounts.end();
}

account_const_iterator AccountList::begin() const
{
	return accounts.begin();
}

account_const_iterator AccountList::end() const
{
	return accounts.end();
}

// private helpers
void AccountList::ClearAccounts()
{
	// deleting the data pointed by the pointers 
	// using a pointer reference to be able to do the assignment to nullptr correctly(maybe unnecessary)
	for (Account*& account : accounts)
	{
		delete account;
		account = nullptr;
	}

	// clearing the pointers that the vector holds
	accounts.clear();
}

void AccountList::CopyAccounts(const std::vector<Account*>& otherAccounts)
{
	for (const Account* account : otherAccounts)
	{
		accounts.emplace_back(account->CloneAccount());
	}
}

account_iterator AccountList::GetAccountPosition(const std::string& IBAN)
{
	return std::find_if(begin(), end(), [&](const Account* account) { return account->GetAccountIBAN() == IBAN; });
}

account_const_iterator AccountList::GetAccountPosition(const std::string& IBAN) const
{
	return std::find_if(begin(), end(), [&](const Account* account) { return account->GetAccountIBAN() == IBAN; });
}