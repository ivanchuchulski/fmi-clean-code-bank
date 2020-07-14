#include "pch.h"
#include "CppUnitTest.h"

#include <exception>
#include "Accounts/CurrentAccount/CurrentAccount.h"

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

}
