#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <string>
#include <vector>
#include <regex>

const std::regex NAME_MATCH = std::regex("[A-Za-z[:s:]]+");
const std::regex USERNAME_MATCH = std::regex("[A-Za-z0-94_.-]+");
const std::regex EMAIL_MATCH = std::regex("([A-Za-z0-9_.]+)(@)([A-Za-z]+)(.com)");
const std::regex PASSWORD_MATCH = std::regex("[A-Za-z0-9]+");

class Account
{
private:
    std::string id, username, password, name, email, age, accountType, accountValidation;
public:
    Account();
    Account(const std::string &, const std::string &, const std::string &,
            const std::string &, const std::string &, const std::string &,
            const std::string &, const std::string &);
    Account(const std::string &);
    std::string get_id();
    std::string get_username();
    std::string get_password();
    std::string get_name();
    std::string get_email();
    std::string get_age();
    std::string get_accountType();
    std::string get_accountValidation();

    void set_id(const std::string &);
    void set_username(const std::string &);
    void set_password(const std::string &);
    void set_name(const std::string &);
    void set_email(const std::string &);
    void set_age(const std::string &);
    void set_accountType(const std::string &);
    void set_accountValidation(const std::string &);
    void set_all(const std::string &, const std::string &, const std::string &,
                 const std::string &, const std::string &, const std::string &,
                 const std::string &, const std::string &);

    static bool validate_username(const std::string &);
    static bool validate_password(const std::string &);
    static bool validate_name(const std::string &);
    static bool validate_email(const std::string &);
    static bool validate_age(const std::string &);
    static bool validate_accountType(const std::string &);
    static bool distinct_account(const std::string &, const std::string &);

    void initialize();
    bool empty();

    void printAccount();

    std::vector<std::string> putOnVector();
    std::string putOnString();
    void setAccountByID(int) ;
    void operator=(const Account &other);

    //communications 
    void loadMessages(Account &); 
    void sendMessage() ;
};
#endif