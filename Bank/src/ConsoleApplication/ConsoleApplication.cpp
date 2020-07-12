#include "ConsoleApplication/ConsoleApplication.h"
#include "AccountFactory/AccountFactory.h"
#include <stdlib.h>


ConsoleApplication::ConsoleApplication()
	:	consoleInterface(),
		bank("Bright finances", "Sofia")
{}

ConsoleApplication::~ConsoleApplication()
{
}

void ConsoleApplication::Start()
{
    bool running = true;

    do
    {
        consoleInterface.DisplayMenu();

        OptionCode option = consoleInterface.GetOption();

        switch (option)
        {
            case OptionCode::AddCustomer:
                AddCustomer();
                break;

            case OptionCode::DeleteCustomer:
                DeleteCustomer();
                break;

            case OptionCode::AddAccount:
                AddAccount();
                break;

            case OptionCode::DeleteAccount:
                DeleteAccount();
                break;

            case OptionCode::ListCustomers:
                ListCustomers();
                break;

            case OptionCode::ListAllCustomersAccount:
                ListAllCustomersAccount();
                break;

            case OptionCode::ListAccounts:
                ListAccounts();
                break;

            case OptionCode::BankInformation:
                BankInformation();
                break;

            case OptionCode::Withdraw:
                Withdraw();
                break;

            case OptionCode::Deposit:
                Deposit();
                break;

            case OptionCode::Transfer:
                Transfer();
                break;

            case OptionCode::Help:
                consoleInterface.DisplayMenu();
                break;

            case OptionCode::Quit:
                running = false;
                break;

            default:
                consoleInterface.DisplayErrorMessege("error, wrong command, please try again\n");
                break;
        }

    } while (running);

    std::cout << "exiting...\n";
}

void ConsoleApplication::AddCustomer()
{
    try
    {
        std::string customerAddress = consoleInterface.InputCustomerAddress();
        std::string customerName = consoleInterface.InputCustomerName();
        Customer* customer = new Customer(customerName, customerAddress);

        bank.AddCustomer(customer);

        consoleInterface.DisplaySuccessMessege("customer addition success\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::DeleteCustomer()
{
    try
    {
        std::string customerID = consoleInterface.InputCustomerID();

        bank.DeleteCustomer(customerID);

        consoleInterface.DisplaySuccessMessege("customer removal success!\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::AddAccount()
{
    try
    {
        std::string accountOwnerID = consoleInterface.InputCustomerID();
        consoleInterface.PrintSupportedAccountTypes();
        AccountType accountType = consoleInterface.InputAccountType();

        Account* account = AccountFactory::CreateAccount(accountType, accountOwnerID);

        bank.AddAccount(account);

        consoleInterface.DisplaySuccessMessege("account addition success\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::DeleteAccount()
{
    try
    {
        std::string accountIBAN;
        accountIBAN = consoleInterface.InputAccountIBAN();

        bank.DeleteAccount(accountIBAN);

        consoleInterface.DisplaySuccessMessege("account removal success!\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::ListCustomers()
{
    try
    {
        for (const Customer& customer : bank.GetCustomerList())
        {
            consoleInterface.PrintCustomerDetails(customer);
        }
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::ListAllCustomersAccount()
{
}

void ConsoleApplication::ListAccounts()
{
    try
    {
        for (const Account* const account : bank.GetAccountList())
        {
            consoleInterface.PrintAccountDetails(account);
        }
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }

}

void ConsoleApplication::BankInformation()
{
}

void ConsoleApplication::Withdraw()
{
}

void ConsoleApplication::Deposit()
{
}

void ConsoleApplication::Transfer()
{
}
