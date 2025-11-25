#pragma once
#include <string>
#include <vector>
#include "ResearchAssociate.h"

class Institute {
	std::vector<ResearchAssociate*> m_vec_researchassociates;
public:
	std::string name;
	std::string address;

	Institute(const std::string& name, const std::string& address)
		: name(name), address(address) {}
};