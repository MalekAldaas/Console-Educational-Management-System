#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include<string>
#include<vector>

class SystemController{
    private :
        std::string u_account_id, u_course_id, u_post_id,
                    u_assignment_id, u_comment_id, u_solution_id;  
    public :
        void run() ;
        std::string get_account_ID() ;
        std::string get_course_ID() ;
        std::string get_post_ID() ;
        std::string get_assignment_ID() ;
        std::string get_comment_ID() ;
        std::string get_solution_ID() ;

        void set_account_ID(const std::string&) ;
        void set_course_ID(const std::string&) ;
        void set_post_ID(const std::string&) ;
        void set_assignment_ID(const std::string&) ;
        void set_comment_ID(const std::string&) ;
        void set_solution_ID(const std::string&) ;

        std::vector<std::string> putOnVector() ;

        void updateSystem(); 
        void fetchdata() ;

} ;




#endif