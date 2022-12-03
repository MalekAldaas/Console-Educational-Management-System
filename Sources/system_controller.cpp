#include"../Headers/system_controller.h"
#include"../Headers/account.h"
#include"../Headers/student.h"
#include"../Headers/doctor.h"
#include"../Headers/teacher_assistant.h"
#include"../Headers/login.h"
#include"../Headers/signup.h"
#include"../Headers/helper_func.h" 
#include"../Headers/manager.h"

#include<string>
#include<iostream>
#include<vector>
#include<fstream>

std::string SystemController::get_account_ID() { return this->u_account_id ; }
std::string SystemController::get_course_ID() { return this->u_course_id ; }
std::string SystemController::get_post_ID() { return this->u_post_id ; }
std::string SystemController::get_comment_ID() { return this->u_comment_id ; }
std::string SystemController::get_assignment_ID() { return this->u_assignment_id ; }
std::string SystemController::get_solution_ID() { return this->u_solution_id ; }

void SystemController::set_account_ID(const std::string& ID){
    this->u_account_id = ID ;
}
void SystemController::set_assignment_ID(const std::string& ID){
    this->u_assignment_id = ID ;
}
void SystemController::set_comment_ID(const std::string& ID){
    this->u_comment_id = ID ;
}
void SystemController::set_course_ID(const std::string& ID){
    this->u_course_id = ID ;
}
void SystemController::set_post_ID(const std::string& ID){
    this->u_post_id = ID ;
}
void SystemController::set_solution_ID(const std::string& ID){
    this->u_solution_id = ID ;
}

std::vector<std::string> SystemController::putOnVector(){
    std::vector<std::string> data; 
    data.push_back(this->u_account_id) ;
    data.push_back(this->u_course_id) ;
    data.push_back(this->u_post_id) ;
    data.push_back(this->u_comment_id) ;
    data.push_back(this->u_assignment_id) ;
    data.push_back(this->u_solution_id) ;
    return data ;
}

void SystemController::updateSystem(){
    std::ofstream systemInfo_File("../Database/System_info.txt") ; 
    if(systemInfo_File.fail()){
        std::cerr << "System Faild!" ; 
        return ;
    }
    std::vector<std::string> data = this->putOnVector() ;
    for(int i = 0 ; i < (int)data.size() ; i++){
        systemInfo_File << data[i] << "," ;
    }
    systemInfo_File.close() ;
}

void SystemController::fetchdata(){
    std::ifstream systemInfo_File("../Database/System_info.txt") ;
    if(systemInfo_File.fail()){
        std::cerr << "System Faild!" ;
        return ;
    }
    std::string line ;
    getline(systemInfo_File, line) ;
    systemInfo_File.close() ;
    std::vector<std::string> data = readLine(line) ;
    this->u_account_id = data[0] ;
    this->u_course_id = data[1] ;
    this->u_post_id = data[2] ;
    this->u_comment_id = data[3] ;
    this->u_assignment_id = data[4] ;
    this->u_solution_id = data[5] ;
}

void SystemController::run(){
    Account account; 
    while(account.empty()){
        std::cout << "Menu: " << std::endl ;
        std::cout << "1- Login" << std::endl ; 
        std::cout << "2- Signup" << std::endl ; 
        std::cout << "3- Exit"; 
        std::string choice ;
        if(input_number(choice, {1,3}) == true){
            if(choice == "1"){
                std::string username_email, password; 
                std::cout << "Enter your you email/username :" ;
                getline(std::cin, username_email) ;
                std::cout << "Enter you password :" ;
                getline(std::cin, password) ;
                login(username_email, password, account); 
            }
            else if(choice == "2"){
                signup(account); 
            }
            else if(choice == "3"){
                return ;
            }
        }
        if(account.get_accountType() == "Student"){
            Student student(account); 
            student.run() ;
        }
        else if(account.get_accountType() == "Doctor"){
            Doctor doctor(account) ;
            doctor.run() ;
        }
        else if(account.get_accountType() == "MANAGER"){
            Manager manager(account) ;
            manager.run() ;
        }
        else if(account.get_accountType() == "Teacher Assistant"){
            Teacher_Assistant teacher_assistant(account) ;
            teacher_assistant.run(); 
        }
    }
}

