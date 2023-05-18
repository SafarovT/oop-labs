#include "Memory.h"
#include <regex>

Variable* Memory::GetVariableByName(std::string const& name)
{
	Variable* variablePointer = nullptr;
	auto foundVariable = m_variables.find(name);
	if (foundVariable != m_variables.end())
	{
		variablePointer = &foundVariable->second;
	}

	return variablePointer;
}

Function* Memory::GetFunctionByName(std::string const& name)
{
	Function* functionPointer = nullptr;
	auto foundFunction = m_functions.find(name);
	if (foundFunction != m_functions.end())
	{
		functionPointer = &foundFunction->second;
	}

	return functionPointer;
}

bool Memory::ChangeVariableValue(std::string const& name, double const value)
{
	auto foundVariable = m_variables.find(name);
	if (foundVariable == m_variables.end())
	{
		return false;
	}
	//auto& [var_name, var_value] = *foundVariable;
	foundVariable->second.SetValue(value);
	ResetDependences(name); // name

	return true;
}

std::map<std::string, Variable> Memory::GetVariables() const
{
	return m_variables;
}

std::map<std::string, Function> Memory::GetFunctions() const
{
	return m_functions;
}

bool Memory::AddFunction(std::string const& name, Function function)
{
	if (IsOperandNameAlreadyUsed(name) || !IsNameValid(name))
	{
		return false;
	}
	m_functions[name] = function;

	return true;
}

bool Memory::AddVariable(std::string const& name, Variable variable)
{
	if (IsOperandNameAlreadyUsed(name) || !IsNameValid(name))
	{
		return false;
	}
	m_variables[name] = variable;

	return true;
}

bool Memory::IsOperandNameAlreadyUsed(std::string const& name) const
{
	auto foundVariable = m_variables.find(name);
	auto foundFunction = m_functions.find(name);

	return (foundVariable != m_variables.end()) || (foundFunction != m_functions.end());
}

bool Memory::IsNameValid(std::string const& name) const
{
	std::regex reg(R"([a-zA-Z_][a-zA-Z0-9_]*)", std::regex_constants::icase);
	std::smatch matchedResult;

	return std::regex_match(name, matchedResult, reg);
}

void Memory::AddDependence(std::string const& operandName, std::string const& functionThatDependsOn)
{
	auto foundDepences = m_dependences.find(operandName);
	if (foundDepences != m_dependences.end())
	{
		foundDepences->second.push_back(functionThatDependsOn);
	}
	else
	{
		std::vector newDependences = { functionThatDependsOn };
		m_dependences[operandName] = newDependences;
	}
}

void Memory::ResetDependences(std::string const& operandName)
{
	
	if (auto foundDependences = m_dependences.find(operandName); foundDependences != m_dependences.end())
	{
		// не лучше ли перебирать по ссылке
		for (auto& functionThatDependsOnName : foundDependences->second)
		{
			
			if (auto foundFunction = m_functions.find(functionThatDependsOnName); foundFunction != m_functions.end())
			{
				foundFunction->second.ResetValue();
				ResetDependences(functionThatDependsOnName);
			}
		}
	}
}