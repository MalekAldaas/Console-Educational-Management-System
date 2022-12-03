#include"../Headers/manager.h"
#include"../Headers/helper_func.h"
#include"../Headers/teacher_assistant.h"
#include"../Headers/login.h"
#include<iostream>
#include<fstream>
#include<string> 

Manager :: Manager() {} ; 
Manager :: Manager(Account _acocunt){
    this->account = _acocunt ;
}

void Manager::run(){
    std::cout << "Menu :" << std::endl; 
    std::cout << "1- Show signup requests" << std::endl ;
    std::cout << "2- accept or rejct signup requests" << std::endl ;
    std::cout << "3- Delete User" << std::endl ;
    std::cout << "4- Logout" << std::endl ; 
    
    std::string choice ;
    input_number(choice, {1,4}) ;
    
    if(choice == "1"){ // show signup requests
        showSignupReq() ;
    }
    else if(choice == "2"){ // accept or reject signup requests
        std::string ID, operationType;
        std::cout << "Enter the ID: "; std::cin >> ID;
        std::cout << "to accept enter 1, otherwise enter 0" << std::endl ;
        bool ac = true ;
        std::cin >> operationType; 
        if(operationType == "1") ac = true ;
        else if(operationType == "0") ac = false; 
        if(setAccountValidation(ID,ac))  std::cout << "Operation Done." << std::endl ;
        else std::cout << "There is no user with the given ID! " << std::endl ;
        
    }
    else if(choice == "3"){ // Delete User
        std::string ID;
        std::cout << "Enter the ID: " ; std::cin >> ID;
        if(setAccountValidation(ID,false))  std::cout << "Deleting Done." << std::endl ;
        else std::cout << "There is no user with the given ID! " << std::endl ;
    }
    else if(choice == "4"){ // logout
        logout(this->account );
        return ;
    }
    this->run() ;
    
}

void Manager::showSignupReq(){
    std::ifstream accounts_File ("../Database/Accounts.txt") ;
    if(accounts_File.fail()){
        std::cerr << "System Failed!" << std::endl ;
        return ;
    }
    std::string line ;
    while(getline(accounts_File,line)){
        Account account(line) ;
        if(account.get_accountType() == "Teacher_Assistant" || account.get_accountType() == "Doctor"){
            std::cout << account.get_id() << " " << account.get_username()
             << " " << account.get_name() << " " << account.get_email() << std::endl ; 
        }
    }
    accounts_File.close() ;
}

bool Manager::setAccountValidation(const std::string& ID, bool ac){  //note, this method deletes the account from db.
    if(ID == this->account.get_id()) return false ;
    std::vector<std::string> data ;
    std::ifstream accounts_File("../Database/Accounts.txt") ;
    if(accounts_File.fail()){
        std::cerr << "System Failed!" << std::endl ;
        return false;
    }
    std::string line ;
    std::string AC ;
    if(ac == true) AC = "1" ;
    else AC = "0" ;
    bool validOperation = false ;
    while(getline(accounts_File, line)){
        Account account(line) ;
        if(account.get_id() == ID){
            validOperation = true ;
            account.set_accountValidation(AC) ;
            std::string tem = account.putOnString(); 
            if(ac == true) data.push_back(tem) ;
        }
        else{
            data.push_back(line) ;
        }
    }
    accounts_File.close() ;
    writeOnFile("../Database/Accounts.txt", data) ;
    return validOperation ;
}