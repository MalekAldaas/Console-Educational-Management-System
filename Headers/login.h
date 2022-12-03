#ifndef LOGIN_H
#define LOGIN_H

#include"account.h"

#include<string>

void login(const std::string&, const std::string&, Account&) ; 
void logout(Account& account) ;

#endif