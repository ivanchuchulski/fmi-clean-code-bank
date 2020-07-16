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

		TEST_METHOD(TestDepositingInEmptyBalanceEqualsTheDepositAmmount)
		{
			std::string ownerName = "peter";
			double depositAmmount = 100.0;
			Account* savingsAccount = new SavingsAccount(ownerName);

			savingsAccount->Deposit(depositAmmount);

			Assert::AreEqual(depositAmmount, savingsAccount->GetBalance());

			delete savingsAccount;
		}

		TEST_METHOD(TestWithrawAfterDepositSameAmmountEqualsZero)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* savingsAccount = new SavingsAccount(ownerName);

			savingsAccount->Deposit(moneyAmmount);

			savingsAccount->Withdraw(moneyAmmount);

			Assert::AreEqual(0.0, savingsAccount->GetBalance());

			delete savingsAccount;
		}

		TEST_METHOD(TestWithrawWithEmptyBalanceThrowsException)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* savingsAccount = new SavingsAccount(ownerName);

			auto method = [&]() { savingsAccount->Withdraw(moneyAmmount); };

			Assert::ExpectException<std::exception>(method);

			delete savingsAccount;
		}

		TEST_METHOD(TestWithrawMoreThanAvailableBalanceThrowsException)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* savingsAccount = new SavingsAccount(ownerName);
		
			savingsAccount->Deposit(moneyAmmount);

			auto method = [&]() { savingsAccount->Withdraw(2 * moneyAmmount); };

			Assert::ExpectException<std::exception>(method);

			delete savingsAccount;
		}

	};

}
