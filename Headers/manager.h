#ifndef MANAGER_H
#define MANAGER_H

#include"account.h"

#include<string>

class Manager{
    private :
        Account account ;
    public :
        Manager() ;
        Manager(Account) ;
        void showSignupReq() ;
        bool setAccountValidation(const std::string&, bool); 
        void deleteUser(const std::string&) ;

        void run() ; 
        

};

#endif