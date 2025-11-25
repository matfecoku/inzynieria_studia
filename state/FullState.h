#pragma once
#include "CourseState.h"
#include <iostream>
#include <string>

class FullState : public CourseState {
public:
	bool enroll(Course* course, Student* student) override {
		std::cout << "[Brak miejsc]: Nie mozna zapisac studenta " 
			<< student->getName() 
			<< " (" 
			<< student->getIndex() 
			<< ")" 
			<< std::endl;
		return false;
	}

	std::string getStateName() const override { return "BRAK_MIEJSC"; }
};