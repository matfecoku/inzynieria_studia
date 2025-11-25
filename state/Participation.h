#pragma once
#include "ResearchAssociate.h"
#include "Project.h"
#include "Date.h"

class Participation {
private:
	ResearchAssociate* m_researchAssociate;
	Project* m_project;

public:
	int hours;
	Participation(ResearchAssociate* researchAssociate, Project* project, int hours)
		: m_researchAssociate(researchAssociate), m_project(project), hours(hours) {
	}
};