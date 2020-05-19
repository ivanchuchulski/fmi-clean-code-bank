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