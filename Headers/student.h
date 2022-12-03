#ifndef STUDENT_H
#define STUDENT_H

#include"account.h"
#include"course.h"

#include<string> 
#include<vector>

class Student{
    private : 
        Account account ; 
        std::vector<Course> myCourses ;
    public : 
        Student() ;
        Student(const Account&) ;
        void run() ;
        void showMyCourses() ;
        void showCoursesList() ;
        void enrolCourse(const std::string&) ;
} ;

#endif