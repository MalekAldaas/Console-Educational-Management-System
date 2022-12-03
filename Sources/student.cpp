#include"../Headers/student.h"
#include"../Headers/account.h"
#include"../Headers/helper_func.h" 

#include<vector>
#include<string>


Student::Student() {
    this->account.initialize() ;
} 
Student::Student(const Account& _account){
    this->account = _account ;
}

void Student::run(){
    std::cout << "1- Register in Course" << std::endl;
    std::cout << "2- List My Courses" << std::endl;
    std::cout << "3- View My Courses" << std::endl;
    std::cout << "4- Grades Report" << std::endl;
    std::cout << "5- Logout" << std::endl;
    std::string choice ;
    input_number(choice, {1,5}) ;
    
}
