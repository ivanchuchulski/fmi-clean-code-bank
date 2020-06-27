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

		std::cout << "success : added customer : \n" << *customer;
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

		std::cout << "customer removal success!\n";
	}
	catch (const std::exception& exception)
	{
		throw;
	}
}

void Bank::AddAccount(const std::string& customerID, const AccountType accountType)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			std::cout << "account addition failed : the bank has no customers\n";
			return;
		}

		if (m_customerList.CustomerDoesNotExist(customerID))
		{
			std::cout << "account addition failed : the customer doesn't exist\n";
			return;
		}
		
		m_accountList.AddAccount(customerID, accountType);

		std::cout << "account addition success\n";
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}

void Bank::DeleteAccount(const std::string& accountIBAN)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			std::cout << "account removal failed : the bank has no customers\n";
			return;
		}

		m_accountList.DeleteAccount(accountIBAN);

		std::cout << "account removal success\n";
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}

void Bank::Transfer(const std::string& fromIBAN, const std::string& toIBAN, double ammount)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			std::cout << "the bank has no customers\n";
			return;
		}

		WithdrawFromAccount(fromIBAN, ammount);
		DepositToAccount(toIBAN, ammount);

	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}

void Bank::DepositToAccount(const std::string& accountIBAN, double depositAmmount)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			std::cout << "the bank has no customers\n";
			return;
		}

		m_accountList.WithdrawFromAccount(accountIBAN, depositAmmount);
		std::cout << "account deposit success\n";
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what();
	}
}

void Bank::WithdrawFromAccount(const std::string& accountIBAN, double withdrawAmmount)
{
	try
	{
		if (NoRegisteredCustomers())
		{
			std::cout << "the bank has no customers\n";
			return;
		}

		m_accountList.WithdrawFromAccount(accountIBAN, withdrawAmmount);
		std::cout << "account withdraw success\n";
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}

void Bank::ListCustomers() const
{
	try
	{
		m_customerList.PrintCustomers();
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what();
	}
}

void Bank::ListAccounts() const
{
	try
	{
		m_accountList.PrintAccounts();
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what();
	}
}

void Bank::ListCustomerAccount(const std::string& customerID) const
{
	try
	{
		m_customerList.PrintCustomerDetails(customerID);
		m_accountList.PrintCustomerAccounts(customerID);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}

void Bank::PrintSupportedAccountTypes() const
{
	std::cout << static_cast<int>(AccountType::CurrentAccount) << " <-> CurrentAccount "
				<< static_cast<int>(AccountType::SavingsAccount) << " <-> Savings Account "
				<< static_cast<int>(AccountType::PrivileAccount) << " <-> Privileged Account\n";
}

void Bank::DisplayBank() const
{
	std::cout << *this << '\n';
}


std::ostream& operator<<(std::ostream& outStream, const Bank& bank)
{
	outStream << "\nBank " << bank.GetName() << " info : \n"
		<< "\taddress : " << bank.GetAddress();
	
	outStream << '\n';
	bank.ListCustomers();

	outStream << '\n';
	bank.ListAccounts();

	outStream << std::endl;

	return outStream;
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
	return m_accountList.NoOpenedAccounts();
}