#include "PrivilegeAccount.h"
#include <exception>

// static member initialization
const double PrivilegeAccount::M_OVERDRAFT_DEFAULT = 100.0;

PrivilegeAccount::PrivilegeAccount()
	:	Account(),
		m_overdraftOverBalance(M_OVERDRAFT_DEFAULT)
{}

PrivilegeAccount::PrivilegeAccount(const std::string& ownerID)
	:	Account(ownerID),
		m_overdraftOverBalance(M_OVERDRAFT_DEFAULT)
{}

PrivilegeAccount::PrivilegeAccount(const std::string& ownerID, double initialDeposit, double overdraft)
	:	Account(ownerID, initialDeposit),
		m_overdraftOverBalance((overdraft >= 0) ? overdraft : M_OVERDRAFT_DEFAULT)
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

const double PrivilegeAccount::GetOverdraft() const
{
	return m_overdraftOverBalance;
}

void PrivilegeAccount::IncreaseOverdraft(double overdraftIncrease)
{
	if (overdraftIncrease < 0)
	{
		throw std::exception("error : overdraft increase can\'t be negative value\n");
	}

	m_overdraftOverBalance += overdraftIncrease;
}

void PrivilegeAccount::DecreaseOverdraft(double overdraftDecrease)
{
	if (overdraftDecrease < 0)
	{
		throw std::exception("error : overdraft descrease can\'t be negative number\n");
	}

	double decreasedOverdraft = m_overdraftOverBalance - overdraftDecrease;

	if (decreasedOverdraft < 0)
	{
		throw std::exception("error : overdraft can\'t become negative number\n");
	}

	m_overdraftOverBalance = decreasedOverdraft;
}

void PrivilegeAccount::Deposit(double depositAmmount)
{
	IncreaseBalance(depositAmmount);
}

void PrivilegeAccount::Withdraw(double withdrawAmmount)
{
	// if there is zero balance no withdraw
	if (GetBalance() <= 0)
	{
		throw std::exception("error : negative balance");
	}

	// if balance alone is enough for the withdraw, then just directly decrese from it
	else if (GetBalance() >= withdrawAmmount)
	{
		DecreaseBalance(withdrawAmmount);
	}

	// if balance is not enough for the withdraw and we have also use the overdraft
	else if (GetBalance() + m_overdraftOverBalance >= withdrawAmmount) 
	{
		double moneyLack = withdrawAmmount - GetBalance();

		DecreaseOverdraft(moneyLack);
		DecreaseBalance(withdrawAmmount - moneyLack);
	}

	// if balance plus overdraft is not enough to cover the withdraw
	else 
	{
		throw std::exception("error : not enough balace to finish withdraw");
	}
}

void PrivilegeAccount::DisplayAccount() const
{
	std::cout << *this << '\n';
}

int PrivilegeAccount::GetAccountType() const
{
	return static_cast<int>(AccountType::PrivileAccount);
}

Account* PrivilegeAccount::CloneAccount() const
{
	return new PrivilegeAccount(*this);
}

std::ostream& operator<<(std::ostream& outStream, const PrivilegeAccount& privilegedAccount)
{
	outStream << "account type : Privileged Account" << "\n"
		<< "overdraft : " << privilegedAccount.m_overdraftOverBalance << "\n";

	outStream << static_cast<const Account&>(privilegedAccount);

	return outStream;
}