#pragma once
#include "Employee.h"
#include <string>

class ResearchAssociate : public Employee {
public:

	std::string fieldOfStudy;

	ResearchAssociate(int ssNo, const std::string& name, const std::string& email, const std::string& fieldOfStudy)
		: Employee(ssNo, name, email), fieldOfStudy(fieldOfStudy) {
	}
};