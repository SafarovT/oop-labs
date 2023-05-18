#pragma once
#include "Variable.h"
#include "Function.h"
#include <map>
#include <optional>
#include <vector>

class Memory
{
public:
	Variable* GetVariableByName(std::string const& name);
	Function* GetFunctionByName(std::string const& name);
	[[nodiscard]] bool ChangeVariableValue(std::string const& name, double const value);
	std::map<std::string, Variable> GetVariables() const; //ускорить
	std::map<std::string, Function> GetFunctions() const;
	bool AddFunction(std::string const& name, Function function);
	bool AddVariable(std::string const& name, Variable variable);
	void AddDependence(std::string const& operandName, std::string const& operandThatDependsOn);
private:
	using OperandDependences = std::map<std::string, std::vector<std::string>>;
	std::map<std::string, Variable> m_variables;
	std::map<std::string, Function> m_functions;
	OperandDependences m_dependences;

	bool IsOperandNameAlreadyUsed(std::string const& name) const;
	bool IsNameValid(std::string const& name) const;
	void ResetDependences(std::string const& operandName);
};