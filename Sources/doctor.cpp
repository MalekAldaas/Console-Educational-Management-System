#include "../Headers/account.h"
#include "../Headers/doctor.h"
#include "../Headers/helper_func.h"
#include "../Headers/course.h"
#include "../Headers/system_controller.h"
#include "../Headers/login.h"
#include "../Headers/date.h"
#include "../Headers/assignment.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

Doctor::Doctor()
{
    this->account.initialize();
}
Doctor::Doctor(Account &_account)
{
    this->account = _account;
}
Doctor::Doctor(std::string ID)
{
    std::ifstream Accounts_File("Database/Accounts.txt");
    if (Accounts_File.fail())
    {
        std::cerr << "Error Opening Accounts File, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(Accounts_File, line))
    {
        Account tem_account(line);
        if (tem_account.get_id() == ID)
        {
            this->account = tem_account;
            return;
        }
    }
    Accounts_File.close();
    this->build();
}
void Doctor::run()
{
    this->build();
    while (true)
    {
        std::cout << "1- List Courses" << std::endl;
        std::cout << "2- Create Courses" << std::endl;
        std::cout << "3- List My Courses" << std::endl;
        std::cout << "4- List System Users" << std::endl;
        std::cout << "5- Send Message" << std::endl;
        std::cout << "6- Logout" << std::endl;

        std::string choice;
        if (input_number(choice, {1, 6}) == true)
        {
            if (choice == "1")
            {
                this->listCourses();
            }
            else if (choice == "2")
            {
                this->addCourse();
            }
            else if (choice == "3")
            {
                this->view_Course();
            }
            else if (choice == "4")
            {
                SystemController ems; 
                ems.listUsers() ;
            }
            else if (choice == "5")
            {
                this->account.sendMessage();
            }
            else if (choice == "6")
            {
                logout(this->account);
                return;
            }
        }
    }
}

void Doctor::listCourses()
{
    SystemController ems;
    std::vector<Course> globalCourses = ems.listCourses();
    std::vector<Course> coursesList = get_IdenticalCourses_From(this->myCourses, globalCourses);
    if((int)coursesList.size() == 0){
        std::cout << "Ther Are No Courses, Please Check Again Later." << std::endl; 
        return ;
    }
    for (int i = 0; i < (int)coursesList.size(); i++)
    {
        std::cout << i + 1 << "- ";
        coursesList[i].showCourse_Main();
    }
}

void Doctor::addCourse()
{
    std::string course_name, course_password = "-1", course_id, course_code, course_paragraph, course_instructor;
    std::vector<Course> preRequests;
    std::string need_password = "2";
    std::cout << "Enter Course Name: ";
    getline(std::cin, course_name);
    while (!(need_password == "0" || need_password == "1"))
    {
        std::cout << "Enter 1 If You Want To Have Password On The Course, Otherwise 0, or -1 to exit: ";
        getline(std::cin, need_password);
        if (need_password == "-1")
            return;
    }
    if (need_password == "1")
    {
        std::cout << "Enter The Course Password: ";
        getline(std::cin, course_password);
        
    }
    SystemController ems;
    std::vector<Course> courseList = ems.listCourses();

    for (int i = 0; i < (int)courseList.size(); i++)
    {
        std::cout << i + 1 << " ";
        courseList[i].showCourse_Main();
    }
    std::string choice_line;
    std::set<std::string> choices;
    std::cout << "Enter All the prerequest Courses by Their Indexes Space Seperated, Becareful, You Can't Edit The Course Prerequest Afterwards!" << std::endl;
    getline(std::cin, choice_line);
    choice_line += " ";
    std::string tem = "";
    for (int i = 0; i < (int)choice_line.size(); i++)
    {
        char c = choice_line[i];
        if (c == ' ')
        {
            if ((int)tem.size() > 0)
            {
                choices.insert(tem);
                tem = "";
            }
        }
        else
        {
            tem += choice_line[i];
        }
    }
    for (auto index : choices)
    {
        int idx = std::stoi(index);
        if (1 <= idx && idx <= (int)courseList.size())
        {
            preRequests.push_back(courseList[idx - 1]);
        }
    }
    std::cout << "Enter Post For The Course: ";
    getline(std::cin, course_paragraph);

    course_id = ems.get_course_ID();
    ems.increase_course_ID();
    course_code = "SCS-" + course_id;
    course_instructor = this->account.get_id();
    Course new_course(course_id, course_name, course_password, course_code, course_instructor, course_paragraph, preRequests);

    std::vector<std::string> course_mainData = new_course.putOnVector();
    std::vector<std::string> course_prereqData;
    for (int i = 0; i < (int)preRequests.size(); i++)
    {
        course_prereqData.push_back(course_id + "," + preRequests[i].get_id());
        std::string path_ = "Database/Course_prerequests.txt";
        appendOnFile(path_, course_prereqData);
        course_prereqData.clear();
    }
    std::string path_ = "Database/Courses.txt";
    appendOnFile(path_, course_mainData);
}

void Doctor::listMyCourses()
{
    this->build();
    if ((int)this->myCourses.size() == 0)
    {
        std::cout << "There Are No Courses To Show." << std::endl;
        return;
    }
    for (int i = 0; i < (int)this->myCourses.size(); i++)
    {
        std::cout << i+1 << ":  " ;
        this->myCourses[i].showCourse_Main();
    }
}

void Doctor::view_Course()
{
    while (true)
    {
        this->listMyCourses();
        this->build();
        if ((int)this->myCourses.size() == 0)
        {
            return;
        }
        std::string choice, choice_index;
        std::cout << "1- View Course" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "1")
        {
            std::cout << "Enter The Number Of Course You Want To View" << std::endl;
            if (!input_number(choice_index, {1, (int)this->myCourses.size()}))
            {
                return;
            }
            this->myCourses[std::stoi(choice_index) - 1].view_courseMenu(this->account.get_id());
        }
        else if (choice == "2")
        {
            return;
        }
    }
}

void Doctor::build()
{
    this->myCourses.clear() ;
    std::ifstream courses_File("Database/Courses.txt");
    if (courses_File.fail())
    {
        std::cerr << "Error Opening Course File While Building Doctor Data, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(courses_File, line))
    {
        Course course(line);
        if (course.get_instructor() == this->account.get_id())
        {
            this->myCourses.push_back(course);
        }
    }
    courses_File.close();
    for (int i = 0; i < (int)this->myCourses.size(); i++)
    {
        this->myCourses[i].buildCourse();
    }
}

