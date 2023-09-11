#include "../Headers/solution.h"
#include "../Headers/assignment.h"
#include "../Headers/helper_func.h"
#include "../Headers/date.h"
#include "../Headers/account.h"

#include <string>
#include <vector>
#include <iostream>

Solution::Solution()
{
    this->solutionGrade = "-2";
    this->assignmentGrade = "-2";
};
Solution::Solution(std::string &line)
{
    std::vector<std::string> data = readLine(line);
    this->id = data[0];
    this->student_id = data[1];
    this->assignment_id = data[2];
    this->paragraph = data[3];
    this->solutionGrade = data[4];
    this->assignmentGrade = data[5];

    int Day, Month, Year;
    Day = std::stoi(data[6]);
    Month = std::stoi(data[7]);
    Year = std::stoi(data[8]);

    Date _submissionDate(Day, Month, Year);
    this->submissionDate = _submissionDate;
}

Solution::Solution(std::string &_id, std::string &_student_id, std::string &_assignment_id, std::string &_paragraph, std::string &_solutionGrade, std::string &_assignmentGrade, Date &_submissionDate)
{
    this->id = _id;
    this->student_id = _student_id;
    this->assignment_id = _assignment_id;
    this->paragraph = _paragraph;
    this->solutionGrade = _solutionGrade;
    this->assignmentGrade = _assignmentGrade;
    this->submissionDate = _submissionDate;
}

std::string Solution::get_id() { return this->id; }
std::string Solution::get_student_id() { return this->student_id; }
std::string Solution::get_assignment_id() { return this->assignment_id; }
std::string Solution::get_solutionGrade() { return this->solutionGrade; }
std::string Solution::get_assignmentGrade() { return this->assignmentGrade; }
std::string Solution::get_instructorComment() { return this->instructorComment; }
std::string Solution::get_paragraph() { return this->paragraph; }
Date Solution::get_submissionData() { return this->submissionDate; }

std::vector<std::string> Solution::putOnVector()
{
    std::string Day, Month, Year;
    Day = std::to_string(this->submissionDate.getDay());
    Month = std::to_string(this->submissionDate.getMonth());
    Year = std::to_string(this->submissionDate.getYear());

    std::vector<std::string> result;
    result.push_back(this->id);
    result.push_back(this->student_id);
    result.push_back(this->assignment_id);
    result.push_back(this->paragraph);
    result.push_back(this->solutionGrade);
    result.push_back(this->assignmentGrade);
    result.push_back(Day);
    result.push_back(Month);
    result.push_back(Year);
    result.push_back(this->instructorComment);

    return result;
}

void Solution::showSolution()
{
    Account studnet_account;
    studnet_account.setAccountByID(std::stoi(this->student_id));

    std::cout << "Solution By: " << studnet_account.get_name() << "  ";
    if (this->solutionGrade == "-1")
    {
        std::cout << "(Not Graded Yet)";
    }
    else
    {
        std::cout << "Grade: " << this->get_solutionGrade() << "/" << this->get_assignmentGrade();
    }
    std::cout << "  ";
    this->submissionDate.ShowDate();
    std::cout << std::endl;
    std::cout << "Solution:\t" << this->paragraph << std::endl;
    std::cout << "Instructor Comment: ";
    if ((int)this->instructorComment.size() > 0)
    {
        std::cout << this->instructorComment;
    }
    else
    {
        std::cout << "(Empty)" << std::endl;
    }
}
void Solution::set_solutionGrade(std::string &_grade)
{
    std::vector<std::string> vc_solutionData = this->putOnVector();
    std::string str_solutionData = putOnString(vc_solutionData);
    std::string solutionFile = "Database/solutions.txt";

    this->solutionGrade = solutionGrade;
    deleteFromFile(solutionFile, str_solutionData);

    std::vector<std::string> dataVector = this->putOnVector();
    appendOnFile(solutionFile, dataVector);
}
void Solution::set_instructorComment(std::string &_instructorComment)
{
    std::vector<std::string> vc_solutionData = this->putOnVector();
    std::string str_solutionData = putOnString(vc_solutionData);
    std::string solutionFile = "Database/solutions.txt";

    deleteFromFile(solutionFile, str_solutionData);
    this->instructorComment = _instructorComment;

    std::vector<std::string> dataVector = this->putOnVector();
    appendOnFile(solutionFile, dataVector);
}
void Solution::view_solutionMenu()
{ // view single solution and list some options
    while (true)
    {
        std::string choice;
        std::cout << "1- Set Grade" << std::endl;
        std::cout << "2- Set a Comment" << std::endl;
        std::cout << "3- Back" << std::endl;
        if (!input_number(choice, {1, 3}))
        {
            continue;
        }
        if (choice == "1")
        {
            std::string _grade;
            if (!input_number(_grade, {1, std::stoi(this->get_assignmentGrade())}))
            {
                continue;
            }
            this->set_solutionGrade(_grade);
        }
        else if (choice == "2")
        {
            std::string _comment;
            std::cout << "Enter One Line Comment: ";
            getline(std::cin, _comment);
            this->set_instructorComment(_comment);
        }
        else if (choice == "3")
        {
            return;
        }
    }
}
