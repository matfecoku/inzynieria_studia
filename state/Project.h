#pragma once
#include "Date.h"
#include <string>

class Project {
public:
	std::string name;
	Date start;
	Date end;

	Project(const std::string& name, Date start, Date end)
		: name(name), start(start), end(end) {}
};