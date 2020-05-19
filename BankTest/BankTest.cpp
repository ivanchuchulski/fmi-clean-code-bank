#include "pch.h"
#include "CppUnitTest.h"

#include "ConsoleInput.h"
#include "Customers/Customer.h"
#include "Account/Account.h"
#include "Accounts/CurrentAccount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(AccountTest)
	{
	public:
		TEST_METHOD(TestAccountBalance)
		{
			std::string accountID = "123";
			double balance = 100.0;
			Account* account = new CurrentAccount(accountID, balance);

			Assert::AreEqual(100.0, account->GetBalance());
		}

	};

	TEST_CLASS(CustomerTest)
	{
	public:
		TEST_METHOD(TestCustomerGetName)
		{
			std::string name = "boris";
			std::string address = "sofia";
			Customer* customer = new Customer(name, address);

			Assert::AreEqual(name, customer->GetName());
		}
	};
}
