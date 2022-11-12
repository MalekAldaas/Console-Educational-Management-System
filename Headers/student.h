#ifndef STUDENT_H
#define STUDENT_H

#include"account.h"

#include<string> 

class Student{
    private : 
        Account account ; 

    public : 
        void showMyCourses() ;
        void showCoursesList() ;
        void enrolCourse(const std::string&) ;


}

#endif