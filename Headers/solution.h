#ifndef SOLUTION_H
#define SOLUTION_H

#include "date.h"

#include <string>
#include <vector>

class Solution
{
private:
    std::string id, student_id, assignment_id, paragraph, solutionGrade, assignmentGrade;
    Date submissionDate;
    std::string instructorComment;

public:
    Solution();
    Solution(std::string &);
    Solution(std::string &, std::string &, std::string &, std::string &, std::string &, std::string &, Date &);

    std::string get_id();
    std::string get_student_id();
    std::string get_assignment_id();
    std::string get_solutionGrade();
    std::string get_assignmentGrade();
    std::string get_instructorComment();
    std::string get_paragraph(); 
    Date get_submissionData(); 

    void set_solutionGrade(std::string &);
    void set_instructorComment(std::string &);


    std::vector<std::string> putOnVector();
    void showSolution();

    void view_solutionMenu();
};

#endif