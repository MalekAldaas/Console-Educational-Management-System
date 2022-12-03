#ifndef COURSE_H
#define COURSE_H

#include"assignment.h" 
#include"teacher_assistant.h"

#include<string>
#include<vector>

class Course{
    private : 
        std::string id, name, password, code, instructer ; 
        std::vector<Assignment> assignments ;  
        std::vector<Teacher_Assistant> teacher_assistants  ;
    public : 
        void buildCourse() ;
        void showCourse() ;

        

};


#endif