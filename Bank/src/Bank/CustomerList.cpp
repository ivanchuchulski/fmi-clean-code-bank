#include "Bank/CustomerList.h"
#include "../ConsoleInput.h"

#include <exception>


void CustomerList::PrintCustomers() const
{
	if (Empty())
	{
		throw std::exception("bank has no customers to display\n");
	}

	std::cout << "printing bank customers : \n";

	for (const Customer& customer : m_customers)
	{
		customer.DisplayCustomerInfo();
	}

}

void CustomerList::PrintCustomerDetails(const std::string& customerID) const
{
	if (Empty())
	{
		throw std::exception("bank has no customers to display\n");
	}

	if (CustomerDoesNotExist(customerID))
	{
		throw std::exception("customer does not exist\n");
	}

	auto customerPosition = GetCustomerPosition(customerID);

	customerPosition->DisplayCustomerInfo();
}

void CustomerList::AddCustomer(const std::string& customerName, const std::string& customerAddress)
{
	m_customers.emplace_back(Customer(customerName, customerAddress));
}

void CustomerList::DeleteCustomer(const std::string& customerID)
{
	if (Empty()) {
		throw std::exception("error : no regitered customers");
	}

	auto customerToRemovePosition = GetCustomerPosition(customerID);

	if (!IsCustomerRegistered(customerToRemovePosition))
	{
		throw std::exception("customer removal failed : customer id not found\n");
	}

	m_customers.erase(customerToRemovePosition);
}

void CustomerList::Clear()
{
	m_customers.clear();
}

bool CustomerList::Empty() const
{
	return m_customers.empty();
}

bool CustomerList::IsCustomerRegistered(std::vector<Customer>::const_iterator customerIt) const
{
	return customerIt != m_customers.end();
}

bool CustomerList::CustomerDoesNotExist(const std::string& customerID) const
{
	auto customerPosition = GetCustomerPosition(customerID);

	return !IsCustomerRegistered(customerPosition);
}

std::vector<Customer>::const_iterator CustomerList::GetCustomerPosition(const std::string& customerID) const
{
	for (auto customer = m_customers.begin(); customer != m_customers.end(); ++customer) 
	{
		if (customer->GetID() == customerID) 
		{
			return customer;
		}
	}

	return m_customers.end();
}

