#include "pch.h"
#include "CppUnitTest.h"

#include "Customer/Customer.h"
#include "CustomerList/CustomerList.h"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(CustomerListTest)
	{
	public:
		TEST_METHOD(TestDeletingANonExistingCustomerThrowsException)
		{
			std::string customerName = "peter";
			CustomerList customerList;

			// a method wrapper is needed, because Assert::ExpectException accepts method signature with no arguments and returning void
			// so we can use a lamba, name it and pass it to the Assert
			auto methodWrapper = [&]() {customerList.DeleteCustomer(customerName); };
			
			Assert::ExpectException<std::exception>(methodWrapper, L"DeleteCustomer() didn't throw exception");
		}

		TEST_METHOD(TestDeletingAnExistingCustomer)
		{
			std::string customerName = "george";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			CustomerList customerList = CustomerList();

			customerList.AddCustomer(&customer);
			customerList.DeleteCustomer(customerName);

			Assert::AreEqual(true, customerList.Empty());
		}

		TEST_METHOD(TestAddingNonExistingCustomer)
		{
			std::string customerName = "george";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			CustomerList customerList = CustomerList();

			customerList.AddCustomer(&customer);

			Assert::IsTrue(customerList.CustomerExists(customer.GetName()));
		}

		TEST_METHOD(TestAddingNonExistingCustomerEqualsTheAddedOne)
		{
			std::string customerName = "george";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			CustomerList customerList = CustomerList();

			customerList.AddCustomer(&customer);

			const Customer& addedCustomer = customerList.GetCustomer(customer.GetName());
			Assert::IsTrue(customer.Equals(addedCustomer));
		}

		TEST_METHOD(TestAddingAlreadyExistingCustomerThrowsException)
		{
			std::string customerName = "george";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			CustomerList customerList = CustomerList();

			customerList.AddCustomer(&customer);

			auto methodWrapper = [&]() {customerList.AddCustomer(&customer); };

			Assert::ExpectException<std::exception>(methodWrapper, L"AddCustomer() didn't throw exception");
		}

		TEST_METHOD(TestClearingCustomerList)
		{
			Customer customerOne = Customer("ivan", "sofia");
			Customer customerTwo = Customer("dragan", "sofia");
			CustomerList customerList = CustomerList();

			customerList.AddCustomer(&customerOne);
			customerList.AddCustomer(&customerTwo);

			customerList.Clear();
			
			Assert::IsTrue(customerList.Empty());
		}
	};

}
