#include "CurrentAccount.h"
#include <exception>


CurrentAccount::CurrentAccount()
	: Account()
{}

CurrentAccount::CurrentAccount(const CurrentAccount& other)
	: Account(other)
{}

CurrentAccount::CurrentAccount(const std::string& ownerName)
	: Account(ownerName)
{}

CurrentAccount::CurrentAccount(const std::string& ownerName, double initialDeposit)
	: Account(ownerName, initialDeposit)
{}

CurrentAccount& CurrentAccount::operator=(const CurrentAccount& other)
{
	if (this != &other)
	{
		Account::operator=(static_cast<const Account&>(other));
	}

	return *this;
}

void CurrentAccount::Deposit(double depositAmmount)
{
	if (depositAmmount < 0)
	{
		throw std::exception("error : deposit ammount can't be negative number");
	}

	IncreaseBalance(depositAmmount);
}

void CurrentAccount::Withdraw(double withdrawAmmount)
{
	if (withdrawAmmount < 0)
	{
		throw std::exception("error : withdraw ammount can'be negative number, it must be positive");
	}

	if (GetBalance() < withdrawAmmount)
	{
		throw std::exception("error : not enough balace to finish withdraw");
	}


	DecreaseBalance(withdrawAmmount);
}

void CurrentAccount::DisplayAccount(std::ostream& outStream) const
{
	outStream << *this << '\n';
}

int CurrentAccount::GetAccountType() const
{
	return static_cast<int>(AccountType::CurrentAccount);
}

Account* CurrentAccount::CloneAccount() const
{
	return new CurrentAccount(*this);
}

std::ostream& operator<<(std::ostream& outStream, const CurrentAccount& currentAccount)
{
	outStream << "account type : Current Account\n";

	outStream << static_cast<const Account&>(currentAccount);

	return outStream;
}