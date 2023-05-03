#include "Memory.h"
#include <algorithm>

std::optional<Variable> Memory::GetVariableByName(std::string name) const
{
	auto isVariableFound = [name](Variable variable)
	{
		return variable.GetName() == name;
	};
	auto variableIter = std::find_if(m_variables.begin(), m_variables.end(), isVariableFound);
	if (variableIter == m_variables.end())
	{
		return std::nullopt;
	}

	return *variableIter;
}

std::optional<Function> Memory::GetFunctionByName(std::string name) const
{
	auto isFunctionFound = [name](Function function)
	{
		return function.GetName() == name;
	};
	auto functionIter = std::find_if(m_functions.begin(), m_functions.end(), isFunctionFound);
	if (functionIter == m_functions.end())
	{
		return std::nullopt;
	}

	return *functionIter;
}

std::vector<Variable> Memory::GetVariables() const
{
	return m_variables;
}

std::vector<Function> Memory::GetFunctions() const
{
	return m_functions;
}

bool Memory::AddFunction(Function function)
{
	if (IsOperandNameAlreadyUsed(function.GetName()))
	{
		return false;
	}
	m_functions.push_back(function);

	return true;
}

bool Memory::AddVariable(Variable variable)
{
	if (IsOperandNameAlreadyUsed(variable.GetName()))
	{
		return false;
	}
	m_variables.push_back(variable);

	return true;
}

bool Memory::IsOperandNameAlreadyUsed(std::string name) const
{
	auto isOperandFoundByName = [name](Operand operandToCheck)
	{
		return operandToCheck.GetName() == name;
	};
	auto variableIter = std::find_if(m_variables.begin(), m_variables.end(), isOperandFoundByName);
	auto functionIter = std::find_if(m_functions.begin(), m_functions.end(), isOperandFoundByName);

	return (variableIter != m_variables.end()) && (functionIter != m_functions.end());
}