#ifndef STUDENT_H
#define STUDENT_H

#include "account.h"
#include "course.h"
#include "assignment.h"

#include <string>
#include <vector>

class Student
{
private:
    Account account;
    std::vector<Course> myCourses;

public:
    Student();
    Student(Account &);

    void run();
    void listCourses();
    void listMyCourses();

    void build() ;

    void enrollCourse(Course &);
    void submitSolution(Assignment &);

    void view_allCourse();
    void view_myCourses();
    void view_courseMenu(Course &);
    void unRegisterFromCourse(Course &);
    void view_assignmentMenu(Assignment &);
    void view_global_courseMenu(Course &);
};

#endif