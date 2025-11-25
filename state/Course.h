#pragma once
#include <string>
#include "CourseState.h"
#include <vector>
#include "ClosedState.h"

class Enrollment;

class Course {
private:
	int m_capacity;

	CourseState* m_state;

	std::vector<Enrollment*> m_vec_enrollments;

public:

	std::string name;
	int id;
	float hours;

	Course(std::string name, int id, float hours, int capacity)
		: name(name), id(id), hours(hours), m_capacity(capacity) {
		m_state = new ClosedState();
	}

	~Course() {
		if (m_state != nullptr)
			delete m_state;

		for (auto& e : m_vec_enrollments)
			delete e;
	}

	void setState(CourseState* newState) {
		if (m_state != nullptr) 
			delete m_state;

		m_state = newState;
		std::cout << "Zmiana stanu kursu: " 
			<< name 
			<< " -> " 
			<< m_state->getStateName() 
			<< std::endl;
	}

	bool registerStudent(Student* s) {
		return m_state->enroll(this, s);
	}

	int getStudentCount() const { return m_vec_enrollments.size(); }
	int getCapacity() const { return m_capacity; }

	void addEnrollmentObj(Enrollment* e) {
		m_vec_enrollments.push_back(e);
	}

	std::string getName() const { return name; }
	std::string getStateName() const {
		return m_state->getStateName();
	}
};