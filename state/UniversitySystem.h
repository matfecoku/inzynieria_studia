#pragma once
#include <vector>
#include "Student.h"
#include "Course.h"
#include "OpenState.h"
#include "ClosedState.h"

class UniversitySystem {
private:
	std::vector<Student*> m_vec_students;
	std::vector<Course*> m_vec_courses;

public:
	void addStudent(Student* s) {
		m_vec_students.push_back(s);
	}

	void addCourse(Course* c) {
		m_vec_courses.push_back(c);
	}

	void openEnrollmentForCourse(Course* c) {
		c->setState(new OpenState());
	}

	void closeEnrollmentForCourse(Course* c) {
		c->setState(new ClosedState());
	}
};