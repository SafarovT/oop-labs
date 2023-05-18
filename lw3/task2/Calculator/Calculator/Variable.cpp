#include "Variable.h"

void Variable::SetValue(double const value)
{
	m_value = value;
}

double Variable::GetValue() const
{
	return m_value;
}