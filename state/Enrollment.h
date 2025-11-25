#pragma once
#include "Student.h"
#include "Course.h"
#include "Date.h"

class Enrollment {
private:
	Student* m_student;
	Course* m_course;
	Date m_enrollmentDate;

public:
	Enrollment(Student* student, Course* course, Date date)
		: m_student(student), m_course(course), m_enrollmentDate(date) {}

	Student* getStudent() { return m_student; }
};