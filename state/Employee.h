#pragma once
#include <string>

class Faculty;

class Employee {
public:

	Faculty* leads = nullptr;

	static int s_counter;
	int ssNo;
	std::string name;
	std::string email;

	virtual ~Employee() = default;

	int getSsNo() const {
		return ssNo;
	}

	const std::string& getName() const {
		return name;
	}

	const std::string& getEmail() const {
		return email;
	}

	static int getCounter() {
		return s_counter;
	}

protected:
	Employee(int ssNo, const std::string& name, const std::string& email)
		: ssNo(ssNo), name(name), email(email) {
	}
};