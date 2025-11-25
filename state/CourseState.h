#pragma once
#include <string>

class Course;
class Student;

class CourseState {
public:
	virtual ~CourseState() {}
	virtual bool enroll(Course* course, Student* student) = 0;
	virtual std::string getStateName() const = 0;
};