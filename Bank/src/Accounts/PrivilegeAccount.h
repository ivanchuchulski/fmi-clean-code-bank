#pragma once

#ifndef PRIVILEGE_ACCOUNT_H
#define PRIVILEGE_ACCOUNT_H

#include "Account/Account.h"

class PrivilegeAccount 
	: public Account
{
public:
	PrivilegeAccount() = delete;
	PrivilegeAccount(const PrivilegeAccount& other) = default;
	PrivilegeAccount(const std::string& ownerID);
	PrivilegeAccount(const std::string& ownerID, double initialDeposit, double overdraft);

	virtual ~PrivilegeAccount();

	PrivilegeAccount& operator=(const PrivilegeAccount& other);

	// getters
	const double GetOverdraft() const;

	// setters
	void IncreaseOverdraft(double overdraftIncrease);
	void DecreaseOverdraft(double overdraftDecrease);

	// virtual methods
	virtual void InputAccount(const std::string& ownerID) override;

	// pure virtual mehtods overrides
	virtual int GetAccountType() const override;
	virtual Account* CloneAccount() const override;
	void Deposit(double depositAmmount) override;
	bool Withdraw(double withdrawAmmount) override;
	void DisplayAccount() const override;

	// friend methods
	friend std::ostream& operator<<(std::ostream& outStream, const PrivilegeAccount& somePrivilAcc);

private:
	static const double M_OVERDRAFT_DEFAULT;

private:
	double m_overdraftOverBalance;
};

#endif // !PRIVILEGE_ACCOUNT_H
