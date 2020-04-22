#include "Bank.h"

#include <algorithm>
#include "../ConsoleInput.h"


Bank::Bank()
	:	m_bankName("the anonymous bank"),	
		m_bankAddress("hidden address"),
		m_customerList(),
		m_accounts()
{}

Bank::Bank(const Bank& other)
	:	m_bankName(other.m_bankName),
		m_bankAddress(other.m_bankAddress),
		m_customerList(other.m_customerList),
		m_accounts()
{
	CopyAccounts(other.m_accounts);
}

Bank::Bank(const std::string& bankName, const std::string& bankAddress)
	:	m_bankName(bankName),
		m_bankAddress(bankAddress),
		m_customerList(),
		m_accounts()
{}

Bank::~Bank()
{
	ClearAccounts();
}

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



void Bank::AddCustomer(const std::string& customerName, const std::string& customerAddress)
{
	try
	{
		m_customerList.AddCustomer(customerName, customerAddress);

		std::cout << "success : customer " << customerName << " added\n";
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}

}

void Bank::DeleteCustomer(const std::string& customerIDToRemove)
{
	try
	{
		m_customerList.DeleteCustomer(customerIDToRemove);
		
		RemoveAllCustomersAccounts(customerIDToRemove);

		std::cout << "customer removal success!\n";
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}
}


void Bank::AddAccount(const std::string& customerID, const AccountType accountType)
{
	if (m_customerList.Empty())
	{
		std::cout << "account addition failed : the bank has no customers\n";
		return;
	}

	if (m_customerList.CustomerDoesNotExist(customerID))
	{
		std::cout << "account addition failed : the customer doesn't exist\n";
		return;
	}

	Account* temp = nullptr;

	switch (accountType)
	{
		case AccountType::CurrentAccount :
			temp = new CurrentAccount(customerID);
			break;

		case AccountType::SavingsAccount :
			temp = new SavingsAccount(customerID);
			break;

		case AccountType::PrivileAccount :
			temp = new PrivilegeAccount(customerID);
			break;

		default :
			std::cout << "account addition failed : invalid account type\n";
			return;
	}

	//m_accounts.emplace_back(temp->CloneAccount());
	//delete temp;
	
	// or just that
	m_accounts.emplace_back(temp);

	std::cout << "account addition success\n";
}

void Bank::DeleteAccount(const std::string& accountIBAN)
{
	if (NoRegisteredCustomers())
	{
		std::cout << "account removal failed : the bank has no customers\n";
		return;
	}

	if (NoOpenedAccounts())
	{
		std::cout << "account removal failed : the bank has no accounts\n";
		return;
	}

	auto ibanIndex = GetAccountPosition(accountIBAN);

	if (!IsAccountOpened(ibanIndex))
	{
		std::cout << "account removal failed : no account with IBAN " << accountIBAN << " exists\n";
		return;
	}

	// delete the account : first free memory and then delete the pointer in the vector
	auto accountPosition = ibanIndex - m_accounts.begin();

	delete m_accounts[accountPosition];
	
	m_accounts.erase(ibanIndex);

	std::cout << "account removal success\n";
}

// bank money operations
void Bank::Transfer(const std::string& fromIBAN, const std::string& toIBAN, double ammount)
{
	if (NoRegisteredCustomers())
	{
		std::cout << "the bank has no customers\n";
		return;
	}

	if (NoOpenedAccounts())
	{
		std::cout << "bank has no accounts\n";
		return;
	}

	// check if the passed strings are the same
	if (fromIBAN== toIBAN)
	{
		std::cout << "error : source and destination IBANs are the same\n";
		return;
	}

	auto sourceIt = GetAccountPosition(fromIBAN);
	auto destIt = GetAccountPosition(toIBAN);

	// check if both accounts exist
	if (!IsAccountOpened(sourceIt))
	{
		std::cout << "error : account to transfer from doesn't exist\n";
		return;
	}

	if (!IsAccountOpened(destIt))
	{
		std::cout << "error : account to transfer to doesn't exist\n";
		return;
	}

	auto sourceArrayIndex = sourceIt- m_accounts.begin();
	auto destArrayIndex = destIt - m_accounts.begin();

	 //try to withdraw from source account
	bool withdrawSuccessful = m_accounts[sourceArrayIndex]->Withdraw(ammount);

	if (!withdrawSuccessful) 
	{
		std::cout << "Can not withraw that ammount from the account!\n";
		return;
	}

	// transfer to destination account
	m_accounts[destArrayIndex]->Deposit(ammount);

	std::cout << "Transfer successful!\n";
}

void Bank::DepositToAccount(const std::string& accountIBAN, double depositAmmount)
{
	auto foundIndex = GetAccountPosition(accountIBAN);

	if (!IsAccountOpened(foundIndex)) 
	{
		std::cout << "depoit failed : account doesn't exist\n";
		return;
	}

	auto accountArrayIndex = foundIndex - m_accounts.begin();

	m_accounts[accountArrayIndex]->Deposit(depositAmmount);

	std::cout << "account deposit success\n";
}

bool Bank::WithdrawFromAccount(const std::string& accountIBAN, double withdrawAmmount)
{
	auto foundIndex = GetAccountPosition(accountIBAN);

	if (!IsAccountOpened(foundIndex)) 
	{
		std::cout << "withdraw failed : account doesn't exist\n";
		return false;
	}

	auto accountArrayIndex = foundIndex - m_accounts.begin();

	bool withdrawSuccessful = m_accounts[accountArrayIndex]->Withdraw(withdrawAmmount);

	if (!withdrawSuccessful) 
	{
		std::cout << "withraw failed : withraw ammount is to high\n";
		return false;
	}

	std::cout << "withdraw success\n";
	return true;
}

// bank information 
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
		if (NoOpenedAccounts())
		{
			std::cout << "bank has no accounts opened\n";
			return;
		}

		std::cout << "printing bank accounts : \n";

		for (const Account* account : m_accounts)
		{
			account->DisplayAccount();
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what();
	}

}

void Bank::ListCustomerAccount(const std::string& customerID) const
{
	try
	{
		m_customerList.PrintCustomerDetails(customerID);

		if (NoOpenedAccounts())
		{
			std::cout << "bank has no accounts\n";
			return;
		}

		for (const Account* account : m_accounts)
		{
			if (account->AccountOwnedByCustomer(customerID))
			{
				account->DisplayAccount();
			}
		}

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
	ClearAccounts();
}

void Bank::CopyOtherBank(const Bank& otherBank)
{
	m_bankName = otherBank.m_bankName;
	m_bankAddress = otherBank.m_bankAddress;
	m_customerList = otherBank.m_customerList;
	CopyAccounts(otherBank.m_accounts);
}

void Bank::ClearAccounts()
{
	// deleting the data pointed by the pointers 
	// using a pointer reference to be able to do the assignment to nullptr correctly(maybe unnecessary)
	for (Account*& account : m_accounts)
	{
		delete account;
		account = nullptr;
	}

	// clearing the pointers that the vector holds
	m_accounts.clear();
}

void Bank::CopyAccounts(const std::vector<Account*>& otherAccounts)
{
	for (const Account* account : otherAccounts)
	{
		m_accounts.emplace_back(account->CloneAccount());
	}
}

std::vector<Account*>::const_iterator Bank::GetAccountPosition(const std::string& accountIBAN) const
{
	for (auto accountIt = m_accounts.begin(); accountIt != m_accounts.end(); ++accountIt)
	{
		if ((*accountIt)->GetAccountIBAN() == accountIBAN)
		{
			return accountIt;
		}
	}

	// if nothing found
	return m_accounts.end();
}

bool Bank::IsAccountOpened(const std::vector<Account*>::const_iterator accountIt) const
{
	return accountIt != m_accounts.end();
}

bool Bank::NoRegisteredCustomers() const
{
	return m_customerList.Empty();
}

bool Bank::NoOpenedAccounts() const
{
	return m_accounts.empty();
}
void Bank::RemoveAllCustomersAccounts(const std::string& customerIDToRemove)
{
	for (size_t i = 0; i < m_accounts.size(); i++)
	{
		if (m_accounts[i]->GetOwnerID() == customerIDToRemove)
		{
			delete m_accounts[i];

			m_accounts.erase(m_accounts.begin() + i);
		}
	}
}