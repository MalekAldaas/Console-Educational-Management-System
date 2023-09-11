#include "../Headers/course.h"
#include "../Headers/helper_func.h"
#include "../Headers/assignment.h"
#include "../Headers/doctor.h"
#include "../Headers/teacher_assistant.h"
#include "../Headers/system_controller.h"
#include "../Headers/account.h"

#include "iostream"
#include <string>
#include <vector>

Course::Course()
{
    this->id = "";
    this->code = "";
    this->paragraph = "";
    this->password = "-1";
    this->instructor = "";
}
Course::Course(std::string &line)
{
    std::vector<std::string> data = readLine(line);
    this->id = data[0];
    this->name = data[1];
    this->password = data[2];
    this->code = data[3];
    this->instructor = data[4];
    this->paragraph = data[5];
}
void Course::setCourseByID(int ID)
{
    std::ifstream courses_File("Database/Courses.txt");
    if (courses_File.fail())
    {
        std::cerr << "Error Opening Courses File, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(courses_File, line))
    {
        Course tempCourse(line);
        if (tempCourse.get_id() == std::to_string(ID))
        {
            *this = tempCourse;
            return;
        }
    }
}
Course::Course(std::string &_id, std::string &_name, std::string &_password, std::string &_code,
               std::string &_instructor, std::string &_paragraph, std::vector<Course> &_preRequests)
{
    this->id = _id;
    this->name = _name;
    this->password = _password;
    this->code = _code;
    this->instructor = _instructor;
    this->paragraph = _paragraph;
    this->preRequests = _preRequests;
}
std::string Course::get_id() { return this->id; }
std::string Course::get_name() { return this->name; }
std::string Course::get_password() { return this->password; }
std::string Course::get_code() { return this->code; }
std::string Course::get_instructor() { return this->instructor; }
std::string Course::get_paragraph() { return this->paragraph; }
int Course::getNumberOfAssignments() { return (int)this->assignments.size(); }

void Course::showCourse_Main()
{
    Doctor doctor(this->instructor);
    std::string Locked = "(Locked With PASSWORD)" ;
    if(this->password == "-1"){
        Locked = "(FREE)" ;
    }
    std::cout << "ID-" << this->id << "  Name: " << this->name << "  Code: " << this->code << " Instructor: " << doctor.account.get_name() << "   " << Locked << std::endl;
    std::cout << this->paragraph << std::endl;
}
void Course::showCourse_Details()
{
    this->showCourse_Main();
    std::cout << "Course Has (" << (int)this->assignments.size() << ") Assignments." << std::endl;
    for (int i = 0; i < (int)this->assignments.size(); i++)
    {
        std::cout << i + 1 << ": ";
        this->assignments[i].showAssignment();
    }
}

std::vector<std::string> Course::putOnVector()
{
    std::vector<std::string> result;
    result.push_back(this->id);
    result.push_back(this->name);
    result.push_back(this->password);
    result.push_back(this->code);
    result.push_back(this->instructor);
    result.push_back(this->paragraph);
    return result;
}

void Course::buildCourse()
{
    this->assignments.clear();
    this->preRequests.clear();
    this->buildCourse_Assignments();
    this->buildCourse_PreRequests();
}

void Course::buildCourse_Assignments()
{
    this->assignments.clear();
    std::ifstream assignment_File("Database/Assignments.txt");
    if (assignment_File.fail())
    {
        std::cerr << "Error Opening Assignment File While Building Course Assignments, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(assignment_File, line))
    {
        Assignment assignment(line);
        if (assignment.get_parentCourse() == this->id)
        {
            this->assignments.push_back(assignment);
        }
    }
    assignment_File.close();
    for (int i = 0; i < (int)this->assignments.size(); i++)
    {
        assignments[i].buildAssignment();
    }
}

void Course::buildCourse_PreRequests()
{
    std::ifstream course_prerequests_File("Database/Course_prerequests.txt");
    if (course_prerequests_File.fail())
    {
        std::cerr << "Error Opening Course Prerequests File While Build Course Prerequests, System Faild!" << std::endl;
        return;
    }
    std::string line;
    std::vector<int> course_prerequests_IDs;
    while (getline(course_prerequests_File, line))
    {
        std::vector<std::string> data = readLine(line);
        if (data[0] == this->id)
        {
            course_prerequests_IDs.push_back(std::stoi(data[1]));
        }
    }
    course_prerequests_File.close();
    for (int i = 0; i < (int)course_prerequests_IDs.size(); i++)
    {
        Course course;
        course.setCourseByID(course_prerequests_IDs[i]);
        this->preRequests.push_back(course);
    }
}

void Course::showCouse_Report()
{
    this->buildCourse();
    int numberOfStudents = 0;
    int numberOfTAs = 0;
    std::ifstream Registerd_courses_File("Database/Registered_courses.txt");
    if (Registerd_courses_File.fail())
    {
        std::cerr << "Error Opening Registered Courses File While Making Course Report, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(Registerd_courses_File, line))
    {
        std::vector<std::string> data = readLine(line);
        if (data[1] == this->id)
        {
            numberOfStudents++;
        }
    }
    Registerd_courses_File.close();

    std::ifstream TA_courses_File("Database/TA_courses.txt");
    if (TA_courses_File.fail())
    {
        std::cerr << "Error Opening Teacher Assistant Courses File While Making Course Report, System Faild!" << std::endl;
        return;
    }
    while (getline(TA_courses_File, line))
    {
        std::vector<std::string> data = readLine(line); // data = {TA_id, course_id}
        if (data[1] == this->id)
        {
            numberOfTAs++;
        }
    }

    std::cout << "Course Code " << this->code << " - Total Assignments: " << (int)this->assignments.size();
    std::cout << " - With " << numberOfStudents << " Students Registered";
    std::cout << "  And " << numberOfTAs << " Teacher Assistants";
    std::cout << std::endl;
    this->showCourse_preRequests();
}

void Course::showCourse_preRequests()
{
    std::cout << "This Course Prerequests: ";
    if ((int)this->preRequests.size() == 0)
    {
        std::cout << "None." << std::endl;
        return;
    }
    for (int i = 0; i < (int)this->preRequests.size(); i++)
    {
        std::cout << preRequests[i].get_name() << " " << preRequests[i].get_code() << ", ";
    }
    std::cout << "." << std::endl;
}

std::vector<Course> get_IdenticalCourses_From(std::vector<Course> &my, std::vector<Course> &other)
{ // this function gets all from others that doesn't exist in my.
    std::vector<Course> result;
    for (int i = 0; i < (int)other.size(); i++)
    {

        bool found_i = false;
        for (int j = 0; j < (int)my.size(); j++)
        {
            if (other[i].get_id() == my[j].get_id())
            {
                found_i = true;
                break;
            }
        }
        if (found_i == false)
        {
            result.push_back(other[i]);
        }
    }
    return result;
}

void Course::addAssignment()
{
    std::string Assignment_id, Assignment_parentCourse, Assignment_totalGrade, Assignment_paragraph;
    std::cout << "Enter The Assignment Text: ";
    getline(std::cin, Assignment_paragraph);
    std::cout << "Enter Positive Integer For Assignment Total Grade: ";
    getline(std::cin, Assignment_totalGrade);
    while (!isNumber(Assignment_totalGrade))
    {
        std::cout << "Invalid input, please try again!" << std::endl;
        std::cout << "Enter Positve Integer For Assignment Total Grad: " << std::endl;
        getline(std::cin, Assignment_totalGrade);
    }
    std::string year, month, day;
    bool validDate_input = false;
    while (validDate_input == false)
    {
        std::cout << "Enter Space Seperated The Year, Month, And Day Of Desired Deadline For Assignmnt: ";
        std::cin >> year >> month >> day;
        Date currentDate;
        currentDate = GetCurentDate();
        while (!(isNumber(year) && isNumber(month) && isNumber(day)))
        {
            std ::cout << "Invalid Input! " << std::endl;
            std::cout << "Enter Space Seperated The Year, Month, And Day Of Desired Deadline For Assignmnt: ";
            std::cin >> year >> month >> day;
        }
        Date desired_date(std::stoi(day), std::stoi(month), std::stoi(year));
        if (desired_date > currentDate)
        {
            validDate_input = true;
        }
    }
    std::cin.ignore();
    Date Assignment_Date(std::stoi(day), std::stoi(month), std::stoi(year));
    SystemController ems;
    Assignment_id = ems.get_assignment_ID();
    ems.increase_assignment_ID();
    Assignment_parentCourse = this->id;

    Assignment assignment(Assignment_id, Assignment_parentCourse, Assignment_totalGrade, Assignment_paragraph, Assignment_Date);
    std::vector<std::string> vc_assignmentData = assignment.putOnVector();
    std::vector<std::string> vc_course_assignments_Linker = {this->id, Assignment_id};
    std::string path_1 = "Database/Assignments.txt";
    appendOnFile(path_1, vc_assignmentData);
}
void Course::view_courseMenu(std::string instructor_id)
{
    while (true)
    {
        this->buildCourse();
        this->showCourse_Details();
        std::string choice;
        std::cout << "1- View Assignments" << std::endl;
        std::cout << "2- Create Assignment" << std::endl;
        std::cout << "3- View Course Report" << std::endl;
        std::cout << "4- Invite Teacher Assistan" << std::endl;
        std::cout << "5- Back" << std::endl;
        if (!input_number(choice, {1, 5}))
        {
            continue;
        }
        if (choice == "1")
        {
            if (this->getNumberOfAssignments() == 0)
            {
                std::cout << "There Are No Assignments!" << std::endl;
                continue;
            }
            std::string assignment_index;
            this->showCourse_Details();
            std::cout << "Enter The Assginments You Want To Show" << std::endl;
            if (!input_number(assignment_index, {1, this->getNumberOfAssignments()}))
            {
                continue;
            }
            Assignment assignment = this->assignments[std::stoi(assignment_index) - 1];
            assignment.view_assignmentMenu();
        }
        else if (choice == "2")
        {
            this->addAssignment();
        }
        else if (choice == "3")
        {
            this->showCouse_Report();
        }
        else if (choice == "4")
        {
            this->invite_TA(instructor_id);
        }
        else if (choice == "5")
        {
            return;
        }
    }
}
void Course::invite_TA(std::string instructor_id)
{
    Account account; 
    account.setAccountByID(std::stoi(instructor_id));
    if(account.get_accountType() == "Teacher Assistant"){
        std::cout << "You Are Not Allowed Yet To Invite Teacher Assistants To This Course." << std::endl;
        return;
    }
    this->buildCourse();
    this->showCourse_Main();

    std::string course_id = this->id;

    SystemController ems;
    std::vector<Account> global_TA = ems.listTA();
    std::vector<Account> available_TA;
    std::string TA_courses_File = "Database/TA_courses.txt";
    std::string TA_invitations_File = "Database/TA_invitations.txt";
    for (int i = 0; i < (int)global_TA.size(); i++)
    {

        std::vector<std::string> vc_data_TA_AlreadyTeaching = {global_TA[i].get_id(), course_id};
        std::vector<std::string> vc_data_invite = {instructor_id, global_TA[i].get_id(), course_id};
        if (vectorExistInFile(TA_courses_File, vc_data_TA_AlreadyTeaching) == false && vectorExistInFile(TA_invitations_File, vc_data_invite) == false)
        {
            available_TA.push_back(global_TA[i]);
        }
    }
    if ((int)available_TA.size() == 0)
    {
        std::cout << "Ther Are No Teacher Assistants In The System Yet." << std::endl;
        return;
    }
    
    std::cout << "Select The Teacher Assistant You Want To Invite: ";
    std::string TA_index;
    if (!input_number(TA_index, {1, (int)available_TA.size()}))
    {
        return;
    }

    std::vector<std::string> vc_data_invite = {instructor_id, available_TA[std::stoi(TA_index) - 1].get_id(), course_id};
    std::string path = "Database/TA_invitations.txt";
    appendOnFile(path, vc_data_invite);
}
