#include "../Headers/account.h"
#include "../Headers/helper_func.h"
#include "../Headers/system_controller.h"

#include <iostream>
#include <regex>
#include <string>
#include <vector>

Account::Account()
{
    this->initialize();
}

Account::Account(const std::string &_id, const std::string &_username, const std::string &_password,
                 const std::string &_name, const std::string &_email, const std::string &_age,
                 const std::string &_accountType, const std::string &_accountValidation)
{
    Account::set_all(_id, _username, _password, _name, _email, _age, _accountType, _accountValidation);
}

Account::Account(const std::string &line)
{
    std::vector<std::string> v = readLine(line);
    this->id = v[0];
    this->username = v[1];
    this->password = v[2];
    this->name = v[3];
    this->email = v[4];
    this->age = v[5];
    this->accountType = v[6];
    this->accountValidation = v[7];
}

std::string Account::get_id() { return this->id; }
std::string Account::get_username() { return this->username; }
std::string Account::get_password() { return this->password; }
std::string Account::get_name() { return this->name; }
std::string Account::get_email() { return this->email; }
std::string Account::get_age() { return this->age; }
std::string Account::get_accountType() { return this->accountType; }
std::string Account::get_accountValidation() { return this->accountValidation; }

bool Account::validate_email(const std::string &desired_email)
{
    return std::regex_match(desired_email, EMAIL_MATCH);
}

bool Account::validate_password(const std::string &desired_password)
{
    return std::regex_match(desired_password, PASSWORD_MATCH);
}

bool Account::validate_username(const std::string &desired_username)
{
    return std::regex_match(desired_username, USERNAME_MATCH);
}

bool Account::validate_name(const std::string &desired_name)
{
    return std::regex_match(desired_name, NAME_MATCH);
}

bool Account::validate_age(const std::string &desired_age)
{
    if (desired_age.size() != 2)
        return false;
    if (desired_age[0] >= '1' && desired_age[0] <= '9' &&
        desired_age[1] >= '0' && desired_age[1] <= '9')
    {
        if (desired_age[0] == '1')
            return desired_age[1] >= '8';
        else if (desired_age[0] == '0')
            return false;
        else
            return true;
    }
    else
        return false;
}

bool Account::validate_accountType(const std::string &desired_accountType)
{
    if (desired_accountType == "Student" || desired_accountType == "Doctor" ||
        desired_accountType == "Teacher Assistant" || desired_accountType == "MANAGER")
        return true;
    return false;
}

bool Account::distinct_account(const std::string &_username, const std::string &_email)
{
    std::ifstream account_File("Database/Accounts.txt");
    if (account_File.fail())
    {
        std::cerr << "Error Opening Accounts File While Checking Distinct Accounts, System Faild!" << std::endl;
        return false;
    }
    std::string line;
    while (getline(account_File, line))
    {
        Account account(line);
        if (account.get_username() == _username || account.get_email() == _email)
            return false;
    }
    return true;
}

void Account::set_id(const std::string &desired_id)
{
    this->id = desired_id;
}

void Account::set_username(const std::string &desired_username)
{
    if (Account::validate_username(desired_username))
    {
        this->username = desired_username;
    }
}

void Account::set_password(const std::string &desired_password)
{
    if (Account::validate_password(desired_password))
    {
        this->password = desired_password;
    }
}

void Account::set_name(const std::string &desired_name)
{
    if (Account::validate_name(desired_name))
    {
        this->name = desired_name;
    }
}

void Account::set_email(const std::string &desired_email)
{
    if (Account::validate_email(desired_email))
    {
        this->email = desired_email;
    }
}

void Account::set_age(const std::string &desired_age)
{
    if (Account::validate_age(desired_age))
    {
        this->age = desired_age;
    }
}

void Account::set_accountType(const std::string &desired_accountType)
{
    this->accountType = desired_accountType;
}

void Account::set_accountValidation(const std::string &desired_validation)
{
    this->accountValidation = desired_validation;
}

void Account::set_all(const std::string &_id, const std::string &_username,
                      const std::string &_password, const std::string &_name,
                      const std::string &_email, const std::string &_age,
                      const std::string &_accountType, const std::string &_accountValidation)
{
    if (Account::validate_username(_username) && Account::validate_password(_password) &&
        Account::validate_name(_name) && Account::validate_accountType(_accountType) &&
        Account::validate_email(_email) && Account::validate_age(_age) &&
        Account::distinct_account(_username, _email))
    {
        this->set_id(_id);
        this->set_username(_username);
        this->set_password(_password);
        this->set_name(_name);
        this->set_email(_email);
        this->set_age(_age);
        this->set_accountType(_accountType);
        this->set_accountValidation(_accountValidation);
    }
}

bool Account::empty()
{
    return this->id.size() == 0;
}

void Account::initialize()
{
    this->id = "";
    this->username = "";
    this->password = "";
    this->name = "";
    this->email = "";
    this->age = "";
    this->accountType = "";
    this->accountValidation = "";
}

std::vector<std::string> Account::putOnVector()
{
    std::vector<std::string> tem;

    tem.push_back(this->get_id());
    tem.push_back(this->get_username());
    tem.push_back(this->get_password());
    tem.push_back(this->get_name());
    tem.push_back(this->get_email());
    tem.push_back(this->get_age());
    tem.push_back(this->get_accountType());
    tem.push_back(this->get_accountValidation());

    return tem;
}

std::string Account::putOnString()
{
    std::vector<std::string> v;
    std::string total = "";
    v = this->putOnVector();
    for (std::string s : v)
    {
        total += s;
        total += ",";
    }
    return total;
}

void Account::operator=(const Account &other)
{
    this->id = other.id;
    this->username = other.username;
    this->password = other.password;
    this->email = other.email;
    this->name = other.name;
    this->age = other.age;
    this->accountType = other.accountType;
    this->accountValidation = other.accountValidation;
}

void Account::printAccount()
{
    std::cout << "ID: " << this->id << "  Username: " << this->username << "  Password: " << this->password << "  Name: " << this->name
              << "  Email: " << this->email << "  Age: " << this->age << "  Role: " << this->accountType << " Statues: " ;
    if(this->accountValidation == "1"){
        std::cout << "(Accepted)" << std::endl; 
    }
    else{
        std::cout << "(NOT Accepted)" << std::endl; 
    }
}
void Account::setAccountByID(int id)
{
    std::ifstream accounts_File("Database/Accounts.txt");
    if (accounts_File.fail())
    {
        std::cerr << "Error Opening Accounts File, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(accounts_File, line))
    {
        Account _account(line);
        if (_account.get_id() == std::to_string(id))
        {
            *this = _account;
            return;
        }
    }
}

void Account::loadMessages(Account &other_account)
{
    std::ifstream messages_File("Database/Messages.txt");
    if (messages_File.fail())
    {
        std::cerr << "Error Opening Messages File While Loading Messages, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(messages_File, line))
    {
        std::vector<std::string> data = readLine(line);
        if (data[0] == this->id && data[1] == other_account.get_id())
        {
            std::cout << this->name << ": " << data[2] << std::endl;
        }
        else if (data[0] == other_account.get_id() && data[1] == this->id)
        {
            std::cout << other_account.get_name() << ": " << data[2] << std::endl;
        }
    }
    messages_File.close();
}

void Account::sendMessage()
{
    std::cout << "Enter Username/Email/ID: " << std::endl;
    std::string desired;
    getline(std::cin, desired);

    if (desired == this->id || desired == this->email)
    {
        std::cout << "Messaging Your Self Is Not Allowed :)." << std::endl;
        return;
    }

    Account other;
    bool foundUser = false;
    std::ifstream accounts_File("Database/Accounts.txt");
    if (accounts_File.fail())
    {
        std::cerr << "Error Opeining Accounts File While Preparing To Send Message, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(accounts_File, line))
    {
        Account tem_account(line);
        if (tem_account.get_id() == desired || tem_account.get_email() == desired || tem_account.get_username() == desired)
        {
            other = tem_account;
            foundUser = true;
            break;
        }
    }
    accounts_File.close();
    if (foundUser == false || other.get_accountValidation() == "0")
    {
        std::cout << "There is No User With The Given Informations!" << std::endl;
        return;
    }

    this->loadMessages(other);
    std::string message;
    std::cout << "Enter Message: ";
    getline(std::cin, message);

    std::vector<std::string> vc_messageData = {this->id, other.get_id(), message};
    std::string path = "Database/Messages.txt";
    appendOnFile(path, vc_messageData);
}
