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

		TEST_METHOD(TestDepositingEqualsTheDepositAmmount)
		{
			std::string ownerName = "peter";
			double depositAmmount = 200.0;
			Account* priviligeAccount = new PrivilegeAccount(ownerName);

			priviligeAccount->Deposit(depositAmmount);

			Assert::AreEqual(depositAmmount, priviligeAccount->GetBalance());

			delete priviligeAccount;
		}
	};

}
