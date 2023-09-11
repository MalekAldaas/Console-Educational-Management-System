#include "../Headers/assignment.h"
#include "../Headers/helper_func.h"
#include "../Headers/date.h"
#include "../Headers/solution.h"
#include "../Headers/account.h"

#include <string>
#include <vector>

Assignment::Assignment(){};
Assignment::Assignment(std::string &line)
{
    std::vector<std::string> data = readLine(line);
    std::string Day, Month, Year;
    this->id = data[0];
    this->parentCourse = data[1];
    this->totalGrade = data[2];
    this->paragraph = data[3];
    Day = data[4];
    Month = data[5];
    Year = data[6];
    Date Assignment_deadLine(std::stoi(Day), std::stoi(Month), std::stoi(Year));
    this->deadLine = Assignment_deadLine;
}
Assignment::Assignment(std::string &_id, std::string &_parentCourse, std::string &_totalGrade, std::string &_paragraph, Date &_deadLine)
{
    this->id = _id;
    this->parentCourse = _parentCourse;
    this->totalGrade = _totalGrade;
    this->paragraph = _paragraph;
    this->deadLine = _deadLine;
}

void Assignment::showAssignment()
{
    std::cout << "Assignment ID: " << this->id << " Total Grade: " << this->totalGrade << "  Dead Line: ";
    this->deadLine.ShowDate();
    std::cout << this->paragraph << std::endl;
}

std::vector<std::string> Assignment::putOnVector()
{
    std::string Day, Month, Year;
    Day = std::to_string(this->deadLine.getDay());
    Month = std::to_string(this->deadLine.getMonth());
    Year = std::to_string(this->deadLine.getYear());

    std::vector<std::string> result;
    result.push_back(this->id);
    result.push_back(this->parentCourse);
    result.push_back(this->totalGrade);
    result.push_back(this->paragraph);
    result.push_back(Day);
    result.push_back(Month);
    result.push_back(Year);

    return result;
}

std::string Assignment::get_id()
{
    return this->id;
}
std::string Assignment::get_parentCourse()
{
    return this->parentCourse;
}
std::string Assignment::get_totalGrade()
{
    return this->totalGrade;
}
Date Assignment::get_deadLine()
{
    return this->deadLine;
}
void Assignment::push_Solution(Solution solution)
{
    this->solutions.push_back(solution);
    std::vector<std::string> data = solution.putOnVector();
    appendOnFile("Database/Solutions.txt", data);
}
void Assignment::buildAssignment()
{
    this->solutions.clear();
    std::ifstream solutions_File("Database/Solutions.txt");
    if (solutions_File.fail())
    {
        std::cerr << "Error Opeining Solutions File While Building Assignment, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(solutions_File, line))
    {
        Solution solution(line);
        if (solution.get_assignment_id() == this->id)
        {
            this->solutions.push_back(solution);
        }
    }
    solutions_File.close();
}

void Assignment::listSolutions()
{
    if ((int)this->solutions.size() == 0)
    {
        std::cout << "(No Solutions)" << std::endl;
        return;
    }
    for (int i = 0; i < (int)this->solutions.size(); i++)
    {
        std::cout << i + 1 << ": ";
        this->solutions[i].showSolution();
    }
}

void Assignment::showAssignment_Report()
{
    this->buildAssignment() ;
    int number_markedSolutions = 0;
    int average_markedSubmitedSolutions = 0;
    for (int i = 0; i < (int)this->solutions.size(); i++)
    {
        if (this->solutions[i].get_solutionGrade() != "-1")
        {
            number_markedSolutions++;
            average_markedSubmitedSolutions += std::stoi(this->solutions[i].get_solutionGrade());
        }
    }
    if((int)this->solutions.size() > 0) average_markedSubmitedSolutions /= (int)this->solutions.size();

    std::cout << "Total Submited Solutions: " << (int)this->solutions.size() << "  ";
    std::cout << "Marked Solutions: " << number_markedSolutions << "/" << (int)this->solutions.size() << "  ";
    std::cout << "With Total Average: " << average_markedSubmitedSolutions;
    std::cout << std::endl;
}

Solution Assignment::isStudentHasSubmit(std::string student_ID)
{
    Solution res;
    for (int i = 0; i < (int)this->solutions.size(); i++)
    {
        if (solutions[i].get_student_id() == student_ID)
        {
            res = solutions[i];
            break;
        }
    }
    return res;
}

void Assignment::view_assignmentMenu()
{ // view single assignment and list some options
    while (true)
    {
        this->buildAssignment();
        this->showAssignment();
        std::string choice;
        std::cout << "1- List Solutions" << std::endl;
        std::cout << "2- View Solution" << std::endl;
        std::cout << "3- Show Grade Report" << std::endl;
        std::cout << "4- Back" << std::endl;
        if (!input_number(choice, {1, 4}))
        {
            continue;
        }
        if (choice == "1")
        {
            this->listSolutions();
        }
        else if (choice == "2")
        {
            std::string solution_index;
            if((int)this->solutions.size() == 0){
                std::cout << "Assignment Has No Solutions." << std::endl;
                continue ;
            }
            this->listSolutions() ;
            std::cout << "Enter The Solution You Want To Show" << std::endl;
            if (!input_number(solution_index, {1, (int)this->solutions.size()}))
            {
                continue;
            }
            this->solutions[std::stoi(solution_index) - 1].view_solutionMenu();
        }
        else if (choice == "3")
        {
            this->showAssignment_Report();
        }
        else if (choice == "4")
        {
            return;
        }
    }
}