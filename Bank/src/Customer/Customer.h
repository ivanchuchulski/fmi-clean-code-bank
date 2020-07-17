#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

#include "Utils/Utils.h"

class Customer 
{
public:
	Customer();
	Customer(const Customer& other) = default;
	Customer(const std::string& name, const std::string& address);

	~Customer() = default;

	Customer& operator=(const Customer& other) = default;

	void SetName(const std::string& name);
	void SetAddress(const std::string& address);

	const std::string GetID() const;
	const std::string GetName() const;
	const std::string GetAddress() const;

	void DisplayCustomerInfo() const;

	bool Equals(const Customer& other) const;

	friend std::ostream& operator<<(std::ostream& outStr, const Customer& customer);

private:
	static unsigned int ID_COUNTER;
	static const std::string ID_PREFIX;

private:
	std::string id;
	std::string name;
	std::string address;
};

#endif // !CUSTOMER_H