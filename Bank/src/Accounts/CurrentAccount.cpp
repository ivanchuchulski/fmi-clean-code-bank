#include "CurrentAccount.h"


//
CurrentAccount::CurrentAccount(const CurrentAccount& other)
	:	Account(other)
{}


CurrentAccount::CurrentAccount(const std::string& ownerID)
	: Account(ownerID)
{}

CurrentAccount::CurrentAccount(const std::string& ownerID, double initialDeposit)
	:	Account(ownerID, initialDeposit)
{}


CurrentAccount & CurrentAccount::operator=(const CurrentAccount & other)
{
	if (this != &other) 
	{
		Account::operator=(static_cast<const Account&>(other));
	}

	return *this;
}


// virtual methods
void CurrentAccount::InputAccount(const std::string& ownerID)
{
	Account::InputAccount(ownerID);
}


// pure virtual mehtods overrides
int CurrentAccount::GetAccountType() const
{
	return static_cast<int>(AccountType::CurrentAccount);
}

Account* CurrentAccount::CloneAccount() const
{
	return new CurrentAccount(*this);
}

void CurrentAccount::Deposit(double depositAmmount)
{
	IncreaseBalance(depositAmmount);
}

bool CurrentAccount::Withdraw(double withdrawAmmount)
{
	if (GetBalance() < withdrawAmmount) 
	{
		return false; 
	}

	DecreaseBalance(withdrawAmmount);
	return true;
}

void CurrentAccount::DisplayAccount() const
{
	std::cout << *this << '\n';
}

// friend methods
std::ostream& operator<<(std::ostream& outStream, const CurrentAccount& currentAccount)
{

	outStream << "account type : Current Account\n" 
				<< static_cast<const Account&>(currentAccount);

	return outStream;
}

std::istream& operator>>(std::istream& inStream, CurrentAccount& currentAccount)
{
	inStream >> static_cast<Account&>(currentAccount);

	return inStream;
}