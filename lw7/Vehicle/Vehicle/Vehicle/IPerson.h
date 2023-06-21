#pragma once
#include <string>

class IPerson
{
public:
	virtual ~IPerson() {};


	virtual std::string GetName() const = 0;
};