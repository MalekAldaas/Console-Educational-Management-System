#ifndef DOCTOR_H
#define DOCTOR_H

#include "account.h"
#include "course.h"
#include "assignment.h"

class Doctor
{
private:
    std::vector<Course> myCourses;

public:
    Account account;
    Doctor();
    Doctor(std::string);
    Doctor(Account &);

    void run();
    void build();

    void view_Course();

    void listCourses();
    void listMyCourses();
    void addCourse();
};

#endif