#include "pch.h"
#include "CppUnitTest.h"

#include "Customers/Customer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
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
