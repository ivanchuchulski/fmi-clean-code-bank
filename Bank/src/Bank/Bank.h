#pragma once

#ifndef BANK_H
#define BANK_H

#include <vector>

#include "Account/Account.h"
#include "Accounts/CurrentAccount.h"	
#include "Accounts/SavingsAccount.h"
#include "Accounts/PrivilegeAccount.h"
#include "Customers/Customer.h"
#include "CustomerList/CustomerList.h"
#include "AccountList/AccountList.h"

class Bank 
{
public:
	Bank();
	Bank(const Bank& other);
	Bank(const std::string& bankName, const std::string& bankAddress);

	~Bank();

	Bank& operator=(const Bank& someBank);

	void ChangeBankName(const std::string& name);
	void ChangeBankAddress(const std::string& address);

	const std::string GetName() const;
	const std::string GetAddress() const;

	void AddCustomer(const std::string& customerName, const std::string& customerAddress);
	void DeleteCustomer(const std::string& customerID);

	void AddAccount(const std::string& ownerID, const AccountType accountType);
	void DeleteAccount(const std::string& iban);

	void Transfer(const std::string& fromIBAN, const std::string& toIBAN, double ammount);
	void DepositToAccount(const std::string& accountIBAN, double depositAmmount);
	void WithdrawFromAccount(const std::string& accountIBAN, double withdrawAmmount);

	void ListCustomers() const;
	void ListAccounts() const;
	void ListCustomerAccount(const std::string& customerID) const;
	void PrintSupportedAccountTypes() const;
	void DisplayBank() const;

	friend std::ostream& operator<<(std::ostream& outStream, const Bank& bank);

private:
	void ClearBank();
	void CopyOtherBank(const Bank& otherBank);

	bool NoRegisteredCustomers() const;
	bool NoOpenedAccounts() const;

private:
	std::string m_bankName;
	std::string m_bankAddress;
	CustomerList m_customerList;
	AccountList m_accountList;
};

#endif // !define BANK_H


