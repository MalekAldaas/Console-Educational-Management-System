#include "../Headers/student.h"
#include "../Headers/account.h"
#include "../Headers/helper_func.h"
#include "../Headers/system_controller.h"
#include "../Headers/doctor.h"
#include "../Headers/solution.h"
#include "../Headers/assignment.h"

#include <vector>
#include <string>

Student::Student()
{
    this->account.initialize();
}
Student::Student(Account &_account)
{
    this->account = _account;
}

void Student::build()
{
    this->myCourses.clear();
    std::ifstream Registered_courses_File("Database/Registered_courses.txt");
    if (Registered_courses_File.fail())
    {
        std::cerr << "Error Opening Registered Courses File While Building Stduent Data, System Faild!" << std::endl;
        return;
    }
    std::string line;
    while (getline(Registered_courses_File, line))
    {
        std::vector<std::string> data = readLine(line);
        std::string account_id = data[0], course_id = data[1];
        Course course;
        course.setCourseByID(std::stoi(course_id));
        if (account_id == this->account.get_id())
        {
            this->myCourses.push_back(course);
        }
    }
    Registered_courses_File.close();
}

void Student::run()
{
    while (true)
    {
        this->build();
        std::cout << "1- List All Courses" << std::endl;
        std::cout << "2- List My Courses" << std::endl;
        std::cout << "3- List System Users" << std::endl;
        std::cout << "4- Send Message" << std::endl;
        std::cout << "5- Logout" << std::endl;
        std::string choice;
        if (!input_number(choice, {1, 5}))
        {
            continue;
        }
        if (choice == "1")
        {
            this->view_allCourse();
        }
        else if (choice == "2")
        {
            this->view_myCourses();
        }
        else if (choice == "3")
        {
            SystemController ems;
            ems.listUsers();
        }
        else if (choice == "4")
        {
            this->account.sendMessage();
        }
        else if (choice == "5")
        {
            return;
        }
    }
}
void Student::listMyCourses()
{
    if ((int)this->myCourses.size() == 0)
    {
        std::cout << "You Are Not Enrolled In Any Course." << std::endl;
        return;
    }
    for (int i = 0; i < (int)this->myCourses.size(); i++)
    {
        std::cout << i + 1 << ": "; 
        this->myCourses[i].showCourse_Main();
    }
}
void Student::view_myCourses()
{
    while (true)
    {
        this->listMyCourses();
        if ((int)this->myCourses.size() == 0)
        {
            return;
        }
        std::cout << "Enter The Number Of Course You Want To View." << std::endl;
        std::string choice, choice_index;
        std::cout << "1- View Course" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "1")
        {
            if (!input_number(choice_index, {1, (int)this->myCourses.size()}))
            {
                continue;
            }
            this->view_courseMenu(this->myCourses[std::stoi(choice_index) - 1]);
        }
        else if (choice == "2")
        {
            return;
        }
    }
}
void Student::view_courseMenu(Course &course)
{
    while (true)
    {
        course.buildCourse();
        course.showCourse_Main();
        std::cout << "Course Has " << (int)course.assignments.size() << " Assignments:" << std::endl;
        for (int i = 0; i < (int)course.assignments.size(); i++)
        {
            std::cout << i + 1 << "- Assignment ";
            Solution solution;
            solution = course.assignments[i].isStudentHasSubmit(this->account.get_id());
            std::string grade;
            if (grade == "-2")
            {
                // Not Answered
                std::cout << "(Not Submited)  ";
            }
            else if (grade == "-1")
            {
                // Not Graded Yet
                std::cout << "(Not Marked Yet) ";
            }
            else
            {
                // graded
                std::cout << grade << " ";
            }
            course.assignments[i].showAssignment();
        }
        std::string choice;
        std::cout << "1- UnRegister From Course" << std::endl;
        std::cout << "2- Show Assignment" << std::endl;
        std::cout << "3- Back";
        if (!input_number(choice, {1, 3}))
        {
            return;
        }
        if (choice == "1")
        {
            std::string unregister;
            std::cout << "Please Note, By Unregistering From Course Will Cause All Your Solutions To Be Deleted, Are You Sure You Want To Unregister? ( There Is NO RESTORING DATA)." << std::endl;
            std::cout << "Enter (1) To Unregister, (0) To Skip" << std::endl;
            if (!input_number(unregister, {0, 1}))
            {
                continue;
            }
            this->unRegisterFromCourse(course);
        }
        else if (choice == "2")
        {
            std::cout << "Enter Assignment Index" << std::endl;
            std::string assignment_index;
            if (!input_number(assignment_index, {1, (int)course.assignments.size()}))
            {
                return;
            }
            int idx = std::stoi(assignment_index) - 1;
            this->view_assignmentMenu(course.assignments[idx]);
        }
        else if (choice == "3")
        {
            return;
        }
    }
}

void Student::listCourses()
{
    SystemController ems;
    std::vector<Course> globalCourses = ems.listCourses();
    std::vector<Course> coursesList = get_IdenticalCourses_From(this->myCourses, globalCourses);
    if ((int)coursesList.size() == 0)
    {
        std::cout << "There Are No Courses, Please Check Again Late For Any New Courses." << std::endl;
        return;
    }
    for (int i = 0; i < (int)coursesList.size(); i++)
    {
        std::cout << i + 1 << ": ";
        coursesList[i].showCourse_Main();
    }
}
void Student::enrollCourse(Course &course)
{
    std::string enteredPassword;
    if(course.get_password() != "-1"){
        std::cout << "Please Enter The Password To This Course: " ; 
        getline(std::cin, enteredPassword);
    }
    if (course.get_password() == "-1" || course.get_password() == enteredPassword)
    {
        this->myCourses.push_back(course);
        std::cout << "You Enrolled In The Course Succesfuly." << std::endl;
        std::vector<std::string> data;
        data.push_back(this->account.get_id());
        data.push_back(course.get_id());
        std::string path_ = "Database/Registered_courses.txt";
        appendOnFile(path_, data);
        return;
    }
    else
    {

        std::cout << "This Course Is Locked With Password, Please Contact The Doctor ";
        Doctor doctor(course.get_instructor());
        std::cout << doctor.account.get_name() << " , ID: " << doctor.account.get_id() << " To Register In The Course." << std::endl;
        return;
    }
}

void Student::submitSolution(Assignment &assignment)
{
    Date currentDate;
    currentDate = GetCurentDate();

    if (assignment.get_deadLine() < currentDate)
    {
        std::cout << "You Can't Submit Any Solution To This Assignment, Deadline Has Reached" << std::endl;
        return;
    }
    else
    {
        std::cout << "Enter The Solution: ";
        std::string solution_paragraph;
        getline(std::cin, solution_paragraph);

        currentDate = GetCurentDate();
        if (currentDate > assignment.get_deadLine())
        {
            std::cout << "You Can't Submit Any Solution To This Assignment, Deadline Has Reached" << std::endl;
            return;
        }
        SystemController ems;
        std::string solution_grade = "-1";
        std::string solution_id = ems.get_solution_ID();
        std::string account_id = this->account.get_id();
        std::string assignment_id = assignment.get_id();
        std::string assignment_grade = assignment.get_totalGrade();

        Solution solution(solution_id, account_id, assignment_id, solution_paragraph, solution_grade, assignment_grade, currentDate);

        assignment.push_Solution(solution);
        ems.increase_solution_ID();
    }
}

void Student::unRegisterFromCourse(Course &course)
{
    std::vector<std::string> vc_courseReg = {this->account.get_id(), course.get_id()};
    std::string str_courseReg = putOnString(vc_courseReg);
    std::string courseReg_File = "Database/Registered_courses.txt";
    deleteFromFile(courseReg_File, str_courseReg);
    for (int i = 0; i < (int)course.assignments.size(); i++)
    {
        for (int j = 0; j < (int)course.assignments[i].solutions.size(); j++)
        {
            if (course.assignments[i].solutions[j].get_student_id() == this->account.get_id())
            {
                std::vector<std::string> vc_solutionData = course.assignments[i].solutions[j].putOnVector();
                std::string str_solutionData = putOnString(vc_solutionData);
                std::string solutions_File = "Database/Solutions.txt";
                deleteFromFile(solutions_File, str_solutionData);
            }
        }
    }
    course.buildCourse();
}
void Student::view_assignmentMenu(Assignment &assignment)
{
    while (true)
    {
        assignment.showAssignment();
        Solution student_solution = assignment.isStudentHasSubmit(this->account.get_id());
        std::string grade = student_solution.get_solutionGrade();
        if (grade == "-2")
        {
            std::cout << "(Not Submited)" << std::endl;
        }
        else if (grade == "-1")
        {
            std::cout << "(Your Submit Isn't Graded Yet)" << std::endl;
        }
        else
        {
            std::cout << "Your Grade: " << grade << "/" << assignment.get_totalGrade() << std::endl;
        }

        std::string choice;
        std::cout << "1- Submit Solution" << std::endl;
        std::cout << "2- Show My Solution" << std::endl;
        std::cout << "3- Back" << std::endl;
        if (!input_number(choice, {1, 3}))
        {
            continue;
        }
        if (choice == "1")
        {
            this->submitSolution(assignment);
        }
        else if (choice == "2")
        {
            Solution solution = assignment.isStudentHasSubmit(this->account.get_id());
            std::string grade = solution.get_solutionGrade();
            if (grade == "-2")
            {
                std::cout << "You Haven't Submited A Solution Yet." << std::endl;
                continue;
            }
            else
            {
                solution.showSolution();
            }
        }
        else if (choice == "3")
        {
            return;
        }
    }
}
void Student::view_allCourse()
{
    while (true)
    {
        SystemController ems;
        std::vector<Course> global_courses = ems.listCourses();
        std::vector<Course> availableCourses = get_IdenticalCourses_From(this->myCourses, global_courses);
        int listSize = (int)availableCourses.size();
        if (listSize == 0)
        {
            std::cout << "There Are No Courses, Please Check Later For Any Updates." << std::endl;
            return;
        }
        for (int i = 0; i < listSize; i++)
        {
            availableCourses[i].showCourse_Main();
        }
        std::string choice;
        std::cout << "1- View Course" << std::endl;
        std::cout << "2- Back" << std::endl;

        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "1")
        {
            std::string choice_index;
            if (!input_number(choice_index, {1, listSize}))
            {
                continue;
            }
            this->view_global_courseMenu(availableCourses[std::stoi(choice_index) - 1]);
        }
        else if (choice == "2")
        {
            return;
        }
    }
}
void Student::view_global_courseMenu(Course &course)
{
    course.showCourse_Main();
    course.showCourse_preRequests();
    std::cout << "This Course Has " << (int)course.assignments.size() << " Assignments." << std::endl;

    std::string choice;
    std::cout << "1- Register" << std::endl;
    std::cout << "2- Back" << std::endl;

    if (!input_number(choice, {1, 2}))
    {
        return;
    }

    if (choice == "1")
    {
        this->enrollCourse(course);
    }
    else if (choice == "2")
    {
        return;
    }
}
