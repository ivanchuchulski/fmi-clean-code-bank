#pragma once

#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "Account/Account.h"

class CurrentAccount 
	:	public Account
{
public:
	CurrentAccount() = delete;
	CurrentAccount(const CurrentAccount& other);
	CurrentAccount(const std::string& ownerID);
	CurrentAccount(const std::string& ownerID, double initialDeposit);

	virtual ~CurrentAccount() = default;

	CurrentAccount& operator=(const CurrentAccount& other);

	// virtual methods
	virtual void InputAccount(const std::string& ownerID) override;

	// pure virtual mehtods 
	virtual int GetAccountType() const override;
	virtual Account* CloneAccount() const override;
	virtual void Deposit(double depositAmmount) override;
	virtual bool Withdraw(double withdrawAmmount) override;
	virtual void DisplayAccount() const override;

	// friend methods
	friend std::ostream& operator<<(std::ostream& outStream, const CurrentAccount& currentAccount);
	friend std::istream& operator>>(std::istream& inStream, CurrentAccount& currentAccount);
};

#endif // !CURRENT_ACCOUNT_H


