#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

struct User
{
    string name;
    string username;
    string email;
    string mobile;
    string password;
};

vector<User> users;

int registration()
{
    User newUser;

    cout << "\n========== REGISTRATION ==========\n";

    cout << "Enter full name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newUser.name);

    cout << "Enter username: ";
    cin >> newUser.username;

    for (const User& user : users)
    {
        if (user.username == newUser.username)
        {
            cout << "Username already exists.\n";
            return 0;
        }
    }

    cout << "Enter email: ";
    cin >> newUser.email;

    cout << "Enter mobile number: ";
    cin >> newUser.mobile;

    cout << "Create password: ";
    cin >> newUser.password;

    string confirmPassword;

    cout << "Confirm password: ";
    cin >> confirmPassword;

    if (newUser.password != confirmPassword)
    {
        cout << "Passwords do not match.\n";
        return 0;
    }

    srand(time(0));

    int otp = 100000 + rand() % 900000;

    cout << "\nYour OTP is: " << otp << endl;

    int enteredOTP;

    cout << "Enter OTP: ";
    cin >> enteredOTP;

    if (enteredOTP != otp)
    {
        cout << "Invalid OTP.\n";
        return 0;
    }

    users.push_back(newUser);

    cout << "\nRegistration successful!\n";

    return 1;
}

int login()
{
    string username, password;
    cout<<"\n==========LOGIN========\n";
    cout<<"Enter username: ";
    cin>> username;

    cout<<"Enter passwrod: ";
    cin>> password;
    for(const User& user : users)
    {
        if(user.username == username && user.password == password)
        {
            cout << "\nLogin successfull!\n";
            cout << "Welcome," <<user.name<<"!\n";
            return 1;
        }
    }
    cout << "\nInvalid username or password.\n";
    return 0;
}

int main()
{
    int choice;
    while(true)

    
    {
        cout << "\n========== LOGIN & REGISTRATION SYSTEM ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice == 1)
        {
            registration(); 
        }
        else if (choice == 2)
        {
            login();

        }
        else if(choice == 3)
        {
            cout <<"\nThank you!\n";
            break;
        }
        else
        {
            cout<<"\nInvalid choice. Try again\n";
        }

    } 
    return 0;
}