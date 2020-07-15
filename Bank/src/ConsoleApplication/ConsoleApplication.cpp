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
        consoleInterface.DisplayErrorMessage(exception.what());
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
        consoleInterface.DisplayErrorMessage("error : wrong command, please try again\n");
        break;
    }
}

void ConsoleApplication::AddCustomer()
{
    try
    {
        std::string customerAddress;
        std::string customerName;

        consoleInterface.DisplayMessage("please provide customer name and address to add\n");

        consoleInterface.DisplayMessage("enter customer name : ");
        customerName = consoleInterface.InputString();

        consoleInterface.DisplayMessage("enter customer address: ");
        customerAddress = consoleInterface.InputString();

        Customer* customer = new Customer(customerName, customerAddress);
        
        bank.AddCustomer(customer);

        consoleInterface.DisplayMessage("success : customer added\n");

        delete customer;
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::DeleteCustomer()
{
    try
    {
        std::string customerName;

        consoleInterface.DisplayMessage("please provide the customer's ID to remove\n");

        consoleInterface.DisplayMessage("enter customer name : ");
        customerName = consoleInterface.InputString();

        bank.DeleteCustomer(customerName);

        consoleInterface.DisplayMessage("sucess : customer removed\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::AddAccount()
{
    try
    {
        std::string accountOnwerName;
        AccountType accountType;

        consoleInterface.DisplayMessage("please provide customer name for account's owner and select the type of the account to add\n");

        consoleInterface.DisplayMessage("enter owner name: ");
        accountOnwerName = consoleInterface.InputString();

        consoleInterface.PrintSupportedAccountTypes();

        consoleInterface.DisplayMessage("enter account type : ");
        accountType = consoleInterface.InputAccountType();

        Account* account = AccountFactory::CreateAccount(accountType, accountOnwerName);

        bank.AddAccount(account);

        consoleInterface.DisplayMessage("success : account addition success\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::DeleteAccount()
{
    try
    {
        std::string accountIBAN;

        consoleInterface.DisplayMessage("please provide the account's IBAN to remove\n");

        consoleInterface.DisplayMessage("enter account IBAN : ");
        accountIBAN = consoleInterface.InputString();

        bank.DeleteAccount(accountIBAN);

        consoleInterface.DisplayMessage("success : account removed\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::ListCustomers()
{
    try
    {
        consoleInterface.DisplayMessage("listing bank customers details\n");

        for (const Customer& customer : bank.GetCustomerList())
        {
            consoleInterface.PrintCustomerDetails(customer);
        }
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::ListAllCustomersAccount()
{
    try
    {
        std::string customerName;

        consoleInterface.DisplayMessage("enter customer name to list his accounts\n");

        consoleInterface.DisplayMessage("enter customer name : ");
        customerName = consoleInterface.InputString();

        const Customer& customer = bank.GetCustomerByName(customerName);

        consoleInterface.DisplayMessage("listing customer details\n");
        consoleInterface.PrintCustomerDetails(customer);

        consoleInterface.DisplayMessage("listing customer's accounts details\n");
        for (const Account* const account : bank.GetAccountList())
        {
            if (account->AccountOwnedByCustomer(customer.GetName()))
            {
                consoleInterface.PrintAccountDetails(account);
            }
        }
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::ListAccounts()
{
    try
    {
        consoleInterface.DisplayMessage("listing bank accounts\n");

        for (const Account* const account : bank.GetAccountList())
        {
            consoleInterface.PrintAccountDetails(account);
        }
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
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

        consoleInterface.DisplayMessage("please provide the account's IBAN to withdraw from and the withdraw ammount\n");

        consoleInterface.DisplayMessage("enter account IBAN : ");
        accountIBAN = consoleInterface.InputString();

        consoleInterface.DisplayMessage("enter withdraw ammount : ");
        withdrawAmmount = consoleInterface.InputMoneyAmmount();

        bank.WithdrawFromAccount(accountIBAN, withdrawAmmount);

        consoleInterface.DisplayMessage("success : account withraw\n");
    }
    catch (const std::exception& exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::Deposit()
{
    try
    {
        std::string accountIBAN;
        double depositAmmount;

        consoleInterface.DisplayMessage("please provide the account's IBAN to deposit to and the deposit ammount\n");

        consoleInterface.DisplayMessage("enter account IBAN : ");
        accountIBAN = consoleInterface.InputString();

        consoleInterface.DisplayMessage("enter deposit ammount : ");
        depositAmmount = consoleInterface.InputMoneyAmmount();

        bank.DepositToAccount(accountIBAN, depositAmmount);

        consoleInterface.DisplayMessage("success : account deposit\n");
    }
    catch (const std::exception & exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::Transfer()
{
    try
    {
        std::string depositerIBAN;
        std::string withdrawerIBAN;
        double transferAmmount;

        consoleInterface.DisplayMessage("enter account IBAN to withdraw from, account IBAN to deposit to and the money ammount\n");

        consoleInterface.DisplayMessage("enter account IBAN to withdraw from: ");
        withdrawerIBAN = consoleInterface.InputString();

        consoleInterface.DisplayMessage("enter account IBAN to deposit to : ");
        depositerIBAN = consoleInterface.InputString();

        consoleInterface.DisplayMessage("enter money ammount : ");
        transferAmmount = consoleInterface.InputMoneyAmmount();

        bank.Transfer(withdrawerIBAN, depositerIBAN, transferAmmount);

        consoleInterface.DisplayMessage("success : account transfer\n");
    }
    catch (const std::exception & exception)
    {
        consoleInterface.DisplayErrorMessage(exception.what());
    }
}

void ConsoleApplication::StopApplication()
{
    isApplicationRunning = false;
}