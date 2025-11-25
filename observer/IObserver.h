#pragma once
#include <string>

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void Update(const std::string& msg_from_subject) = 0;
};