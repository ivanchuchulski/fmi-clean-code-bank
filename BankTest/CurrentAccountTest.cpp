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

		TEST_METHOD(TestDepositingInEmptyBalanceEqualsTheDepositAmmount)
		{
			std::string ownerName = "peter";
			double depositAmmount = 100.0;
			Account* currentAccount = new CurrentAccount(ownerName);

			currentAccount->Deposit(depositAmmount);

			Assert::AreEqual(depositAmmount, currentAccount->GetBalance());

			delete currentAccount;
		}

		TEST_METHOD(TestWithrawAfterDepositSameAmmountEqualsZero)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* currentAccount = new CurrentAccount(ownerName);

			currentAccount->Deposit(moneyAmmount);

			currentAccount->Withdraw(moneyAmmount);

			Assert::AreEqual(0.0, currentAccount->GetBalance());

			delete currentAccount;
		}

		TEST_METHOD(TestWithrawWithEmptyBalanceThrowsException)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* currentAccount = new CurrentAccount(ownerName);

			auto method = [&]() { currentAccount->Withdraw(moneyAmmount); };

			Assert::ExpectException<std::exception>(method);

			delete currentAccount;
		}

		TEST_METHOD(TestWithrawMoreThanAvailableBalanceThrowsException)
		{
			std::string ownerName = "peter";
			double initialDeposit = 100.0;
			double moneyAmmount = 2 * initialDeposit;
			Account* currentAccount = new CurrentAccount(ownerName, initialDeposit);

			auto method = [&]() { currentAccount->Withdraw(moneyAmmount); };

			Assert::ExpectException<std::exception>(method);

			delete currentAccount;
		}
	};

}
