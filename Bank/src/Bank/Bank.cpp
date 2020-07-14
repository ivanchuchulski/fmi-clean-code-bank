#include "Bank.h"

#include <algorithm>


Bank::Bank()
	:	m_bankName("the anonymous bank"),	
		m_bankAddress("hidden address"),
		m_customerList(),
		m_accountList()
{}

Bank::Bank(const Bank& other)
	:	m_bankName(other.m_bankName),
		m_bankAddress(other.m_bankAddress),
		m_customerList(other.m_customerList),
		m_accountList(other.m_accountList)
{}

Bank::Bank(const std::string& bankName, const std::string& bankAddress)
	:	m_bankName(bankName),
		m_bankAddress(bankAddress),
		m_customerList(),
		m_accountList()
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
	m_bankName = name;
}

void Bank::ChangeBankAddress(const std::string& address) 
{
	m_bankAddress = address;
}

const std::string Bank::GetName() const
{
	return std::string(m_bankName);
}

const std::string Bank::GetAddress() const
{
	return std::string(m_bankAddress);
}

void Bank::AddCustomer(Customer* customer)
{
	try
	{
		m_customerList.AddCustomer(customer);
	}
	catch (std::exception& exception)
	{
		throw;
	}
}

void Bank::DeleteCustomer(const std::string& customerID)
{
	try
	{
		m_customerList.DeleteCustomer(customerID);
		
		m_accountList.DeleteAllCustomersAccounts(customerID);
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
			throw std::exception("account addition failed : the bank has no registered customers\n");
		}

		if (!m_customerList.CustomerExists(account->GetOwnerID()))
		{
			throw std::exception("account addition failed : the customer owner doesn't exist\n");
		}
		
		m_accountList.AddAccount(account);
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
			throw std::exception("account removal failed : the bank has no registered customers\n");
		}

		m_accountList.DeleteAccount(accountIBAN);
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
			throw std::exception("money transfer failed : the bank has no registered customers\n");
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
			throw std::exception("money deposit failed : the bank has no registered customers\n");
		}

		if (NoOpenedAccounts())
		{
			throw std::exception("money deposit failed : the bank has no opened accounts\n");
		}

		m_accountList.DepositToAccount(accountIBAN, depositAmmount);
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
			throw std::exception("money withdraw failed : the bank has no registered customers\n");
		}

		if (NoOpenedAccounts())
		{
			throw std::exception("money withdraw failed : the bank has no opened accounts\n");
		}

		m_accountList.WithdrawFromAccount(accountIBAN, withdrawAmmount);
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
		throw std::exception("bank has no registered customers\n");
	}

	return m_customerList;
}

const AccountList& Bank::GetAccountList()
{
	if (m_customerList.Empty())
	{
		throw std::exception("bank has no registered customers and so there are no opened account\n");
	}

	if (m_accountList.Empty())
	{
		throw std::exception("bank has no opened accounts\n");
	}

	return m_accountList;
}

const Customer& Bank::GetCustomerByID(std::string& customerID)
{
	if (m_customerList.Empty())
	{
		throw std::exception("bank has no registered customers and there are no opened account\n");
	}

	if (!m_customerList.CustomerExists(customerID))
	{
		throw std::exception("error : customer is not registered\n");
	}

	return m_customerList.GetCustomerByID(customerID);
}

// private helper methods
void Bank::ClearBank()
{
	m_bankName.clear();
	m_bankAddress.clear();
	m_customerList.Clear();
	m_accountList.Clear();
}

void Bank::CopyOtherBank(const Bank& otherBank)
{
	m_bankName = otherBank.m_bankName;
	m_bankAddress = otherBank.m_bankAddress;
	m_customerList = otherBank.m_customerList;
	m_accountList = otherBank.m_accountList;
}

bool Bank::NoRegisteredCustomers() const
{
	return m_customerList.Empty();
}

bool Bank::NoOpenedAccounts() const
{
	return m_accountList.Empty();
}