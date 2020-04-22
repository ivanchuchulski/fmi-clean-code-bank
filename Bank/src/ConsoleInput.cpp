#include "ConsoleInput.h"

Customer ConsoleInput::InputCustomer()
{
	std::string name;
	std::string address;

	std::cout << "enter customer name : ";
	std::getline(std::cin, name);

	std::cout << "enter customer address : ";
	std::getline(std::cin, address);

	return Customer(name, address);
}