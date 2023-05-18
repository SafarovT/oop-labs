#pragma once
#include <string>

class Variable
{
public:
	Variable() = default;

	Variable(double const value)
	{
		m_value = value;
	}

	void SetValue(double const value);
	double GetValue() const;
private:
	double m_value = NAN;
};