#include "CustomerList/CustomerList.h"
#include "CustomerListIterators/CustomerListIterators.h"
#include <exception>

void CustomerList::AddCustomer(Customer* customer)
{
	if (CustomerExists(customer->GetName()))
	{
		throw std::exception("customer addition failed : customer is already registered\n");
	}

	customers.emplace_back(*customer);
}

void CustomerList::DeleteCustomer(const std::string& customerName)
{
	auto customerPosition = GetCustomerPosition(customerName);

	if (customerPosition == end())
	{
		throw std::exception("customer removal failed : customer with the given name is not registered\n");
	}

	customers.erase(customerPosition);
}

void CustomerList::Clear()
{
	customers.clear();
}

bool CustomerList::Empty() const
{
	return customers.empty();
}

bool CustomerList::CustomerExists(const std::string& customerName) const
{
	auto customerPosition = GetCustomerPosition(customerName);

	return customerPosition != customers.end();
}

Customer& CustomerList::GetCustomer(const std::string& customerName)
{
	auto customerPosition = GetCustomerPosition(customerName);

	if (customerPosition == end())
	{
		throw std::exception("error : such customer is not registered\n");
	}

	return *customerPosition;
}

const Customer& CustomerList::GetCustomer(const std::string& customerName) const
{
	auto customerPosition = GetCustomerPosition(customerName);

	if (customerPosition == end())
	{
		throw std::exception("error : such customer is not registered\n");
	}

	return *customerPosition;
}

customer_iterator CustomerList::begin()
{
	return customers.begin();
}

customer_iterator CustomerList::end()
{
	return customers.end();
}

customer_const_iterator CustomerList::begin() const
{
	return customers.begin();
}

customer_const_iterator CustomerList::end() const
{
	return customers.end();
}

// private methods
customer_iterator CustomerList::GetCustomerPosition(const std::string& customerName)
{
	return std::find_if(begin(), end(), [&](const Customer& customer) { return customer.GetName() == customerName; });
}

customer_const_iterator CustomerList::GetCustomerPosition(const std::string& customerName) const
{
	return std::find_if(begin(), end(), [&](const Customer& customer) { return customer.GetName() == customerName; });
}

