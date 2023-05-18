#include "Calculator.h"

std::optional<Function::Operand> Calculator::GetOperandFromMemory(std::string const& operandName) 
{
	Variable* possibleVariable = m_memory.GetVariableByName(operandName);
	if (possibleVariable != nullptr)
	{
		Function::Operand operand(possibleVariable);
		return operand;
	}
	
	Function* possibleFunction = m_memory.GetFunctionByName(operandName);
	if (possibleFunction != nullptr)
	{
		return Function::Operand(possibleFunction);
	}

	return std::nullopt;
}

bool Calculator::InitVariable(std::string const& name)
{
	return m_memory.AddVariable(name, Variable());
}

bool Calculator::InitVariable(std::string const& name, double const value)
{
	if (m_memory.AddVariable(name, Variable(value)))
	{
		return true;
	}

	return m_memory.ChangeVariableValue(name, value);
}


bool Calculator::InitVariable(std::string const& variableToInitName, std::string const& operandToInitWithName)
{
	auto operandToInitWith = GetOperandFromMemory(operandToInitWithName);
	if (!operandToInitWith)
	{
		return false;
	}
	double valueToInitWith = operandToInitWith->GetValue();

	if (m_memory.AddVariable(variableToInitName, Variable(valueToInitWith)))
	{
		return true;
	}

	return m_memory.ChangeVariableValue(variableToInitName, valueToInitWith);
}

bool Calculator::InitFunction(
	std::string const& functionName,
	std::string const& leftOperandName,
	char const operationSign,
	std::string const& rightOperandName
)
{
	auto leftOperand = GetOperandFromMemory(leftOperandName);
	auto rightOperand = GetOperandFromMemory(rightOperandName);

	if (leftOperand == std::nullopt || rightOperand == std::nullopt)//TODO: лучше сравнивать с nulllprt
	{
		return false;
	}
	
	if (!m_memory.AddFunction(functionName, Function(*leftOperand, Operation(operationSign), *rightOperand)))
	{

		return false;
	}

	m_memory.AddDependence(leftOperandName, functionName);
	m_memory.AddDependence(rightOperandName, functionName);
	
	return true;
}


bool Calculator::InitFunction(std::string const& functionName, std::string const& operandToInitWithName)
{
	auto operandToInitWith = GetOperandFromMemory(operandToInitWithName);

	if (!operandToInitWith)
	{
		return false;
	}

	if (!m_memory.AddFunction(functionName, Function(*operandToInitWith)))
	{
		return false;
	}

	m_memory.AddDependence(operandToInitWithName, functionName);
	return true;
}

double Calculator::GetValue(std::string const& name)
{
	auto foundOperand = GetOperandFromMemory(name);
	if (foundOperand)
	{
		return foundOperand->GetValue();
	}

	return NAN;
}

std::map<std::string, Variable> Calculator::GetVariables() const
{
	return m_memory.GetVariables();
}

std::map<std::string, Function> Calculator::GetFunctions() const
{
	return m_memory.GetFunctions();
}