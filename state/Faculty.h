#pragma once
#include <string>

class Employee;

class Faculty {
public:
	Employee* dean = nullptr;
	std::string name;

	Faculty(const std::string& name)
		: name(name) {}
};