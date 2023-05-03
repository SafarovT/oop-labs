#include "Calculator.h"
#include <algorithm>

std::vector<Variable> Calculator::GetVariables() const
{
	std::vector<Variable> variables = m_memory.GetVariables();
	std::sort(variables.begin(), variables.end());

	return variables;
}

std::vector<Function> Calculator::GetFunctions() const
{
	std::vector<Function> functions = m_memory.GetFunctions();
	std::sort(functions.begin(), functions.end());

	return functions;
}

double Calculator::GetValue(std::string name) const
{
	auto variable = m_memory.GetVariableByName(name);
	if (variable)
	{
		return variable->GetValue();
	}
	else
	{
		auto function = m_memory.GetFunctionByName(name);
		if (function)
		{
			return function->GetValue();
		}
	}

	return NAN;
}

bool Calculator::InitVariable(std::string name)
{
	return m_memory.AddVariable(Variable(name));
}

bool Calculator::InitVariableWithValue(std::string name, double value)
{
	Variable variable(name);
	variable.SetValue(value);
	return m_memory.AddVariable(variable);
}

bool Calculator::InitFunctionWithValue()
{

}