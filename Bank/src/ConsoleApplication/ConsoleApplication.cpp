#include "ConsoleApplication/ConsoleApplication.h"
#include "AccountFactory/AccountFactory.h"
#include <stdlib.h>


ConsoleApplication::ConsoleApplication()
	:	consoleInterface(),
		bank("Bright finances", "Sofia"),
        isApplicationRunning(true)
{}

ConsoleApplication::~ConsoleApplication()
{}

void ConsoleApplication::Start()
{
    do
    {
        DisplayMenu();

        OptionCode option = GetOptionFromConsole();
        
        DispatchAndExecuteOption(option);

    } while (isApplicationRunning);

    std::cout << "exiting...\n";
}

void ConsoleApplication::DisplayMenu()
{
    consoleInterface.DisplayMenu();
}

OptionCode ConsoleApplication::GetOptionFromConsole()
{
    try
    {
        return consoleInterface.GetOption();
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::DispatchAndExecuteOption(OptionCode& optionCode)
{
    switch (optionCode)
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
        DisplayMenu();
        break;

    case OptionCode::Quit:
        StopApplication();
        break;

    default:
        consoleInterface.DisplayErrorMessege("error : wrong command, please try again\n");
        break;
    }
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
    try
    {
        std::string customerID = consoleInterface.InputCustomerID();

        const Customer& customer = bank.GetCustomerByID(customerID);

        consoleInterface.PrintCustomerDetails(customer);

        for (const Account* const account : bank.GetAccountList())
        {
            if (account->AccountOwnedByCustomer(customer.GetID()))
            {
                consoleInterface.PrintAccountDetails(account);
            }
        }
    }
    catch (const std::exception & exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
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
    ListCustomers();
    ListAccounts();
}

void ConsoleApplication::Withdraw()
{
    try
    {
        std::string accountIBAN;
        double withdrawAmmount;

        consoleInterface.DisplaySuccessMessege("enter account IBAN to withdraw from\n");

        accountIBAN = consoleInterface.InputAccountIBAN();
        withdrawAmmount = consoleInterface.InputMoneyAmmount();

        bank.WithdrawFromAccount(accountIBAN, withdrawAmmount);

        consoleInterface.DisplaySuccessMessege("account withraw success\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::Deposit()
{
    try
    {
        std::string accountIBAN;
        double depositAmmount;

        consoleInterface.DisplaySuccessMessege("enter account IBAN to deposit\n");

        accountIBAN = consoleInterface.InputAccountIBAN();
        depositAmmount = consoleInterface.InputMoneyAmmount();

        bank.DepositToAccount(accountIBAN, depositAmmount);

        consoleInterface.DisplaySuccessMessege("account deposit success\n");
    }
    catch (const std::exception & exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::Transfer()
{
    try
    {
        std::string depositerIBAN;
        std::string withdrawerIBAN;
        double transferAmmount;

        consoleInterface.DisplaySuccessMessege("account transfer\n");

        consoleInterface.DisplaySuccessMessege("enter account IBANs to withdraw from, to deposit to and the money ammount\n");

        withdrawerIBAN = consoleInterface.InputAccountIBAN();
        depositerIBAN = consoleInterface.InputAccountIBAN();
        transferAmmount = consoleInterface.InputMoneyAmmount();

        bank.Transfer(withdrawerIBAN, depositerIBAN, transferAmmount);

        consoleInterface.DisplaySuccessMessege("accounts transfer success\n");
    }
    catch (const std::exception & exception)
    {
        consoleInterface.DisplayErrorMessege(exception.what());
    }
}

void ConsoleApplication::StopApplication()
{
    isApplicationRunning = false;
}