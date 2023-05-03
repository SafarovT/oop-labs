#pragma once
#include "Memory.h";
#include <iostream>

class Calculator
{
public:
	bool InitVariable(std::string name);
	bool InitVariableWithValue(std::string name, double value);
	bool InitFunctionWithValue();
	double GetValue(std::string name) const;
	std::vector<Variable> GetVariables() const;
	std::vector<Function> GetFunctions() const;
private:
	Memory m_memory;
};