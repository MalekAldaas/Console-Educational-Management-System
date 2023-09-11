#include "../Headers/signup.h"
#include "../Headers/account.h"
#include "../Headers/helper_func.h"
#include "../Headers/system_controller.h"

#include <string>
#include <iostream>

void signup(Account &account)
{
   std::string _username, _password, _name, _email, _age, _accountType, _accountValidation;
   input_username(_username);
   input_password(_password);
   input_name(_name);
   input_email(_email);
   input_age(_age);
   input_accountType(_accountType);
   if (_accountType == "Student")
      _accountValidation = "1";
   else
      _accountValidation = "0";
   SystemController ems;
   std::string new_account_id = ems.get_account_ID();
   account.set_all(new_account_id, _username, _password, _name, _email, _age, _accountType, _accountValidation);
   if (account.get_id() == new_account_id)
   {
      ems.increase_account_ID();
      std::vector<std::string> account_data = account.putOnVector();
      std::string path_ = "Database/Accounts.txt";
      appendOnFile(path_, account_data);
   }
}