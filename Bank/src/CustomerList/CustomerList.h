#pragma once

#ifndef CUSTOMER_LIST_H
#define CUSTOMER_LIST_H

#include "Customers/Customer.h"
#include <vector>


class CustomerList
{
public:
	CustomerList() = default;
	CustomerList(const CustomerList& other) = default;
	~CustomerList() = default;
	CustomerList& operator=(const CustomerList& other) = default;

	void PrintCustomers() const;
	void PrintCustomerDetails(const std::string& customerID) const;

	void AddCustomer(const std::string& customerName, const std::string& customerAddress);
	void DeleteCustomer(const std::string& customerID);
	void Clear();

	bool Empty() const;
	bool IsCustomerRegistered(std::vector<Customer>::const_iterator customerIt) const;
	bool CustomerDoesNotExist(const std::string& customerID) const;
	std::vector<Customer>::const_iterator GetCustomerPosition(const std::string& customerID) const;

private:
	std::vector<Customer> m_customers;
};


#endif 
