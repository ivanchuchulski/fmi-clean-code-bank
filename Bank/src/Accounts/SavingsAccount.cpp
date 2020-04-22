#include "SavingsAccount.h"


// static members initialization
const float SavingsAccount::M_YEARLY_INTEREST_DEFAULT = 1.1f;

//
SavingsAccount::SavingsAccount(const std::string& ownerID)
	:	Account(ownerID),
		m_yearlyInterestProcent(M_YEARLY_INTEREST_DEFAULT)
{}

SavingsAccount::SavingsAccount(const std::string& ownerID, double initialDeposit, float yearlyInterestProcent)
	:	Account(ownerID, initialDeposit),
		m_yearlyInterestProcent((yearlyInterestProcent >= 0.0f && yearlyInterestProcent <= 100.0f) ? yearlyInterestProcent : M_YEARLY_INTEREST_DEFAULT)
{}

SavingsAccount::~SavingsAccount()
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


// getters
const float SavingsAccount::GetInterestProcent()
{
	return m_yearlyInterestProcent;
}


// setters
void SavingsAccount::IncreaseInterest(float interestIncrease)
{
	if (interestIncrease < 0)
		return;

	float increasedInterest = m_yearlyInterestProcent + interestIncrease;

	if (increasedInterest > 100)
		return;

	m_yearlyInterestProcent = increasedInterest;
}

void SavingsAccount::DecreaseInterest(float interestDecrease)
{
	if (interestDecrease < 0)
		return;

	float decreasedInterest = m_yearlyInterestProcent - interestDecrease;
	
	if (decreasedInterest < 0)
		return;

	m_yearlyInterestProcent = decreasedInterest;
}


// virtual methods
void SavingsAccount::InputAccount(const std::string& ownerID)
{
	Account::InputAccount(ownerID);

	std::cout << "enter yealy interest : ";
	std::cin >> m_yearlyInterestProcent;
}


// pure virtual mehtods overrides
int SavingsAccount::GetAccountType() const
{
	return static_cast<int>(AccountType::SavingsAccount);
}

Account* SavingsAccount::CloneAccount() const
{
	return new SavingsAccount(*this);
}

void SavingsAccount::Deposit(double depositAmmount)
{
	IncreaseBalance(depositAmmount);
}

bool SavingsAccount::Withdraw(double withdrawAmmount)
{
	if (GetBalance() < withdrawAmmount) 
	{
		return false;
	}

	DecreaseBalance(withdrawAmmount);
	return true;
}

void SavingsAccount::DisplayAccount() const
{
	std::cout << *this << '\n';
}

// friend methods
std::ostream& operator<<(std::ostream& outStream, const SavingsAccount& savingsAccount)
{
	outStream << "account type : Savings Account\n" 
		<< static_cast<const Account&>(savingsAccount)
		<< "\n\t" << "interst rate : " << savingsAccount.m_yearlyInterestProcent <<  '\n';

	return outStream;
}