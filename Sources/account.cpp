#include"../Headers/account.h"
#include"../Headers/helper_func.h"

#include<iostream>
#include<regex>
#include<string>
#include<vector>

Account::Account(){
    this -> initialize() ;
} 

Account::Account(const std::string& _id, const std::string& _username, const std::string& _password,
        const std::string& _name, const std::string& _email, const std::string& _age,
        const std::string& _accountType, const std::string& _accountValidation){
    Account::set_all(_id, _username, _password, _name, _email, _age, _accountType, _accountValidation) ;
}

Account::Account(const std::string& line){
    std::vector<std::string> v = readLine(line) ;
    const std::string& _id = v[0] , _username = v[1], _password = v[2], _name = v[3],
    _email = v[4], _age = v[5], _accountType = v[6], _accountValidation = v[7];
    Account::set_all(_id, _username, _password, _name, _email, _age, accountType, accountValidation) ;
}

std::string Account::get_id()           { return this->id ;             }
std::string Account::get_username()     {  return this->username ;      } 
std::string Account::get_password()     { return this->password ;       } 
std::string Account::get_name()         { return this->name ;           } 
std::string Account::get_email()        { return this->email ;          }
std::string Account::get_age()          { return this->age ;            } 
std::string Account::get_accountType()  { return this->accountType ;    }
std::string Account::get_accountValidation()   { return this->accountValidation; }

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

bool Account::validate_accountType(const std::string& desired_accountType){
    if( desired_accountType == "Student" || desired_accountType == "Doctor" || 
        desired_accountType == "Teacher Assistant" || desired_accountType == "MANAGER") return true ;
    return false ;
}

bool Account::distinct_account(const std::string& _username, const std::string& _email){
    std::ifstream account_File("../Database/Accounts.txt") ;
    if(account_File.fail()){
        std::cerr << "System Faild!" << std::endl ;
        return false ;
    }
    std::string line ;
    while(getline(account_File, line)){
        Account account(line) ;
        if(account.get_username() == _username || account.get_email() == _email) return false ;
    }
    return true ;
}

void Account::set_id(const std::string& desired_id){
    this->id = desired_id ;
}

void Account::set_username(const std::string& desired_username){
    if(Account::validate_username(desired_username)){
        this->username = desired_username ;
    }
}

void Account::set_password(const std::string& desired_password){
    if(Account::validate_password(desired_password)){
        this->password = desired_password ;
    }
}

void Account::set_name(const std::string& desired_name){
    if(Account::validate_name(desired_name)){
        this->name = desired_name ; 
    }
}

void Account::set_email(const std::string& desired_email){
    if(Account::validate_email(desired_email)){
        this->email = desired_email ;
    }
}

void Account::set_age(const std::string& desired_age){
    if(Account::validate_age(desired_age)){
        this->age = desired_age ;
    }
}

void Account::set_accountType(const std::string& desired_accountType){
    this->accountType = desired_accountType ;
}

void Account::set_accountValidation(const std::string& desired_validation){
    this->accountValidation = desired_validation ;
}

void Account::set_all(const std::string& _id, const std::string& _username,
         const std::string& _password, const std::string& _name,
         const std::string& _email, const std::string& _age,
        const std::string& _accountType, const std::string& _accountValidation){
    if(Account::validate_username(_username) && Account::validate_password(_password) 
       && Account::validate_name(_name) && Account::validate_accountType(_accountType)
       && Account::validate_email(_email) && Account::validate_age(_age) 
       && Account::distinct_account(_username, _email)) {
        this->set_username(_username) ;
        this->set_password(_password) ;
        this->set_name(_name) ;
        this->set_email(_email) ;
        this->set_age(_age) ;
        this->set_accountType(_accountType) ;
        this->set_accountValidation(_accountValidation) ;
    }
}

bool Account::empty(){
    return this->id.size() == 0 ;
}

void Account::initialize(){
    this->id = "" ;
    this->username = "";
    this->password = ""; 
    this->name = "" ;
    this->email = "";
    this->age = "" ;
    this->accountType = "";
    this->accountValidation = "" ;
}

std::vector<std::string> Account::putOnVector(){
    std::vector<std::string> tem ;

    tem.push_back(this->get_id()) ;
    tem.push_back(this->get_username()) ;
    tem.push_back(this->get_password()) ;
    tem.push_back(this->get_name()) ;
    tem.push_back(this->get_email()) ;
    tem.push_back(this->get_age()) ;
    tem.push_back(this->get_accountType()) ;
    tem.push_back(this->get_accountValidation()) ;

    return tem ;    
}

std::string Account::putOnString(){
    std::vector<std::string> v ;
    std::string total = "" ;
    v = this->putOnVector() ;
    for(std::string s : v){
        total   +=  s ;
        total   +=  "," ;
    }
    return total ;
}

void Account::operator=(const Account& other){
    this->id = other.id ;
    this->username = other.username ;
    this->password = other.password ;
    this->email = other.email ;
    this->name = other.name ;
    this->age = other.age ;
    this->accountType = other.accountType ;
    this->accountValidation = other.accountValidation ;
}

