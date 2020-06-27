#pragma once

#include "ConsoleApplication/ConsoleInterface/ConsoleInterface.h"
#include "Bank/Bank.h"


class ConsoleApplication
{
public:
	ConsoleApplication();
	~ConsoleApplication();
	
	void Start();

private:
	Customer* InputCustomerDetails();
	Account* InputAccountDetails();
	void AddCustomer();
	void DeleteCustomer();
	void AddAccount();
	void DeleteAccount();
	void ListCustomers();
	void ListAllCustomersAccount();
	void ListAccounts();
	void BankInformation();
	void Withdraw();
	void Deposit();
	void Transfer();

private:
	ConsoleInterface consoleInterface;
	Bank bank;
};
