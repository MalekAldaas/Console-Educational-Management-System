CPPFLAGS = -g 
all: a.out
	./a.out
a.out: objects/account.o objects/date.o objects/student.o objects/doctor.o objects/helper_func.o objects/system_controller.o objects/manager.o objects/login.o objects/signup.o objects/teacher_assistant.o objects/EMS-console.o objects/course.o objects/assignment.o objects/solution.o
	g++ objects/account.o objects/date.o objects/student.o objects/doctor.o objects/helper_func.o objects/system_controller.o objects/manager.o objects/login.o objects/signup.o objects/teacher_assistant.o objects/EMS-console.o objects/course.o	objects/assignment.o objects/solution.o
objects/account.o: Sources/account.cpp 
	g++ Sources/account.cpp -c $(CPPFLAGS) -o objects/account.o
objects/date.o: Sources/date.cpp 
	g++ Sources/date.cpp -c $(CPPFLAGS) -o objects/date.o
objects/student.o : Sources/student.cpp
	g++ Sources/student.cpp -c $(CPPFLAGS) -o objects/student.o 
objects/doctor.o : Sources/doctor.cpp
	g++ Sources/doctor.cpp -c $(CPPFLAGS) -o objects/doctor.o
objects/helper_func.o : Sources/helper_func.cpp
	g++ Sources/helper_func.cpp -c $(CPPFLAGS) -o objects/helper_func.o
objects/system_controller.o : Sources/system_controller.cpp
	g++ Sources/system_controller.cpp -c $(CPPFLAGS) -o objects/system_controller.o
objects/manager.o : Sources/manager.cpp
	g++ Sources/manager.cpp -c $(CPPFLAGS) -o objects/manager.o
objects/login.o : Sources/login.cpp
	g++ Sources/login.cpp -c $(CPPFLAGS) -o objects/login.o
objects/signup.o : Sources/signup.cpp
	g++ Sources/signup.cpp -c $(CPPFLAGS) -o objects/signup.o
objects/teacher_assistant.o :Sources/teacher_assistant.cpp
	g++ Sources/teacher_assistant.cpp -c $(CPPFLAGS) -o objects/teacher_assistant.o
objects/EMS-console.o: EMS-console.cpp
	g++ EMS-console.cpp -c $(CPPFLAGS) -o objects/EMS-console.o
objects/course.o: Sources/course.cpp
	g++ Sources/course.cpp -c $(CPPFLAGS) -o objects/course.o
objects/assignment.o: Sources/assignment.cpp
	g++ Sources/assignment.cpp -c $(CPPFLAGS) -o objects/assignment.o
objects/solution.o : Sources/solution.cpp
	g++ Sources/solution.cpp -c $(CPPFLAGS) -o objects/solution.o 