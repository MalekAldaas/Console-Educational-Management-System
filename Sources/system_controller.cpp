#include "../Headers/system_controller.h"
#include "../Headers/account.h"
#include "../Headers/student.h"
#include "../Headers/doctor.h"
#include "../Headers/teacher_assistant.h"
#include "../Headers/login.h"
#include "../Headers/signup.h"
#include "../Headers/helper_func.h"
#include "../Headers/manager.h"
#include "../Headers/course.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

SystemController::SystemController()
{
    std::ifstream system_File("Database/System_info.txt");
    if (system_File.fail())
    {
        std::cerr << "Erorr, System Failed While constructing SYSTEM from System Info File!." << std::endl;
        return;
    }
    std::string line;
    getline(system_File, line);
    std::vector<std::string> data = readLine(line);
    this->u_account_id = data[0];
    this->u_course_id = data[1];
    this->u_comment_id = data[2];
    this->u_assignment_id = data[3];
    this->u_solution_id = data[4];
}

std::string SystemController::get_account_ID() { return this->u_account_id; }
std::string SystemController::get_course_ID() { return this->u_course_id; }
std::string SystemController::get_comment_ID() { return this->u_comment_id; }
std::string SystemController::get_assignment_ID() { return this->u_assignment_id; }
std::string SystemController::get_solution_ID() { return this->u_solution_id; }

std::vector<std::string> SystemController::putOnVector()
{
    std::vector<std::string> data;
    data.push_back(this->u_account_id);
    data.push_back(this->u_course_id);
    data.push_back(this->u_comment_id);
    data.push_back(this->u_assignment_id);
    data.push_back(this->u_solution_id);
    return data;
}

void SystemController::updateSystem()
{
    std::ofstream systemInfo_File("Database/System_info.txt");
    if (systemInfo_File.fail())
    {
        std::cerr << "Erorr, System failed while uppdating System Info File!.";
        return;
    }
    std::vector<std::string> data = this->putOnVector();
    for (int i = 0; i < (int)data.size(); i++)
    {
        systemInfo_File << data[i] << ",";
    }
    systemInfo_File.close();
}

void SystemController::fetchdata()
{
    std::ifstream systemInfo_File("Database/System_info.txt");
    if (systemInfo_File.fail())
    {
        std::cerr << "Error Fetching Data From System Information File, System Failed!" << std::endl;
        return;
    }
    std::string line;
    getline(systemInfo_File, line);
    systemInfo_File.close();
    std::vector<std::string> data = readLine(line);
    this->u_account_id = data[0];
    this->u_course_id = data[1];
    this->u_comment_id = data[2];
    this->u_assignment_id = data[3];
    this->u_solution_id = data[4];
}

void SystemController::run()
{
    Account account;
    while (account.empty())
    {
        std::cout << "Menu: " << std::endl;
        std::cout << "1- Login" << std::endl;
        std::cout << "2- Signup" << std::endl;
        std::cout << "3- Exit" << std::endl;
        std::string choice;
        if (input_number(choice, {1, 3}) == true)
        {
            if (choice == "1")
            {
                login(account);
            }
            else if (choice == "2")
            {
                signup(account);
            }
            else if (choice == "3")
            {
                return;
            }
        }
        if (account.get_accountValidation() == "0")
        {
            std::cout << "Your Account Needs To Be Aproved By The Manager." << std::endl;
        }
        else if (account.get_accountType() == "Student")
        {
            Student student(account);
            student.run();
        }
        else if (account.get_accountType() == "Doctor")
        {
            Doctor doctor(account);
            doctor.run();
        }
        else if (account.get_accountType() == "MANAGER")
        {
            Manager manager(account);
            manager.run();
        }
        else if (account.get_accountType() == "Teacher Assistant")
        {
            Teacher_Assistant teacher_assistant(account);
            teacher_assistant.run();
        }
        account.initialize();
    }
}

void SystemController::increase_account_ID()
{
    this->fetchdata();
    this->u_account_id = std::to_string(std::stoi(this->u_account_id) + 1);
    this->updateSystem();
}

void SystemController::increase_course_ID()
{
    this->fetchdata();
    this->u_course_id = std::to_string(std::stoi(this->u_course_id) + 1);
    this->updateSystem();
}

void SystemController::increase_comment_ID()
{
    this->fetchdata();
    this->u_comment_id = std::to_string(std::stoi(u_comment_id) + 1);
    this->updateSystem();
}
void SystemController::increase_assignment_ID()
{
    this->fetchdata();
    this->u_assignment_id = std::to_string(std::stoi(u_assignment_id) + 1);
    this->updateSystem();
}

void SystemController::increase_solution_ID()
{
    this->fetchdata();
    this->u_solution_id = std::to_string(std::stoi(u_solution_id) + 1);
    this->updateSystem();
}

std::vector<Course> SystemController::listCourses()
{
    std::vector<Course> result;
    std::ifstream courses_File("Database/Courses.txt");
    if (courses_File.fail())
    {
        std::cerr << "Error Opening Courses File While Listing Courses, System Faild!" << std::endl;
        return result;
    }
    std::string line;
    while (getline(courses_File, line))
    {
        Course course(line);
        result.push_back(course);
    }
    courses_File.close();
    return result;
}
void SystemController::listUsers()
{
    std::ifstream accounts_File("Database/Accounts.txt");
    if (accounts_File.fail())
    {
        std::cerr << "Error Opening Accounts File While Listing Accounts, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(accounts_File, line))
    {
        Account account(line);
        if (account.get_accountValidation() == "1")
        {
            std::cout << "ID: " << account.get_id() << "  Name: " << account.get_name() << "  Username: " << account.get_username() << "   Email: " << account.get_email() << "   Role: " << account.get_accountType() << std::endl;
        }
    }
    accounts_File.close() ;
}
std::vector<Account> SystemController::listTA(){
    std::vector<Account> result ;
    std::ifstream accounts_File("Database/Accounts.txt");
    if(accounts_File.fail()){
        std::cerr << "Error Opening Accounts File While Reqeuesting TA List, System Faild!" << std::endl;
        return result ;
    }
    std::string line ;
    while(getline(accounts_File, line)){
        Account account(line);
        if(account.get_accountType() == "Teacher Assistant" && account.get_accountValidation() == "1"){
            result.push_back(account);
        }
    }
    accounts_File.close();
    return result ;
}