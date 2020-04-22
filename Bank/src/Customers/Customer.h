#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

#include "Utils/Utils.h"

class Customer 
{
public:
	Customer() = default;
	Customer(const Customer& other) = default;
	Customer(const std::string& name, const std::string& address);

	~Customer() = default;

	Customer& operator=(const Customer& other) = default;

	// setters
	void SetID(const std::string& id);
	void SetName(const std::string& name);
	void SetAddress(const std::string& address);

	// getters
	const std::string GetID() const;
	const std::string GetName() const;
	const std::string GetAddress() const;

	void DisplayCustomerInfo() const;

	Customer inputCustomer();

	// friend methods
	friend std::ostream& operator<<(std::ostream& outStr, const Customer& someCustomer);

private:
	static unsigned int M_ID_COUNTER;
	static const std::string M_ID_PREFIX;

private:
	std::string m_id;
	std::string m_name;
	std::string m_address;
};

#endif // !CUSTOMER_H