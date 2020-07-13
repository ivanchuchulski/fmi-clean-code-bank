#pragma once

#ifndef CUSTOMER_LIST_H
#define CUSTOMER_LIST_H

#include "Customers/Customer.h"
#include "Account/Account.h"
#include <vector>
#include "CustomerListIterators/CustomerListIterators.h"

class CustomerList
{
public:
	CustomerList() = default;
	CustomerList(const CustomerList& other) = default;
	~CustomerList() = default;
	CustomerList& operator=(const CustomerList& other) = default;

	void AddCustomer(Customer* customer);
	void DeleteCustomer(const std::string& customerID);
	void Clear();

	bool Empty() const;
	bool CustomerDoesNotExist(const std::string& customerID) const;

	const Customer& GetCustomerByID(const std::string& customerID) const;

	customer_iterator begin();
	customer_iterator end();
	customer_const_iterator begin() const;
	customer_const_iterator end() const;
	
private:
	customer_const_iterator GetCustomerPosition(const std::string& customerID) const;

private:
	std::vector<Customer> m_customers;
};


#endif 
