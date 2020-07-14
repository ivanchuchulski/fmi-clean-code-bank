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
	void DisplayMenu();
	OptionCode GetOptionFromConsole();

	void DispatchAndExecuteOption(OptionCode& optionCode);

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
	void StopApplication();

private:
	ConsoleInterface consoleInterface;
	Bank bank;
	bool isApplicationRunning;
};
