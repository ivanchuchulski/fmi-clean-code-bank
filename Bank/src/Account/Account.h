#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

#include "AccountType/AccountType.h"


class Account 
{
public:
	Account() = delete;
	Account(const Account& other) = default;
	Account(const std::string& ownerID);
	Account(const std::string& ownerID, double initialDeposit);

	virtual ~Account() = default;

	Account& operator=(const Account& other) = default;

	// getters
	const double GetBalance() const;
	const std::string GetOwnerID() const;
	const std::string GetAccountIBAN() const;

	// setters
	void SetOwnerID(const std::string& ownerID);
	void SetIBAN(const std::string& iban);

	bool AccountOwnedByCustomer(const std::string& customerID) const;

	// virtual methods
	virtual void InputAccount(const std::string& ownerID);

	// pure virtual methods
	virtual int GetAccountType() const = 0;
	virtual Account* CloneAccount() const = 0;
	virtual void Deposit(double depositAmmount) = 0;
	virtual bool Withdraw(double withdrawAmmount) = 0;
	virtual void DisplayAccount() const = 0;


	// friend methods
	friend std::ostream& operator<<(std::ostream& outStream, const Account& account);
	friend std::istream& operator>>(std::istream& inStream, Account& account);

protected:
	// modifiers
	void IncreaseBalance(double increase);
	void DecreaseBalance(double decrease);

private:
	static unsigned int M_IBAN_COUNTER;
	static std::string M_IBAN_PREFIX;

private:
	double m_balance;
	std::string m_ownerID;
	std::string m_accountIBAN;
};


#endif // !ACCOUNT_H