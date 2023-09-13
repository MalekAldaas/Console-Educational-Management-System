# Console Educational Management System
EMS is a system that manage the educational processes that happen between professors, teacher assistants and students. 
Basically build using primary concepts of Object Oriented Programming using C++

## Actors
- Manager
- Professor / Doctor
- Teacher Assistant
- Student

## Use Cases
- Manager:
  - Show signup requests from Doctors ans TAs.
  - Accept or decline signup requests.
  - List all system users, show user details, ban or unban user.
  - Send messages to system users.
- Professor / Doctor
    - Create new course.
    - Add assginment to courses he supervise.
    - Show course assignments.
    - List solutions on some assignemnt, and grade it.
    - invite Teacher Assistants to course.
    - Generate Grade Report for some course.
- Teacher Assistant
    - List course supervising invitations, Accept or decline the invite.
    - View courses he supervise, create assignments.
    - List solutions on some assignemnt, and grade it.
    - Generate grade report
    - Send messages to system users.
- Student
    - Show courses list
        - all courses.
        - courses that student is enrolled in.
        - show unenrolled courses that student has fulfilled the prerequisite courses..
    - Enroll in course, only if course conditions are met.
    - View course assignments, submit solution for some assginment.
    - send messages to system users.
---
## Interface
![EMS_01](https://github.com/MalekAldaas/Console-Educational-Management-System/assets/82756026/5cea1289-b954-4558-a724-c9a9a0309441)
![EMS_03](https://github.com/MalekAldaas/Console-Educational-Management-System/assets/82756026/0443043b-8c50-4115-9de7-b3d993f4684a)
![EMS_02](https://github.com/MalekAldaas/Console-Educational-Management-System/assets/82756026/8ff5f854-6ac8-4102-8df4-494531905870)
![EMS_04](https://github.com/MalekAldaas/Console-Educational-Management-System/assets/82756026/acc2b330-2305-4065-8ea4-75c8e89f7efc)

## How to work on your pc
- clone the project on your pc.
- open terminal in project folder
- type the command "make" with out quets, and here we go.

Note: Type "ADMIN" for both username and password at login stage to login as Manager.

---
