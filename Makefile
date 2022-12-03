CPPFLAGS = -g 
all: a.out
	./a.out
a.out: account.o date.o student.o doctor.o helper_func.o system_controller.o manager.o login.o signup.o teacher_assistant.o EMS-console.o
	g++ account.o date.o student.o doctor.o helper_func.o system_controller.o manager.o login.o signup.o teacher_assistant.o EMS-console.o
account.o: Sources/account.cpp 
	g++ Sources/account.cpp -c $(CPPFLAGS)
date.o: Sources/date.cpp 
	g++ Sources/date.cpp -c $(CPPFLAGS)
student.o : Sources/student.cpp
	g++ Sources/student.cpp -c $(CPPFLAGS) 
doctor.o : Sources/doctor.cpp
	g++ Sources/doctor.cpp -c $(CPPFLAGS)
helper_func.o : Sources/helper_func.cpp
	g++ Sources/helper_func.cpp -c $(CPPFLAGS) 
system_controller.o : Sources/system_controller.cpp
	g++ Sources/system_controller.cpp -c $(CPPFLAGS) 
manager.o : Sources/manager.cpp
	g++ Sources/manager.cpp -c $(CPPFLAGS)
login.o : Sources/login.cpp
	g++ Sources/login.cpp -c $(CPPFLAGS)
signup.o : Sources/signup.cpp
	g++ Sources/signup.cpp -c $(CPPFLAGS)
teacher_assistant.o :Sources/teacher_assistant.cpp
	g++ Sources/teacher_assistant.cpp -c $(CPPFLAGS) 
