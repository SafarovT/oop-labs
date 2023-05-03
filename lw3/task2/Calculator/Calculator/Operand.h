#pragma once
#include <string>

class Operand
{
public:
	Operand(std::string name)
		:m_name(name)
	{
	}

	virtual double GetValue() const = 0;
	std::string GetName() const;
protected:
	std::string m_name;
	double m_value = NAN;
};