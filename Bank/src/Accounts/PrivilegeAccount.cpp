#include "PrivilegeAccount.h"

// TODO : improve logic in the Withdraw method

// static member initialization
const double PrivilegeAccount::M_OVERDRAFT_DEFAULT = 100.0;

//
PrivilegeAccount::PrivilegeAccount(const std::string& ownerID)
	:	Account(ownerID),
		m_overdraftOverBalance(M_OVERDRAFT_DEFAULT)
{}


PrivilegeAccount::PrivilegeAccount(const std::string& ownerID, double initialDeposit, double overdraft)
	:	Account(ownerID, initialDeposit),
		m_overdraftOverBalance((overdraft >= 0) ? overdraft : M_OVERDRAFT_DEFAULT)
{}

PrivilegeAccount::~PrivilegeAccount()
{}

PrivilegeAccount& PrivilegeAccount::operator=(const PrivilegeAccount& other)
{
	if (this != &other) 
	{
		Account::operator=(static_cast<const Account&>(other));
		m_overdraftOverBalance = other.m_overdraftOverBalance;
	}

	return *this;
}


// getters
const double PrivilegeAccount::GetOverdraft() const
{
	return m_overdraftOverBalance;
}


// setters
void PrivilegeAccount::IncreaseOverdraft(double overdraftIncrease)
{
	// overdraftIncrease should be positive number
	if (overdraftIncrease < 0)
		return;

	m_overdraftOverBalance += overdraftIncrease;
}

void PrivilegeAccount::DecreaseOverdraft(double overdraftDecrease)
{
	// overdraftDecrease should be positive number
	if (overdraftDecrease < 0)
	{
		return;
	}

	double decreasedOverdraft = m_overdraftOverBalance - overdraftDecrease;

	if (decreasedOverdraft < 0)
	{
		return;
	}

	m_overdraftOverBalance = decreasedOverdraft;
}


// virtual methods
void PrivilegeAccount::InputAccount(const std::string& ownerID)
{
	Account::InputAccount(ownerID);

	std::cout << "enter overdraft : ";
	std::cin >> m_overdraftOverBalance;
}

// pure virtual mehtods overrides
int PrivilegeAccount::GetAccountType() const
{
	return static_cast<int>(AccountType::PrivileAccount);
}

Account* PrivilegeAccount::CloneAccount() const
{
	return new PrivilegeAccount(*this);
}

void PrivilegeAccount::Deposit(double depositAmmount)
{
	IncreaseBalance(depositAmmount);
}

bool PrivilegeAccount::Withdraw(double withdrawAmmount)
{
	// if there is zero balance no withdraw
	if (GetBalance() <= 0)
	{
		return false;
	}

	// if balance plus overdraft is not enough to cover the withdraw
	else if (GetBalance() + m_overdraftOverBalance < withdrawAmmount) 
	{
		return false;
	}

	// if balance is enough for the withdraw
	else if (GetBalance() >= withdrawAmmount)
	{
		DecreaseBalance(withdrawAmmount);
		return true;
	}

	// if balance is not enough for the withdraw and we have also use the overdraft
	else 
	{
		double moneyLack = withdrawAmmount - GetBalance();

		DecreaseOverdraft(moneyLack);
		DecreaseBalance(withdrawAmmount - moneyLack);

		return true;
	}

}

void PrivilegeAccount::DisplayAccount() const
{
	std::cout << *this << '\n';
}


// friend methods
std::ostream& operator<<(std::ostream& outStream, const PrivilegeAccount& privilegedAccount)
{
	outStream << "account type : Privileged Account\n"
		<< static_cast<const Account&>(privilegedAccount)
		<< "\n\t" << "overdraft : " << privilegedAccount.m_overdraftOverBalance << '\n';

	return outStream;
}