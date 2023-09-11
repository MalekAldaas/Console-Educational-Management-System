#ifndef COURSE_H
#define COURSE_H

#include "assignment.h"

#include <string>
#include <vector>

class Course
{
private:
    std::string id, name, password, code, instructor, paragraph;

public:
    std::vector<Assignment> assignments;
    std::vector<Course> preRequests; // in file, I store two integers u and v, mean the u prerequests v.

    Course();
    Course(std::string &);
    Course(std::string &, std::string &, std::string &, std::string &, std::string &, std::string &, std::vector<Course> &);
    std::string get_id();
    std::string get_name();
    std::string get_password();
    std::string get_code();
    std::string get_instructor();
    std::string get_paragraph();

    void setCourseByID(int);

    std::vector<std::string> putOnVector();

    void buildCourse();
    void buildCourse_Assignments();
    void buildCourse_PreRequests();
    void showCourse_Main();
    void showCourse_Details();
    void showCouse_Report();

    int getNumberOfAssignments();

    void showCourse_preRequests();
    void addAssignment();

    void view_courseMenu(std::string);

    void invite_TA(std::string); 
};
std::vector<Course> get_IdenticalCourses_From(std::vector<Course> &, std::vector<Course> &);

#endif