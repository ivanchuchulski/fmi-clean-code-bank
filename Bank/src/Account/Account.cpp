#include "Account.h"
#include "Utils/Utils.h"

// static members initialization
unsigned int Account::M_IBAN_COUNTER = 0;
std::string Account::M_IBAN_PREFIX = "#IBAN#";

Account::Account()
	:	balance(0.0),
		ownerName(),
		accountIBAN(Utils::GenerateNumberedStringWithPrefix(M_IBAN_PREFIX, M_IBAN_COUNTER))
{
	M_IBAN_COUNTER++;
}

Account::Account(const std::string& ownerName)
	:	balance(0.0),
		ownerName(ownerName),
		accountIBAN(Utils::GenerateNumberedStringWithPrefix(M_IBAN_PREFIX, M_IBAN_COUNTER))
{
	M_IBAN_COUNTER++;
}

Account::Account(const std::string& ownerName, double initialDeposit)
	:	balance(initialDeposit > 0 ? initialDeposit : 0.0),
		ownerName(ownerName),
		accountIBAN(Utils::GenerateNumberedStringWithPrefix(M_IBAN_PREFIX, M_IBAN_COUNTER++))
{
	M_IBAN_COUNTER++;
}

void Account::IncreaseBalance(double increase)
{
	balance += increase;
}

void Account::DecreaseBalance(double decrease)
{
	balance -= decrease;
}

const double Account::GetBalance() const
{
	return balance;
}

const std::string Account::GetOwnerName() const
{
	return std::string(ownerName);
}

const std::string Account::GetAccountIBAN() const
{
	return std::string(accountIBAN);
}

void Account::SetOwnerName(const std::string& ownerName)
{
	this->ownerName = ownerName;
}

void Account::SetIBAN(const std::string& iban)
{
	this->accountIBAN = iban;
}

bool Account::AccountOwnedByCustomer(const std::string& ownerName) const
{
	return this->ownerName == ownerName;
}

std::ostream& operator<<(std::ostream& outStream, const Account& account)
{
	outStream << "balance : " << account.balance << '\n' 
				<< "ownerName : " << account.ownerName  << '\n' 
				<< "IBAN : " << account.accountIBAN;

	return outStream;
}