#pragma once
#include "CourseState.h"
#include <iostream>
#include <string>

class ClosedState : public CourseState {
public:
	bool enroll(Course* course, Student* student) override {
		std::cout << "[System Zamkniety]: "
			<< "Sprobuj ponownie pozniej"
			<< std::endl;
		return false;
	}

	std::string getStateName() const override { return "SYSTEM_ZAMKNIETY"; }
};