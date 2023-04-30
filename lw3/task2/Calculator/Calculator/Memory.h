#pragma once
#include <vector>
#include "Variable.h"
#include "Function.h"

class Memory
{
public:
	bool IsAlreadyExists(std::string entiryName) const;
	void AddFunction(Function function);
	void AddVariable(Variable Variable);
private:
	std::vector<Variable> m_variables;
	std::vector<Function> m_functions;
};

