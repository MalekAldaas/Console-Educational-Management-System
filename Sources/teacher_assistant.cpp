#include "../Headers/teacher_assistant.h"
#include "../Headers/account.h"
#include "../Headers/helper_func.h"
#include "../Headers/doctor.h"
#include "../Headers/course.h"
#include "../Headers/system_controller.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

Teacher_Assistant::Teacher_Assistant()
{
    this->account.initialize();
}
Teacher_Assistant::Teacher_Assistant(Account &_account)
{
    this->account = _account;
}
void Teacher_Assistant::run()
{
    while (true)
    {
        this->build();
        std::cout << "1- List All Courses" << std::endl;
        std::cout << "2- View My Courses" << std::endl;
        std::cout << "3- List System Users" << std::endl;
        std::cout << "4- Show Coure Invitations" << std::endl;
        std::cout << "5- Send Message" << std::endl;
        std::cout << "6- Logout" << std::endl;
        std::string choice;
        input_number(choice, {1, 4});

        if (choice == "1")
        {
            this->view_allCourses();
        }
        else if (choice == "2")
        {
            this->view_myCourse();
        }
        else if (choice == "3")
        {
            SystemController ems;
            ems.listUsers();
        }
        else if (choice == "4")
        {
            this->showInvitations();
        }
        else if (choice == "5")
        {
            this->account.sendMessage();
        }
        else if (choice == "6")
        {
            return;
        }
    }
}

std::vector<std::string> Teacher_Assistant::loadInvitations()
{
    std::vector<std::string> result;
    std::ifstream TA_invitations_File("Database/TA_invitations.txt");
    if (TA_invitations_File.fail())
    {
        std::cerr << "Error Opening TA Invitations File, System Faild!" << std::endl;
        return result;
    }
    std::string line;
    while (getline(TA_invitations_File, line))
    {
        std::vector<std::string> vc_line = readLine(line);
        if (vc_line[1] == this->account.get_id())
        {
            result.push_back(line);
        }
    }
    TA_invitations_File.close();
    return result;
}

void Teacher_Assistant::showInvitations()
{
    while (true)
    {
        this->build();
        std::vector<std::string> invitationsLines = this->loadInvitations();
        if ((int)invitationsLines.size() == 0)
        {
            std::cout << "There Are No Invitations." << std::endl;
            return;
        }
        for (int i = 0; i < (int)invitationsLines.size(); i++)
        {
            std::vector<std::string> data = readLine(invitationsLines[i]);
            Doctor doctor(data[0]);
            Course course;
            course.setCourseByID(std::stoi(data[2]));

            std::cout << i + 1 << ": "
                      << "Dr. " << doctor.account.get_name() << " Has Invited You To " << course.get_name() << "  " << course.get_code() << std::endl;
        }

        std::string choice, choice_index;
        std::cout << "1- Select Inviation" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "2")
        {
            return;
        }
        // selected an invitation.
        if (!input_number(choice_index, {1, (int)invitationsLines.size()}))
        {
            return;
        }
        int idx = std::stoi(choice_index) - 1;
        std::vector<std::string> vc_invitation = readLine(invitationsLines[idx]);
        std::cout << "1- Accept" << std::endl;
        std::cout << "2- Reject" << std::endl;
        std::cout << "3- Back" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            continue;
        }
        if (choice == "1")
        {
            std::vector<std::string> vc_acceptenceData = {this->account.get_id(), vc_invitation[2]};
            std::string path = "Database/TA_courses.txt";
            appendOnFile(path, vc_acceptenceData);
        }
        else if (choice == "2")
        {
            return;
        }
        // accept or rejct will delete the invitation.
        std::string path = "Database/TA_invitations.txt";
        deleteFromFile(path, invitationsLines[idx]);
    }
}

void Teacher_Assistant::view_allCourses()
{
    while (true)
    {
        SystemController ems;
        std::vector<Course> globalCourses = ems.listCourses();
        for (int i = 0; i < (int)globalCourses.size(); i++)
        {
            std::cout << i + 1 << ": ";
            globalCourses[i].showCourse_Main();
        }
        if ((int)globalCourses.size() == 0)
        {
            std::cout << "There Are No Courses." << std::endl;
            return;
        }
        std::string choice;
        std::cout << "1- View Course" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choice, {1, (int)globalCourses.size()}))
        {
            continue;
        }
    }
}

void Teacher_Assistant::build()
{
    this->myCourses.clear() ;
    std::string TA_courses_filePath = "Database/TA_courses.txt";
    std::ifstream TA_courses_File(TA_courses_filePath);
    if (TA_courses_File.fail())
    {
        std::cerr << "Error Opening Teacher Assistant Courses File While Building Data, System Faild!." << std::endl;
        return;
    }
    std::string line;
    while (getline(TA_courses_File, line))
    {
        std::vector<std::string> data = readLine(line);
        std::string TA_ID, course_ID;
        TA_ID = data[0];
        course_ID = data[1];
        if (TA_ID == this->account.get_id())
        {
            Course course;
            course.setCourseByID(std::stoi(course_ID));
            this->myCourses.push_back(course);
        }
    }
    TA_courses_File.close();
}

void Teacher_Assistant::view_myCourse()
{
    while (true)
    {
        this->build();
        for (int i = 0; i < (int)this->myCourses.size(); i++)
        {
            std::cout << i + 1 << ": ";
            this->myCourses[i].showCourse_Main();
        }
        if ((int)this->myCourses.size() == 0)
        {
            std::cout << "There Are No Courses To Show." << std::endl;
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
            std::cout << "Enter The Course You Want To View." << std::endl;
            if (!input_number(choice_index, {1, (int)this->myCourses.size()}))
            {
                continue;
            }
            this->myCourses[std::stoi(choice_index)-1].view_courseMenu(this->account.get_id());
        }
        else if (choice == "2")
        {
            return;
        }
    }
}
