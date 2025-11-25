#pragma once
#include "Employee.h"

class AdministrativeEmployee : public Employee {
public:
	AdministrativeEmployee(int ssNo, const std::string& name, const std::string& email)
		: Employee(ssNo, name, email) {}
};