#include "pch.h"
#include "CppUnitTest.h"

#include <exception>
#include "Accounts/CurrentAccount/CurrentAccount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(CurrentAccountTest)
	{
	public:
		TEST_METHOD(TestCurrentAccountAccountTypeIsCurrentAccount)
		{
			std::string ownerName = "peter";
			Account* currentAccount = new CurrentAccount(ownerName);

			Assert::AreEqual(static_cast<int>(AccountType::CurrentAccount), currentAccount->GetAccountType());

			delete currentAccount;
		}

		TEST_METHOD(TestDepositingEqualsTheDepositAmmount)
		{
			std::string ownerName = "peter";
			double depositAmmount = 100.0;
			Account* currentAccount = new CurrentAccount(ownerName);

			currentAccount->Deposit(depositAmmount);

			Assert::AreEqual(depositAmmount, currentAccount->GetBalance());

			delete currentAccount;
		}
	};

}
