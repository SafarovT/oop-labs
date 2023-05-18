#pragma once
#include "Memory.h"

class Calculator
{
public:
	bool InitVariable(std::string const& name);
	bool InitVariable(std::string const& name, double const value);
	bool InitVariable(std::string const& variableToInitName, std::string const& operandToInitWithName);
	bool InitFunction(
		std::string const& functionName,
		std::string const& leftOperandName,
		char const operationSign,
		std::string const& rightOperandName
	);
	bool InitFunction(
		std::string const& functionName,
		std::string const& operandToInitWithName
	);
	double GetValue(std::string const& name);
	// подумать как ускроить методы
	std::map<std::string, Variable> GetVariables() const;
	std::map<std::string, Function> GetFunctions() const;
private:
	std::optional<Function::Operand> GetOperandFromMemory(std::string const& operandName);
	Memory m_memory;
};

// округялть при выводе до двух знаков
