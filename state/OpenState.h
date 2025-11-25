#pragma once
#include "CourseState.h"
#include <iostream>
#include "Date.h"
#include <chrono>
#include "FullState.h"
#include <string>
#include <ctime>

class Enrollment;

class OpenState : public CourseState {
public:
	bool enroll(Course* course, Student* student) override {
		std::time_t t = std::time(nullptr);
		std::tm now{};
		localtime_s(&now, &t);

		Date today = { now.tm_mday, now.tm_mon + 1, now.tm_year + 1900 };

		Enrollment* newEnrollment = new Enrollment(student, course, today);

		course->addEnrollmentObj(newEnrollment);
		student->addEnrollment(newEnrollment);

		std::cout << "[Sukces]: "
			<< "Student "
			<< student->getName()
			<< " ("
			<< student->getIndex()
			<< ")"
			<< " zapisany na: "
			<< course->getName()
			<< std::endl;

		if (course->getStudentCount() >= course->getCapacity()) {
			course->setState(new FullState());
		}

		return true;

	}

	std::string getStateName() const override { return "ZAPISY_OTWARTE"; }
};