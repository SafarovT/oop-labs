#pragma once
#include "Operand.h"
#include "Variable.h"
#include <optional>

class Function : public Operand
{
public:
	// OperandPosition
	// SetOperand(Function, OperandPosition)
	// SetOperand(Variable, OperandPosition)
	Function(std::string name)
		:Operand(name)
	{
	}

	void SetValue(double value);
	double GetValue() const override;
private:
	struct OneOperand
	{
		std::optional<Function> functionOperand;
		std::optional<Variable> variableOperand;
	};

	OneOperand m_leftOperand;
	// Operator
	OneOperand m_rightOperand;
};