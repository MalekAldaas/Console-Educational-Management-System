#ifndef TEACHER_ASSISTANT_H
#define TEACHER_ASSISTANT_H

#include "account.h"
#include "course.h"

#include <string>
#include <vector>

class Teacher_Assistant
{

public:
    std::vector<Course> myCourses;
    Account account;

    Teacher_Assistant();
    Teacher_Assistant(Account &);
    std::vector<std::string> loadInvitations();
    void showInvitations();

    void build();

    void view_allCourses();
    void view_myCourse();

    void run();
};

#endif