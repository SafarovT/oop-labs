#pragma once
#include <vector> // map?? but NOT unordered
#include <optional>
#include "Variable.h"
#include "Function.h"

class Memory
{
public:
	std::optional<Variable> GetVariableByName(std::string name) const;
	std::optional<Function> GetFunctionByName(std::string name) const;
	std::vector<Variable> GetVariables() const;
	std::vector<Function> GetFunctions() const;
	bool AddFunction(Function function);
	bool AddVariable(Variable variable);
private:
	std::vector<Variable> m_variables;
	std::vector<Function> m_functions;

	bool IsOperandNameAlreadyUsed(std::string name) const;
};

