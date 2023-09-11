#include "../Headers/login.h"
#include "../Headers/account.h"
#include "../Headers/helper_func.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

void login(Account &account)
{
    std::string username_email, password;
    std::cout << "Enter your you email/username: ";
    getline(std::cin, username_email);
    input_password(password);
    std::ifstream accountsFile("Database/Accounts.txt");
    if (accountsFile.fail())
    {
        std::cerr << "Error Opening Accounts File While Login, System Faild!" << std::endl;
        return;
    }
    if (username_email == "ADMIN" && password == "ADMIN")
    {
        account.set_id("0");
        account.set_accountValidation("1") ;
        account.set_accountType("MANAGER");
        return;
    }
    std::string line;
    while (getline(accountsFile, line))
    {
        Account temp_account(line);
        if ((temp_account.get_username() == username_email || temp_account.get_email() == username_email) && temp_account.get_password() == password)
        {
            account = temp_account;
            return;
        }
    }
    accountsFile.close();
    std::cout << "There is no account with such username/email and password." << std::endl;
}

void logout(Account &account)
{
    account.initialize();
}