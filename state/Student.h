#pragma once
#include <string>
#include <vector>
#include "Enrollment.h"

class Student {
private:
	int m_indexNum;
	std::string m_name;
	std::vector<Enrollment*> m_vec_enrollments;

public:
	Student(int index, std::string name)
		: m_indexNum(index), m_name(name) {}

	std::string getName() const { return m_name; };

	int getIndex() const { return m_indexNum; };

	void addEnrollment(Enrollment* e) {
		m_vec_enrollments.push_back(e);
	}
};