#include"../Headers/signup.h"
#include"../Headers/account.h"
#include"../Headers/helper_func.h"

#include<string>
#include<iostream>

void signup(Account& account){
   std::string  _id, _username, _password, _name, _email, _age, _accountType, _accountValidation ;
   input_username(_username) ;
   input_password(_password) ;
   input_name(_name) ;
   input_email(_email) ;
   input_age(_age) ;
   input_accountType(_accountType) ;
   if(_accountType == "Student") _accountValidation = "1" ;
   else _accountValidation = "0" ;
   account.set_all(_id, _username, _password, _name, _email, _age, _accountType, _accountValidation) ;
}