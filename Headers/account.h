#ifndef ACCOUNT_H
#define ACCOUNT_H


#include<string>
#include<vector>
#include<regex>

const std::regex NAME_MATCH = std::regex("[A-Za-z[:s:]]+");
const std::regex USERNAME_MATCH = std::regex("[A-Za-z0-9_.-]+");
const std::regex EMAIL_MATCH = std::regex("([A-Za-z0-9_.]+)(@)([A-Za-z]+)(.com)");
const std::regex PASSWORD_MATCH = std::regex("[A-Za-z0-9]+")

class Account{
private :
    std::string id, username, password, name, email, age  ;
    std::vector<Account> freinds ; 
public :
    std::string get_id() ;
    std::string get_username() ; 
    std::string get_password() ;
    std::string get_name() ;
    std::string get_email() ;
    std::string get_age() ; 

    void set_id(const std::string&) ;
    bool set_username(const std::string&) ;
    bool set_password(const std::string&) ;
    bool set_name(const std::string&) ;
    bool set_email(const std::string&) ;
    bool set_age(const std::string&) ;

    bool validate_username(const std::string&) ;
    bool validate_password(const std::string&) ;
    bool validate_name(const std::string&) ; 
    bool validate_email(const std::string&) ;
    bool validate_age(const std::string&) ;

}

#endif