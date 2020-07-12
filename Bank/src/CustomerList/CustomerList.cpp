#include "CustomerList/CustomerList.h"
#include "CustomerListIterators/CustomerListIterators.h"

#include <exception>


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

void CustomerList::AddCustomer(Customer* customer)
{
	m_customers.emplace_back(*customer);
}

void CustomerList::DeleteCustomer(const std::string& customerID)
{
	try
	{
		auto customerToRemovePosition = GetCustomerPosition(customerID);

		m_customers.erase(customerToRemovePosition);
	}
	catch (const std::exception&)
	{
		throw;
	}
}

void CustomerList::Clear()
{
	m_customers.clear();
}

bool CustomerList::Empty() const
{
	return m_customers.empty();
}

bool CustomerList::CustomerDoesNotExist(const std::string& customerID) const
{
	auto customerPosition = GetCustomerPosition(customerID);

	return customerPosition == m_customers.end();
}

customer_iterator CustomerList::begin()
{
	return m_customers.begin();
}

customer_iterator CustomerList::end()
{
	return m_customers.end();
}

customer_const_iterator CustomerList::begin() const
{
	return m_customers.begin();
}

customer_const_iterator CustomerList::end() const
{
	return m_customers.end();
}

// private helpers
std::vector<Customer>::const_iterator CustomerList::GetCustomerPosition(const std::string& customerID) const
{
	for (auto customer = m_customers.begin(); customer != m_customers.end(); ++customer) 
	{
		if (customer->GetID() == customerID) 
		{
			return customer;
		}
	}

	throw std::exception("error : customer does not exist\n");
}

