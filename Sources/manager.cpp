#include "../Headers/manager.h"
#include "../Headers/helper_func.h"
#include "../Headers/teacher_assistant.h"
#include "../Headers/login.h"
#include "../Headers/system_controller.h"
#include <iostream>
#include <fstream>
#include <string>

Manager ::Manager(){};
Manager ::Manager(Account _acocunt)
{
    this->account = _acocunt;
}

void Manager::run()
{

    while (true)
    {
        std::cout << "Menu :" << std::endl;
        std::cout << "1- Show signup requests" << std::endl;
        std::cout << "2- List All Usesrs" << std::endl;
        std::cout << "3- Logout" << std::endl;

        std::string choice;
        input_number(choice, {1, 3});

        if (choice == "1")
        { // show signup requests
            this->view_signupRequests();
        }
        else if (choice == "2")
        { // list all useres
            this->view_users();
        }
        else if (choice == "3")
        { // logout
            return;
        }
    }
}

std::vector<Account> Manager::listSignupReq()
{
    std::vector<Account> result;
    std::ifstream accounts_File("Database/Accounts.txt");
    if (accounts_File.fail())
    {
        std::cerr << "Error Finding Accounts File While Showing Singup Requests, System Faild!." << std::endl;
        return result;
    }
    std::string line;
    while (getline(accounts_File, line))
    {
        Account account(line);
        if ((account.get_accountType() == "Teacher Assistant" || account.get_accountType() == "Doctor") && account.get_accountValidation() == "0")
        {
            result.push_back(account);
        }
    }
    accounts_File.close();
    return result;
}

std::vector<Account> Manager::listAllUsers()
{
    std::vector<Account> result;
    std::ifstream accounts_File("Database/Accounts.txt");
    if (accounts_File.fail())
    {
        std::cerr << "Error Finding Accounts File, System Failed!" << std::endl;
        return result;
    }
    std::string line;
    while (getline(accounts_File, line))
    {
        Account account(line);
        result.push_back(account);
    }
    accounts_File.close();
    return result;
}

void Manager::view_signupRequests()
{
    while (true)
    {
        std::vector<Account> requests = this->listSignupReq();
        if ((int)requests.size() == 0)
        {
            std::cout << "There Are No Signup Requests." << std::endl;
            return;
        }
        for (int i = 0; i < (int)requests.size(); i++)
        {
            std::cout << i + 1 << ": ";
            requests[i].printAccount();
        }
        std::string choice, choice_index;
        std::cout << "1- View Acount" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "2")
        {
            return;
        }
        std::cout << "Enter The Account You Want To View, ";
        if (!input_number(choice_index, {1, (int)requests.size()}))
        {
            continue;
        }
        std::string option;
        std::cout << "1- Accept" << std::endl;
        std::cout << "2- Reject" << std::endl;
        std::cout << "3- Back" << std::endl;
        if (!input_number(option, {1, 3}))
        {
            continue;
        }
        std::string validation;
        if (option == "1")
        {
            validation = "1";
        }
        else if (option == "2")
        {
            validation = "0";
        }
        else if (option == "3")
        {
            continue;
        }
        std::string path_ = "Database/Accounts.txt";
        std::string toDelete = requests[std::stoi(choice_index) - 1].putOnString();
        deleteFromFile(path_, toDelete);
        requests[std::stoi(choice_index) - 1].set_accountValidation(validation);
        std::vector<std::string> toAppend = requests[std::stoi(choice_index) - 1].putOnVector();
        appendOnFile(path_, toAppend);
    }
}
void Manager::view_users()
{
    while (true)
    {
        std::vector<Account> users = this->listAllUsers();
        if ((int)users.size() == 0)
        {
            std::cout << "There Are No Users" << std::endl;
            return;
        }
        for (int i = 0; i < (int)users.size(); i++)
        {
            std::cout << i + 1 << ": ";
            users[i].printAccount();
        }
        std::string choice, choice_index;
        std::cout << "1- View" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "2")
        {
            return;
        }
        // View
        std::cout << "Enter The Account You Want To View, ";
        if (!input_number(choice_index, {1, (int)users.size()}))
        {
            continue;
        }
        std::string option;
        std::cout << "1- Delete Account" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(option, {1, 2}))
        {
            continue;
        }
        else if (option == "2")
        {
            return;
        }
        std::cout << "Are You Sure You Want To Delete This Account?";
        std::cout << "1- Yes" << std::endl;
        std::cout << "2- No" << std::endl;
        std::string sure;
        if (!input_number(sure, {1, 2}))
        {
            continue;
        }
        if (sure == "2")
        {
            continue;
        }
        // manager wants to delete this user.
        std::string path_ = "Database/Accounts.txt";
        std::string toDelete = users[std::stoi(choice_index) - 1].putOnString();
        deleteFromFile(path_, toDelete);
    }
}