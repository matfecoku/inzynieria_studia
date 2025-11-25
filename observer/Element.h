#pragma once
#include <string>

class Element {
private:
	int m_ID;
	int m_val1;
	std::string m_val2;

public:
	Element(int idEl, int v1, std::string v2)
		: m_ID(idEl), m_val1(v1), m_val2(v2) {
	}

	int getID() const {
		return m_ID;
	}
};