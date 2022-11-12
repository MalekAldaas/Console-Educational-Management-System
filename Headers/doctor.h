#ifndef DOCTOR_H
#define DOCTOR_H

#include"account.h"

class Doctor{
    private :
        Account account ;

    public : 
        void addCourse(const std::string&,  const std::vector<std::string>&, const std::string&) ;
        void addPost(const std::string&, const std::string&) ;
        void addAssignment(const std::string&, const std::string&) ;
        void showSignup
}


#endif