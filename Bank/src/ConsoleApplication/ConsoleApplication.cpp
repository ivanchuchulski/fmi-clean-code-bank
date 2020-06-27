#include "ConsoleApplication/ConsoleApplication.h"


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
                break;
        }

    } while (running);

    std::cout << "exiting...\n";
}

Customer* ConsoleApplication::InputCustomerDetails()
{
    return nullptr;
}

void ConsoleApplication::AddCustomer()
{
    std::string customerAddress = consoleInterface.InputCustomerAddress();
    std::string customerName = consoleInterface.InputCustomerName();

    Customer* customer = new Customer(customerName, customerAddress);

    bank.AddCustomer(customer);
}

void ConsoleApplication::DeleteCustomer()
{
    try
    {
        std::string customerID = consoleInterface.InputCustomerID();

        bank.DeleteCustomer(customerID);
    }
    catch (const std::exception& exception)
    {
        consoleInterface.PrintException(exception);
    }

}

void ConsoleApplication::AddAccount()
{
}

void ConsoleApplication::DeleteAccount()
{
}

void ConsoleApplication::ListCustomers()
{
    bank.ListCustomers();
}

void ConsoleApplication::ListAllCustomersAccount()
{
}


void ConsoleApplication::ListAccounts()
{
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
