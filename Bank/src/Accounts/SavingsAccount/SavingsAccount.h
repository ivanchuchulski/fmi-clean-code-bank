#pragma once

#include "Account/Account.h"

class SavingsAccount : public Account
{
public:
	SavingsAccount();
	SavingsAccount(const SavingsAccount& other) = default;
	SavingsAccount(const std::string& ownerName);
	SavingsAccount(const std::string& ownerName, double initialDeposit, float yearlyInterestProcent);

	virtual ~SavingsAccount() = default;

	SavingsAccount& operator=(const SavingsAccount& other);

	const float GetInterestProcent();

	void IncreaseInterest(float interestIncrease);
	void DecreaseInterest(float interestDecrease);

	virtual void Deposit(double depositAmmount) override;
	virtual void Withdraw(double withdrawAmmount) override;
	virtual void DisplayAccount(std::ostream& outStream) const override;
	virtual int GetAccountType() const override;
	virtual Account* CloneAccount() const override;

	friend std::ostream& operator<<(std::ostream& outStream, const SavingsAccount& savingsAccount);

private:
	static const float M_YEARLY_INTEREST_DEFAULT;

private:
	float m_yearlyInterestProcent;
};

