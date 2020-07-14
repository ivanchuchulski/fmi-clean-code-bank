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
	};
}
