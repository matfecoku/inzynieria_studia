#pragma once
#include "UniversitySystem.h"
#include "Course.h"
#include "Student.h"

class Application {
private:
	UniversitySystem m_uniSystem;

public:
	void run() {
		Course* mathCourse = new Course("Inzynieria Oprogramowania", 1, 2, 20);
		m_uniSystem.addCourse(mathCourse);

		Student* s1 = new Student(1, "Jan Kowalski");
		Student* s2 = new Student(2, "Adam Nowak");
		Student* s3 = new Student(3, "Piotr Wisniewski");

		m_uniSystem.addStudent(s1);
		m_uniSystem.addStudent(s2);
		m_uniSystem.addStudent(s3);

		std::cout << "\nZapis przed otwarciem:" << std::endl;

		mathCourse->registerStudent(s1);

		std::cout << "GetStudentCount: " << mathCourse->getStudentCount() << std::endl;

		std::cout << "\nOtwarcie zapisow i zapelnienie:" << std::endl;

		m_uniSystem.openEnrollmentForCourse(mathCourse);

		mathCourse->registerStudent(s1);
		std::cout << "GetStudentCount: " << mathCourse->getStudentCount() << std::endl;
		mathCourse->registerStudent(s2);
		std::cout << "GetStudentCount: " << mathCourse->getStudentCount() << std::endl;

		std::cout << "\nBrak miejsc:" << std::endl;

		mathCourse->registerStudent(s3);

		std::cout << "GetStudentCount: " << mathCourse->getStudentCount() << std::endl;

		delete mathCourse;
		delete s1;
		delete s2;
		delete s3;
	}
};