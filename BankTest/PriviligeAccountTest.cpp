#include "pch.h"
#include "CppUnitTest.h"

#include <exception>
#include "Accounts/PriviligeAccount/PrivilegeAccount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(PriviligeAccountTest)
	{
	public:
		TEST_METHOD(TestPriviligeAccountAccountTypeIsPriviligeAccount)
		{
			std::string ownerName = "peter";
			Account* priviligeAccount = new PrivilegeAccount(ownerName);

			Assert::AreEqual(static_cast<int>(AccountType::PrivileAccount), priviligeAccount->GetAccountType());

			delete priviligeAccount;
		}

		TEST_METHOD(TestDepositingInEmptyBalanceEqualsTheDepositAmmount)
		{
			std::string ownerName = "peter";
			double depositAmmount = 200.0;
			Account* priviligeAccount = new PrivilegeAccount(ownerName);

			priviligeAccount->Deposit(depositAmmount);

			Assert::AreEqual(depositAmmount, priviligeAccount->GetBalance());

			delete priviligeAccount;
		}

		TEST_METHOD(TestWithrawAfterDepositSameAmmountEqualsZero)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* priviligeAccount = new PrivilegeAccount(ownerName);

			priviligeAccount->Deposit(moneyAmmount);

			priviligeAccount->Withdraw(moneyAmmount);

			Assert::AreEqual(0.0, priviligeAccount->GetBalance());

			delete priviligeAccount;
		}

		TEST_METHOD(TestWithrawWithEmptyBalanceThrowsException)
		{
			std::string ownerName = "peter";
			double moneyAmmount = 100.0;
			Account* priviligeAccount = new PrivilegeAccount(ownerName);

			auto method = [&]() { priviligeAccount->Withdraw(moneyAmmount); };

			Assert::ExpectException<std::exception>(method);

			delete priviligeAccount;
		}

		TEST_METHOD(TestWithrawMoreThanAvailableBalanceThrowsException)
		{
			std::string ownerName = "peter";
			double initialDeposit = 100.0;
			double overdraft = initialDeposit / 2;

			double moneyAmmount = 2 * initialDeposit;

			Account* priviligeAccount = new PrivilegeAccount(ownerName, initialDeposit, overdraft);

			auto method = [&]() { priviligeAccount->Withdraw(moneyAmmount); };

			Assert::ExpectException<std::exception>(method);

			delete priviligeAccount;
		}

		TEST_METHOD(TestWithrawMoreThanAvailableBalanceIsCoveredByOverdraft)
		{
			std::string ownerName = "peter";
			double initialDeposit = 100.0;
			double overdraft = 2 * initialDeposit;

			// transactions equal to the (initial deposit + overdraft) are guaranteed to be successful
			// and it will leave the balance at zero
			double moneyAmmount = initialDeposit + overdraft;

			Account* priviligeAccount = new PrivilegeAccount(ownerName, initialDeposit, overdraft);

			priviligeAccount->Withdraw(moneyAmmount);

			Assert::AreEqual(0.0, priviligeAccount->GetBalance());

			delete priviligeAccount;
		}

	};

}
