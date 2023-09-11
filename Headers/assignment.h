#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "date.h"
#include "solution.h"
#include "account.h"

#include <string>
#include <vector>

class Assignment
{
private:
    std::string id, parentCourse, totalGrade, paragraph;
    Date deadLine;

public:
    std::vector<Solution> solutions;

    Assignment();
    Assignment(std::string &);
    Assignment(std::string &, std::string &, std::string &, std::string &, Date &);

    void buildAssignment();
    void showAssignment();
    void listSolutions();
    void showAssignment_Report();

    std::string get_id();
    std::string get_parentCourse();
    std::string get_totalGrade();

    Date get_deadLine();
    void push_Solution(Solution);
    std::vector<std::string> putOnVector();

    Solution isStudentHasSubmit(std::string);

    void view_assignmentMenu();
};

#endif