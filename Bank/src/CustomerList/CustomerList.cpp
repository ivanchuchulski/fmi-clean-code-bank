#include "CustomerList/CustomerList.h"
#include "CustomerListIterators/CustomerListIterators.h"
#include <exception>

void CustomerList::AddCustomer(Customer* customer)
{
	m_customers.emplace_back(*customer);
}

void CustomerList::DeleteCustomer(const std::string& customerName)
{
	try
	{
		auto customerPosition = GetCustomerPosition(customerName);

		if (customerPosition == end())
		{
			throw std::exception("error : customer doesn't exist\n");
		}

		m_customers.erase(customerPosition);

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

bool CustomerList::CustomerExists(const std::string& customerName) const
{
	auto customerPosition = GetCustomerPosition(customerName);

	return customerPosition != m_customers.end();
}

const Customer& CustomerList::GetCustomer(const std::string& customerName) const
{
	auto customerPosition = GetCustomerPosition(customerName);

	if (customerPosition == end())
	{
		throw std::exception("error : customer doesn't exist\n");
	}

	return *customerPosition;
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

// private methods
customer_const_iterator CustomerList::GetCustomerPosition(const std::string& customerName) const
{
	for (auto customer = m_customers.begin(); customer != m_customers.end(); ++customer) 
	{
		if (customer->GetName() == customerName)
		{
			return customer;
		}
	}

	return m_customers.end();
}

