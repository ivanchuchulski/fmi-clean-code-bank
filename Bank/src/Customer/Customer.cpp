#include "Customer/Customer.h"

//static members initialization
unsigned int Customer::ID_COUNTER = 0;
const std::string Customer::ID_PREFIX= "#ID#";

Customer::Customer()
	:	id(Utils::GenerateNumberedStringWithPrefix(ID_PREFIX, ID_COUNTER)),
		name(),
		address()
{
	ID_COUNTER++;
}

Customer::Customer(const std::string& name, const std::string& address)
	:	id(Utils::GenerateNumberedStringWithPrefix(ID_PREFIX, ID_COUNTER)),
		name(name),
		address(address)
{
	ID_COUNTER++;
}

void Customer::SetName(const std::string & name)
{
	this->name = name;
}

void Customer::SetAddress(const std::string & address)
{
	this->address = address;
}

const std::string Customer::GetID() const
{
	return std::string(id);
}

const std::string Customer::GetName() const
{
	return std::string(name);
}

const std::string Customer::GetAddress() const
{
	return std::string(address);
}


void Customer::DisplayCustomerInfo() const
{
	std::cout << (*this);
}

bool Customer::Equals(const Customer& other) const
{
	return name == other.name;
}

// friend methods
std::ostream& operator<<(std::ostream& outStream, const Customer& customer)
{
	outStream << "customer name : " << customer.name 
		<< "\ncustomer ID : " << customer.id 
		<< "\naddress : " << customer.address << '\n';

	return outStream;
}
