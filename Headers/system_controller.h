#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "course.h"

#include <string>
#include <vector>

class SystemController
{
private:
    std::string u_account_id, u_course_id,
        u_comment_id, u_assignment_id, u_solution_id;

public:
    SystemController();
    void run();
    std::string get_account_ID();
    std::string get_course_ID();
    std::string get_comment_ID();
    std::string get_assignment_ID();
    std::string get_solution_ID();

    void increase_account_ID();
    void increase_course_ID();
    void increase_assignment_ID();
    void increase_comment_ID();
    void increase_solution_ID();

    std::vector<std::string> putOnVector();

    std::vector<Course> listCourses();
    std::vector<Account> listTA(); 
    void listUsers(); 

    void updateSystem();
    void fetchdata();
};

#endif