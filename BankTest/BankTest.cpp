#include "pch.h"
#include "CppUnitTest.h"

#include "Bank/Bank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(BankTest)
	{
	public:
		TEST_METHOD(TestBankGetBankName)
		{
			std::string bankName = "fib";
			std::string bankAddress = "sofia";
			Bank bank = Bank(bankName, bankAddress);

			Assert::AreEqual(bankName, bank.GetName());
		}

		TEST_METHOD(TestDeletingANonExistingCustomerThrowsException)
		{
			std::string customerName = "peter";
			Bank bank = Bank();

			auto methodWrapper = [&]() { bank.DeleteCustomer(customerName); };

			Assert::ExpectException<std::exception>(methodWrapper);
		}

		TEST_METHOD(TestDeletingAnExistingCustomer)
		{
			std::string customerName = "peter";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			Bank bank = Bank();

			bank.AddCustomer(&customer);
			bank.DeleteCustomer(customerName);

			Assert::IsTrue(bank.NoRegisteredCustomers());
		}

		TEST_METHOD(TestAddingNonExistingCustomerAddsCustomerToRegisteredCustomers)
		{
			std::string customerName = "peter";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			Bank bank = Bank();

			bank.AddCustomer(&customer);

			Assert::IsFalse(bank.NoRegisteredCustomers());
		}

		TEST_METHOD(TestAddingNonExistingCustomerEqualsTheAddedOne)
		{
			std::string customerName = "peter";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			Bank bank = Bank();

			bank.AddCustomer(&customer);

			const Customer& addedCustomer = bank.GetCustomerByName(customer.GetName());

			Assert::IsTrue(customer.Equals(addedCustomer));
		}

		TEST_METHOD(TestAddingAlreadyExistingCustomerThrowsException)
		{
			std::string customerName = "peter";
			std::string customerAddress = "sofia";
			Customer customer = Customer(customerName, customerAddress);
			Bank bank = Bank();

			bank.AddCustomer(&customer);

			auto methodWrapper = [&]() {bank.AddCustomer(&customer); };

			Assert::ExpectException<std::exception>(methodWrapper);
		}
	};
}
