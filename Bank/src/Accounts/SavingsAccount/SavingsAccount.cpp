#include "SavingsAccount.h"
#include <exception>

// static members initialization
const float SavingsAccount::M_YEARLY_INTEREST_DEFAULT = 1.1f;

SavingsAccount::SavingsAccount()
	:	Account(),
		m_yearlyInterestProcent(M_YEARLY_INTEREST_DEFAULT)
{}

SavingsAccount::SavingsAccount(const std::string& ownerID)
	:	Account(ownerID),
		m_yearlyInterestProcent(M_YEARLY_INTEREST_DEFAULT)
{}

SavingsAccount::SavingsAccount(const std::string& ownerID, double initialDeposit, float yearlyInterestProcent)
	:	Account(ownerID, initialDeposit),
		m_yearlyInterestProcent((yearlyInterestProcent >= 0.0f && yearlyInterestProcent <= 100.0f) ? yearlyInterestProcent : M_YEARLY_INTEREST_DEFAULT)
{}

SavingsAccount& SavingsAccount::operator=(const SavingsAccount& other)
{
	if (this != &other) 
	{
		Account::operator=(static_cast<const Account&>(other));
		m_yearlyInterestProcent = other.m_yearlyInterestProcent;
	}

	return *this;
}

const float SavingsAccount::GetInterestProcent()
{
	return m_yearlyInterestProcent;
}

void SavingsAccount::IncreaseInterest(float interestIncrease)
{
	if (interestIncrease < 0)
	{
		throw std::exception("error : interest increase can\'t be negative");
	}

	float increasedInterest = m_yearlyInterestProcent + interestIncrease;

	if (increasedInterest > 100)
	{
		throw std::exception("error : interest can\'t become more than 100%");
	}

	m_yearlyInterestProcent = increasedInterest;
}

void SavingsAccount::DecreaseInterest(float interestDecrease)
{
	if (interestDecrease < 0)
	{
		throw std::exception("error : interest decrease can\'t be negative");
	}

	float decreasedInterest = m_yearlyInterestProcent - interestDecrease;
	
	if (decreasedInterest < 0)
	{
		throw std::exception("error : interest can\'t become less than 0%");
	}

	m_yearlyInterestProcent = decreasedInterest;
}

void SavingsAccount::Deposit(double depositAmmount)
{
	IncreaseBalance(depositAmmount);
}

void SavingsAccount::Withdraw(double withdrawAmmount)
{
	if (GetBalance() < withdrawAmmount) 
	{
		throw std::exception("error : not enough balance to finish withdraw");
	}

	DecreaseBalance(withdrawAmmount);
}

void SavingsAccount::DisplayAccount(std::ostream& outStream) const
{
	std::cout << *this << '\n';
}

int SavingsAccount::GetAccountType() const
{
	return static_cast<int>(AccountType::SavingsAccount);
}

Account* SavingsAccount::CloneAccount() const
{
	return new SavingsAccount(*this);
}

std::ostream& operator<<(std::ostream& outStream, const SavingsAccount& savingsAccount)
{
	outStream << "account type : Savings Account\n" 
		<< static_cast<const Account&>(savingsAccount)
		<< "\n\t" << "interst rate : " << savingsAccount.m_yearlyInterestProcent <<  '\n';

	return outStream;
}