#include <iostream>
#include "Headers/login.h"
#include "Headers/signup.h"
#include "Headers/system_controller.h"
#include "Headers/course.h"
#include "Headers/comment.h"
#include "Headers/account.h"
#include "Headers/doctor.h"
#include "Headers/student.h"
#include "Headers/manager.h"
#include "Headers/helper_func.h"
#include "Headers/teacher_assistant.h"

int main()
{
    SystemController EMS;
    EMS.run();
    
    std::cout << "Byeeeee" << std::endl;
}