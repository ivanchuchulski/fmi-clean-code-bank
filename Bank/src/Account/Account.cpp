#include "Account.h"
#include "Utils/Utils.h"

// static members initialization
unsigned int Account::M_IBAN_COUNTER = 0;
std::string Account::M_IBAN_PREFIX = "#IBAN#";

Account::Account()
	:	m_balance(0.0),
		m_ownerID(),
		m_accountIBAN(Utils::GenerateNumberedStringWithPrefix(M_IBAN_PREFIX, M_IBAN_COUNTER))
{
	M_IBAN_COUNTER++;
}

Account::Account(const std::string& ownerID)
	:	m_balance(0.0),
		m_ownerID(ownerID),
		m_accountIBAN(Utils::GenerateNumberedStringWithPrefix(M_IBAN_PREFIX, M_IBAN_COUNTER))
{
	M_IBAN_COUNTER++;
}

Account::Account(const std::string& ownerID, double initialDeposit)
	:	m_balance(initialDeposit > 0 ? initialDeposit : 0.0),
		m_ownerID(ownerID),
		m_accountIBAN(Utils::GenerateNumberedStringWithPrefix(M_IBAN_PREFIX, M_IBAN_COUNTER++))
{
	M_IBAN_COUNTER++;
}

void Account::IncreaseBalance(double increase)
{
	m_balance += increase;
}

void Account::DecreaseBalance(double decrease)
{
	m_balance -= decrease;
}

const double Account::GetBalance() const
{
	return m_balance;
}

const std::string Account::GetOwnerID() const
{
	return std::string(m_ownerID);
}

const std::string Account::GetAccountIBAN() const
{
	return std::string(m_accountIBAN);
}

void Account::SetOwnerID(const std::string& ownerID)
{
	m_ownerID = ownerID;
}

void Account::SetIBAN(const std::string& iban)
{
	m_accountIBAN = iban;
}

bool Account::AccountOwnedByCustomer(const std::string& customerID) const
{
	return m_ownerID == customerID;
}

std::ostream& operator<<(std::ostream& outStream, const Account& account)
{
	outStream << "balance : " << account.m_balance << '\n' 
				<< "ownerID : " << account.m_ownerID  << '\n' 
				<< "IBAN : " << account.m_accountIBAN;

	return outStream;
}