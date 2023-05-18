#pragma once
#include "Operation.h"
#include "Variable.h"
#include <optional>

class Function
{
public:
	// std::variant 
	class Operand
	{
	public:
		Operand() = default;

		Operand(Variable* variable)
		{
			m_variable = variable;
		}

		Operand(Function* function)
		{
			m_function = function;
		}
		double GetValue();
	private:
		Variable* m_variable = nullptr;
		Function* m_function = nullptr;
	};

	Function() = default;

	Function(
		Operand leftOperand,
		Operation operation,
		Operand rightOperand
	)
	{
		m_leftOperand = leftOperand;
		m_operation = operation;
		m_rightOperand = rightOperand;
		m_withOperation = true;
	}
	
	Function(Operand singleOperand)
	{
		m_leftOperand = singleOperand;
		m_withOperation = false;
	}

	double GetValue();
	void ResetValue();

private:
	std::optional<double> m_value = std::nullopt;
	Operand m_leftOperand = Operand();
	Operation m_operation = Operation();
	Operand m_rightOperand = Operand();
	bool m_withOperation;
};