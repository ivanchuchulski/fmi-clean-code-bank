#include "pch.h"
#include "CppUnitTest.h"

#include <exception>
#include "Accounts/SavingsAccount/SavingsAccount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(SavingsAccountTest)
	{
	public:
		TEST_METHOD(TestSavingsAccountAccountTypeIsSavingsAccount)
		{
			std::string ownerName = "peter";
			Account* savingsAccount = new SavingsAccount(ownerName);

			Assert::AreEqual(static_cast<int>(AccountType::SavingsAccount), savingsAccount->GetAccountType());

			delete savingsAccount;
		}

		TEST_METHOD(TestDepositingEqualsTheDepositAmmount)
		{
			std::string ownerName = "peter";
			double depositAmmount = 300.0;
			Account* savingsAccount = new SavingsAccount(ownerName);

			savingsAccount->Deposit(depositAmmount);

			Assert::AreEqual(depositAmmount, savingsAccount->GetBalance());

			delete savingsAccount;
		}
	};

}
