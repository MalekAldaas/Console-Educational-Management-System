#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include"date.h"
#include"solution.h"

#include<string>
#include<vector>
class Assignment{
    private :
        std::string id, parentCourse, paragraph ; 
        Date deadLine; 
        std::vector<Solution> solutions ;
    public : 
        void build_Assignment() ;
};

#endif