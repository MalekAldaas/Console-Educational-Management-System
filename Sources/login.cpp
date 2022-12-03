#include"../Headers/login.h"
#include"../Headers/account.h"



#include<string>
#include<vector>
#include<iostream>
#include<fstream>

void login(const std::string& username_email, const std::string& _password, Account& account){
    std::ifstream accountsFile ("../Database/Accounts") ;
    if(accountsFile.fail()){
        std::cerr << "System Faild!" << std::endl ;
        return ;
    }
    std::string line ;
    while(getline(accountsFile,line)){
        Account temp_account(line) ;
        if(temp_account.get_username() == username_email || temp_account.get_email() == username_email
             && temp_account.get_password() == _password){
            account = temp_account ;
            return;
        }
    }
    accountsFile.close() ;
    std::cout << "There is no account with such username and password." << std::endl ;
}

void logout(Account& account){
    account.initialize() ;
}

