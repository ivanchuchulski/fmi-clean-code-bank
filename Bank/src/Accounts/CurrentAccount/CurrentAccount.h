#pragma once

#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "Account/Account.h"

class CurrentAccount : public Account
{
public:
	CurrentAccount();
	CurrentAccount(const CurrentAccount& other);
	CurrentAccount(const std::string& ownerName);
	CurrentAccount(const std::string& ownerName, double initialDeposit);

	virtual ~CurrentAccount() = default;

	CurrentAccount& operator=(const CurrentAccount& other);

	virtual void Deposit(double depositAmmount) override;
	virtual void Withdraw(double withdrawAmmount) override;
	virtual void DisplayAccount(std::ostream& outStream) const override;
	virtual int GetAccountType() const override;
	virtual Account* CloneAccount() const override;

	friend std::ostream& operator<<(std::ostream& outStream, const CurrentAccount& currentAccount);
};

#endif // !CURRENT_ACCOUNT_H


