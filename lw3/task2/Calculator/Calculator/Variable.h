#pragma once
#include <string>

class Variable
{
public:
	Variable(std::string name)
	{
		m_name = name;
	}

	void SetValue(double value);
	double GetValue() const;
private:
	std::string m_name;
	double m_value = NAN;
};

