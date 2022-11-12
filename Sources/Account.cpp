#include"../Headers/account.h"

#include<iostream>
#include<regex>
#include<string>
#include<vector>

Account::Account() {} ;
Account::Account(const std::string& _id, const std::string& _username, const std::string& _password,
        const std::string _name, const std::string& _email, const std::string& _age){
    this -> set_All(_id, _username, _password, _name, _email, _age) ;
}


std::string Account :: get_id() { return this -> id ;}
std::string Account :: get_username() { return this -> username ; } 
std::string Account :: get_password() { return this -> password ; } 
std::string Account :: get_name() { return this -> name ; } 
std::string Account :: get_email() { return this -> email ; }
std::string Account :: get_age() { return this -> age ; } 


bool Account::validate_email(const std::string& desired_email){
    return std::regex_match(desired_email, EMAIL_MATCH) ;
}
bool Account::validate_password(const std::string& desired_password){
    return std::regex_match(desired_password, PASSWORD_MATCH) ;
}
bool Account::validate_username(const std::string& desired_username){
    return std::regex_match(desired_username, USERNAME_MATCH) ;
}
bool Account::validate_name(const std::string& desired_name){
    return std::regex_match(desired_name, NAME_MATCH) ;
}
bool Account::validate_age(const std::string& desired_age){
    if(desired_age.size() != 2) return false ;
    if(desired_age[0] >= '1' && desired_age[0] <= '9' &&
       desired_age[1] >= '0' && desired_age[1] <= '9'){
        if(desired_age[0] == '1') return desired_age[1] >= '8' ;
        else if(desired_age[0] == '0') return false ;
        else return true ;
    }
    else return false ;
}

bool Account::set_username(const std::string& desired_username){
    if(Account::validate_username(desired_username)){
        Account::username = desired_username ;
        return true ;
    }
    else{
        std::cerr << "Invalid Input" << std::endl ;
        return false ;
    }
}
bool Account::set_password(const std::string& desired_password){
    if(Account::validate_password(desired_password)){
        Account::password = desired_password ;
        return true ; 
    }
    else{
        std::cerr << "Invalid Input" << std::endl ;
        return false ;
    }
}
bool Account::set_name(const std::string& desired_name){
    if(Account::validate_name(desired_name)){
        Account::name = desired_name ; 
        return true ;
    }
    else{
        std::cerr << "Invalid Input" << std::endl ;
        return false ;
    }
}
