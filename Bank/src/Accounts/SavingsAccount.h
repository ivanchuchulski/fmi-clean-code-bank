#pragma once

#include "Account/Account.h"

class SavingsAccount
	:	public Account
{
public:
	SavingsAccount() = delete;
	SavingsAccount(const SavingsAccount& other) = default;
	SavingsAccount(const std::string& ownerID);
	SavingsAccount(const std::string& ownerID, double initialDeposit, float yearlyInterestProcent);

	~SavingsAccount();

	SavingsAccount& operator=(const SavingsAccount& other);

	// getters
	const float GetInterestProcent();

	// setters
	void IncreaseInterest(float interestIncrease);
	void DecreaseInterest(float interestDecrease);

	// virtual methods
	virtual void InputAccount(const std::string& ownerID) override;

	// pure virtual mehtods overrides
	virtual int GetAccountType() const override;
	virtual Account* CloneAccount() const override;
	virtual void Deposit(double depositAmmount) override;
	virtual bool Withdraw(double withdrawAmmount) override;
	virtual void DisplayAccount() const override;

	// friend methods
	friend std::ostream& operator<<(std::ostream& outStream, const SavingsAccount& savingsAccount);

private:
	static const float M_YEARLY_INTEREST_DEFAULT;

private:
	float m_yearlyInterestProcent;
};

