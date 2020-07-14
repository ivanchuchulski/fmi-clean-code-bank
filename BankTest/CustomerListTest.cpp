#include "pch.h"
#include "CppUnitTest.h"

#include "Customers/Customer.h"
#include "CustomerList/CustomerList.h"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BankTest
{
	TEST_CLASS(CustomerListTest)
	{
	public:
		TEST_METHOD(TestDeletingANonExistingCustomerThrowsException)
		{
			CustomerList customerList;
			std::string customerID = "non-existing-id";

			// a method wrapper is needed, because Assert::ExpectException accepts method signature with no arguments and returning void
			// so we can use a lamba, name it and pass it to the Assert
			auto methodWrapper = [&]() {customerList.DeleteCustomer(customerID); };
			
			Assert::ExpectException<std::exception>(methodWrapper);
		}

	};

}
