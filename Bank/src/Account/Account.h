#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

#include "AccountType/AccountType.h"

class Account 
{
public:
	Account();
	Account(const Account& other) = default;
	Account(const std::string& ownerName);
	Account(const std::string& ownerName, double initialDeposit);

	virtual ~Account() = default;

	Account& operator=(const Account& other) = default;

	const double GetBalance() const;
	const std::string GetOwnerName() const;
	const std::string GetAccountIBAN() const;

	void SetOwnerName(const std::string& ownerName);
	void SetIBAN(const std::string& iban);

	bool AccountOwnedByCustomer(const std::string& ownerName) const;

	virtual void Deposit(double depositAmmount) = 0;
	virtual void Withdraw(double withdrawAmmount) = 0;
	virtual void DisplayAccount(std::ostream& outStream) const = 0;
	virtual int GetAccountType() const = 0;
	virtual Account* CloneAccount() const = 0;

	friend std::ostream& operator<<(std::ostream& outStream, const Account& account);

protected:
	void IncreaseBalance(double increase);
	void DecreaseBalance(double decrease);

private:
	static unsigned int M_IBAN_COUNTER;
	static std::string M_IBAN_PREFIX;

private:
	double balance;
	std::string ownerName;
	std::string accountIBAN;
};


#endif // !ACCOUNT_H