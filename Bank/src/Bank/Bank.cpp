#include "Bank.h"

#include <algorithm>


Bank::Bank()
	:	name("the anonymous bank"),	
		address("hidden address"),
		customerList(),
		accountList()
{}

Bank::Bank(const Bank& other)
	:	name(other.name),
		address(other.address),
		customerList(other.customerList),
		accountList(other.accountList)
{}

Bank::Bank(const std::string& bankName, const std::string& bankAddress)
	:	name(bankName),
		address(bankAddress),
		customerList(),
		accountList()
{}

Bank::~Bank()
{}

Bank& Bank::operator=(const Bank& other)
{
	if (this != &other) 
	{
		ClearBank();
		CopyOtherBank(other);
	}

	return *this;
}

void Bank::ChangeBankName(const std::string& name) 
{
	this->name = name;
}

void Bank::ChangeBankAddress(const std::string& address) 
{
	this->address = address;
}

const std::string Bank::GetName() const
{
	return std::string(name);
}

const std::string Bank::GetAddress() const
{
	return std::string(address);
}

void Bank::AddCustomer(Customer* customer)
{
	try
	{
		customerList.AddCustomer(customer);
	}
	catch (std::exception& exception)
	{
		throw;
	}
}

void Bank::DeleteCustomer(const std::string& customerName)
{
	try
	{
		auto& customer = customerList.GetCustomer(customerName);

		accountList.DeleteAllCustomersAccounts(customerName);

		customerList.DeleteCustomer(customerName);
	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

void Bank::AddAccount(Account* account)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			throw std::exception("account addition failed : the bank has no registered customers and you can't open an account\n");
		}

		if (!customerList.CustomerExists(account->GetOwnerName()))
		{
			throw std::exception("account addition failed : the specified account owner doesn't exist\n");
		}
		
		accountList.AddAccount(account);
	}
	catch (const std::exception& exception)
	{
		throw; 
	}
}

void Bank::DeleteAccount(const std::string& accountIBAN)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			throw std::exception("account removal failed : the bank has no registered customers and thus no opened accounts\n");
		}

		accountList.DeleteAccount(accountIBAN);
	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

void Bank::Transfer(const std::string& fromIBAN, const std::string& toIBAN, double transferAmmount)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			throw std::exception("money transfer failed : the bank has no registered customers and thus no opened accounts\n");
		}

		if (NoOpenedAccounts()) 
		{
			throw std::exception("money transfer failed : the bank has no opened accounts\n");
		}

		WithdrawFromAccount(fromIBAN, transferAmmount);

		DepositToAccount(toIBAN, transferAmmount);

	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

void Bank::DepositToAccount(const std::string& accountIBAN, double depositAmmount)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			throw std::exception("money deposit failed : the bank has no registered customers and thus no opened accounts\n");
		}

		if (NoOpenedAccounts())
		{
			throw std::exception("money deposit failed : the bank has no opened accounts\n");
		}

		Account* account = accountList.GetAccount(accountIBAN);

		account->Deposit(depositAmmount);
	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

void Bank::WithdrawFromAccount(const std::string& accountIBAN, double withdrawAmmount)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			throw std::exception("money withdraw failed : the bank has no registered customers and thus no opened accounts\n");
		}

		if (NoOpenedAccounts())
		{
			throw std::exception("money withdraw failed : the bank has no opened accounts\n");
		}

		Account* account = accountList.GetAccount(accountIBAN);

		account->Withdraw(withdrawAmmount);
	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

const CustomerList& Bank::GetCustomerList()
{
	if (NoRegisteredCustomers())
	{
		throw std::exception("customer list view failed : bank has no registered customers\n");
	}

	return customerList;
}

const AccountList& Bank::GetAccountList()
{
	if (NoRegisteredCustomers())
	{
		throw std::exception("account list view failed : bank has no registered customers and thus no opened accounts\n");
	}

	if (NoOpenedAccounts())
	{
		throw std::exception("account list view failed : bank has no opened accounts\n");
	}

	return accountList;
}

const Customer& Bank::GetCustomerByName(const std::string& customerName)
{
	if (NoRegisteredCustomers())
	{
		throw std::exception("customer view failed : bank has no registered customers\n");
	}

	if (!customerList.CustomerExists(customerName))
	{
		throw std::exception("customer view failed : : customer is not registered\n");
	}

	return customerList.GetCustomer(customerName);
}

bool Bank::NoRegisteredCustomers() const
{
	return customerList.Empty();
}

bool Bank::NoOpenedAccounts() const
{
	return accountList.Empty();
}

// private methods
void Bank::ClearBank()
{
	name.clear();
	address.clear();
	customerList.Clear();
	accountList.Clear();
}

void Bank::CopyOtherBank(const Bank& otherBank)
{
	name = otherBank.name;
	address = otherBank.address;
	customerList = otherBank.customerList;
	accountList = otherBank.accountList;
}