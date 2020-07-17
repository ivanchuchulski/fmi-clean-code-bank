#pragma once

#ifndef CUSTOMER_LIST_H
#define CUSTOMER_LIST_H

#include "Customer/Customer.h"
#include "Account/Account.h"
#include "CustomerListIterators/CustomerListIterators.h"
#include <vector>

class CustomerList
{
public:
	CustomerList() = default;
	CustomerList(const CustomerList& other) = default;
	~CustomerList() = default;
	CustomerList& operator=(const CustomerList& other) = default;

	void AddCustomer(Customer* customer);
	void DeleteCustomer(const std::string& customerName);
	void Clear();

	bool Empty() const;
	bool CustomerExists(const std::string& customerName) const;

	Customer& GetCustomer(const std::string& customerName);
	const Customer& GetCustomer(const std::string& customerName) const;

	customer_iterator begin();
	customer_iterator end();
	customer_const_iterator begin() const;
	customer_const_iterator end() const;
	
private:
	customer_iterator GetCustomerPosition(const std::string& customerName);
	customer_const_iterator GetCustomerPosition(const std::string& customerName) const;

private:
	std::vector<Customer> m_customers;
};


#endif 
