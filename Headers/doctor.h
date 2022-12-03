#ifndef DOCTOR_H
#define DOCTOR_H

#include"account.h"
#include"course.h" 

class Doctor{
    private :
        Account account ;
        std::vector<Course> myCourses ;
    public : 
        Doctor() ;
        Doctor(const Account&); 
        void addCourse(const std::string&,  const std::vector<std::string>&, const std::string&) ;
        void addPost(const std::string&, const std::string&) ;
        void addAssignment(const std::string&, const std::string&) ;
} ;


#endif