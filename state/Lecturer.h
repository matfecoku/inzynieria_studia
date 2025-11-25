#pragma once
#include "ResearchAssociate.h"
#include <vector>

class Course;

class Lecturer : public ResearchAssociate {
private:
	std::vector<Course*> m_vec_courses;
public:
	Lecturer(int ssNo, const std::string& name, const std::string& email, const std::string& fieldOfStudy)
		: ResearchAssociate(ssNo, name, email, fieldOfStudy) {
	}
};