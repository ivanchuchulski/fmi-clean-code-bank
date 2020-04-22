#pragma once

#ifndef BANK_H
#define BANK_H

#include <vector>

#include "Customers/Customer.h"
#include "Account/Account.h"
#include "Accounts/CurrentAccount.h"	
#include "Accounts/SavingsAccount.h"
#include "Accounts/PrivilegeAccount.h"
#include "CustomerList.h"

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
	void DeleteCustomer(const std::string& customerIDToRemove);

	void AddAccount(const std::string& ownerID, const AccountType accountType);
	void DeleteAccount(const std::string& iban);

	void Transfer(const std::string& fromIBAN, const std::string& toIBAN, double ammount);
	void DepositToAccount(const std::string& accountIBAN, double depositAmmount);
	bool WithdrawFromAccount(const std::string& accountIBAN, double withdrawAmmount);

	void ListCustomers() const;
	void ListAccounts() const;
	void ListCustomerAccount(const std::string& customerID) const;
	void PrintSupportedAccountTypes() const;
	void DisplayBank() const;

	// friend methods
	friend std::ostream& operator<<(std::ostream& outStream, const Bank& bank);

private:
	void ClearBank();
	void CopyOtherBank(const Bank& otherBank);

	void ClearAccounts();
	void CopyAccounts(const std::vector<Account*>& otherAccounts);

	bool NoRegisteredCustomers() const;
	bool NoOpenedAccounts() const;
	
	void RemoveAllCustomersAccounts(const std::string& customerID);

	bool IsAccountOpened(const std::vector<Account*>::const_iterator accountIt) const;
	std::vector<Account*>::const_iterator GetAccountPosition(const std::string& accountIBAN) const;

private:
	std::string m_bankName;
	std::string m_bankAddress;
	CustomerList m_customerList;
	std::vector<Account*> m_accounts;
};

#endif // !define BANK_H


