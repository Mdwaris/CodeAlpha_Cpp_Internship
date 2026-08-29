#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ACCOUNTS = 100;
const int MAX_TRANSACTIONS = 50;

struct Account
{
    int accountNumber;
    string name;
    string pin;
    double balance;
    string transactions[MAX_TRANSACTIONS];
    int transactionCount;
};

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

int findAccount(int accountNumber)
{
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
            return i;
    }
    return -1;
}

void addTransaction(int index, string transaction)
{
    if (accounts[index].transactionCount < MAX_TRANSACTIONS)
    {
        accounts[index].transactions[accounts[index].transactionCount] = transaction;
        accounts[index].transactionCount++;
    }
}

void createAccount()
{
    if (accountCount >= MAX_ACCOUNTS)
    {
        cout << "\nAccount limit reached.\n";
        return;
    }

    Account newAccount;

    cout << "\n========== CREATE ACCOUNT ==========\n";

    newAccount.accountNumber = 1001 + accountCount;

    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, newAccount.name);

    cout << "Create a 4-digit PIN: ";
    cin >> newAccount.pin;

    newAccount.balance = 0;
    newAccount.transactionCount = 0;

    accounts[accountCount] = newAccount;

    cout << "\nAccount created successfully!\n";
    cout << "Your Account Number is: "
         << newAccount.accountNumber << "\n";

    addTransaction(accountCount, "Account created");

    accountCount++;
}

int login()
{
    int accountNumber;
    string pin;

    cout << "\n============== LOGIN ==============\n";

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    cout << "Enter PIN: ";
    cin >> pin;

    int index = findAccount(accountNumber);

    if (index == -1)
    {
        cout << "\nAccount not found.\n";
        return -1;
    }

    if (accounts[index].pin != pin)
    {
        cout << "\nIncorrect PIN.\n";
        return -1;
    }

    cout << "\nLogin successful!\n";
    cout << "Welcome, " << accounts[index].name << "!\n";

    return index;
}

void deposit(int index)
{
    double amount;

    cout << "\n========== DEPOSIT MONEY ==========\n";
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "\nInvalid amount.\n";
        return;
    }

    accounts[index].balance += amount;

    cout << fixed << setprecision(2);
    cout << "\nDeposit successful!\n";
    cout << "Deposited: Rs. " << amount << "\n";
    cout << "New Balance: Rs. "
         << accounts[index].balance << "\n";

    addTransaction(index, "Deposited Rs. " + to_string(amount));
}

void withdraw(int index)
{
    double amount;

    cout << "\n========== WITHDRAW MONEY ==========\n";
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "\nInvalid amount.\n";
        return;
    }

    if (amount > accounts[index].balance)
    {
        cout << "\nInsufficient balance.\n";
        cout << "Available Balance: Rs. "
             << accounts[index].balance << "\n";
        return;
    }

    accounts[index].balance -= amount;

    cout << fixed << setprecision(2);
    cout << "\nWithdrawal successful!\n";
    cout << "Withdrawn: Rs. " << amount << "\n";
    cout << "Remaining Balance: Rs. "
         << accounts[index].balance << "\n";

    addTransaction(index, "Withdrawn Rs. " + to_string(amount));
}

void balanceEnquiry(int index)
{
    cout << "\n========== BALANCE ENQUIRY ==========\n";

    cout << fixed << setprecision(2);

    cout << "Account Number : "
         << accounts[index].accountNumber << "\n";

    cout << "Account Holder : "
         << accounts[index].name << "\n";

    cout << "Current Balance: Rs. "
         << accounts[index].balance << "\n";
}

void accountDetails(int index)
{
    cout << "\n========== ACCOUNT DETAILS ==========\n";

    cout << "Account Number : "
         << accounts[index].accountNumber << "\n";

    cout << "Account Holder : "
         << accounts[index].name << "\n";

    cout << fixed << setprecision(2);

    cout << "Balance        : Rs. "
         << accounts[index].balance << "\n";
}

void transactionHistory(int index)
{
    cout << "\n========== TRANSACTION HISTORY ==========\n";

    if (accounts[index].transactionCount == 0)
    {
        cout << "No transactions available.\n";
        return;
    }

    for (int i = 0; i < accounts[index].transactionCount; i++)
    {
        cout << i + 1 << ". "
             << accounts[index].transactions[i]
             << "\n";
    }
}

void transferMoney(int senderIndex)
{
    int receiverAccount;
    double amount;

    cout << "\n========== TRANSFER MONEY ==========\n";

    cout << "Enter receiver account number: ";
    cin >> receiverAccount;

    int receiverIndex = findAccount(receiverAccount);

    if (receiverIndex == -1)
    {
        cout << "\nReceiver account not found.\n";
        return;
    }

    if (receiverIndex == senderIndex)
    {
        cout << "\nYou cannot transfer money to your own account.\n";
        return;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "\nInvalid amount.\n";
        return;
    }

    if (amount > accounts[senderIndex].balance)
    {
        cout << "\nInsufficient balance.\n";
        return;
    }

    accounts[senderIndex].balance -= amount;
    accounts[receiverIndex].balance += amount;

    cout << fixed << setprecision(2);

    cout << "\nTransfer successful!\n";
    cout << "Transferred: Rs. " << amount << "\n";
    cout << "Receiver Account: "
         << receiverAccount << "\n";

    addTransaction(
        senderIndex,
        "Transferred Rs. " + to_string(amount) +
        " to Account " + to_string(receiverAccount)
    );

    addTransaction(
        receiverIndex,
        "Received Rs. " + to_string(amount) +
        " from Account " +
        to_string(accounts[senderIndex].accountNumber)
    );
}

void accountMenu(int index)
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "             ACCOUNT MENU\n";
        cout << "========================================\n";

        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Balance Enquiry\n";
        cout << "4. Transfer Money\n";
        cout << "5. Transaction History\n";
        cout << "6. Account Details\n";
        cout << "7. Logout\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                deposit(index);
                break;

            case 2:
                withdraw(index);
                break;

            case 3:
                balanceEnquiry(index);
                break;

            case 4:
                transferMoney(index);
                break;

            case 5:
                transactionHistory(index);
                break;

            case 6:
                accountDetails(index);
                break;

            case 7:
                cout << "\nLogged out successfully.\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 7);
}

int main()
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "          BANKING SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
            {
                if (accountCount == 0)
                {
                    cout << "\nNo accounts available.\n";
                    break;
                }

                int index = login();

                if (index != -1)
                    accountMenu(index);

                break;
            }

            case 3:
                cout << "\nThank you for using the Banking System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
