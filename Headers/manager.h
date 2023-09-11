#ifndef MANAGER_H
#define MANAGER_H

#include "account.h"

#include <string>
#include <vector>

class Manager
{
private:
    Account account;

public:
    Manager();
    Manager(Account);
    void run();
    std::vector<Account> listSignupReq();
    std::vector<Account> listAllUsers();
    void view_signupRequests() ;
    void view_users() ;
};

#endif