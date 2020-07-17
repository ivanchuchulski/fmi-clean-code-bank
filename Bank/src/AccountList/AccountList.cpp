#include "AccountList/AccountList.h"
#include <exception>


AccountList::AccountList(const AccountList& other)
	: m_accounts()
{
	CopyAccounts(other.m_accounts);
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
		CopyAccounts(other.m_accounts);
	}

	return *this;
}

void AccountList::AddAccount(Account* account)
{
	m_accounts.emplace_back(account);
}

void AccountList::DeleteAccount(const std::string& IBAN)
{
	account_iterator accountPosition = GetAccountPosition(IBAN);

	if (accountPosition == end())
	{
		throw std::exception("error : account doesn't exist\n");
	}

	auto accountIndexInVector = accountPosition - m_accounts.begin();

	delete m_accounts[accountIndexInVector];

	m_accounts.erase(accountPosition);
}

void AccountList::DeleteAllCustomersAccounts(const std::string& customerName)
{
	for (size_t i = 0; i < m_accounts.size(); i++)
	{
		if (m_accounts[i]->AccountOwnedByCustomer(customerName))
		{
			delete m_accounts[i];

			m_accounts.erase(m_accounts.begin() + i);
		}
	}
}

void AccountList::Clear()
{
	ClearAccounts();
}

bool AccountList::Empty() const
{
	return m_accounts.empty();
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
	return m_accounts.begin();
}

account_iterator AccountList::end()
{
	return m_accounts.end();
}

account_const_iterator AccountList::begin() const
{
	return m_accounts.begin();
}

account_const_iterator AccountList::end() const
{
	return m_accounts.end();
}

// private helpers
void AccountList::ClearAccounts()
{
	// deleting the data pointed by the pointers 
	// using a pointer reference to be able to do the assignment to nullptr correctly(maybe unnecessary)
	for (Account*& account : m_accounts)
	{
		delete account;
		account = nullptr;
	}

	// clearing the pointers that the vector holds
	m_accounts.clear();
}

void AccountList::CopyAccounts(const std::vector<Account*>& otherAccounts)
{
	for (const Account* account : otherAccounts)
	{
		m_accounts.emplace_back(account->CloneAccount());
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