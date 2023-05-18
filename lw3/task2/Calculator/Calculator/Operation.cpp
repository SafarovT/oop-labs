#include "Operation.h"

double Operation::Execute(double leftOperand, double rightOperand) const
{
	switch (m_operationSign)
	{
	case '+':
		return leftOperand + rightOperand;
	case '-':
		return leftOperand - rightOperand;
	case '/':
		return leftOperand / rightOperand;
	case '*':
		return leftOperand * rightOperand;
	default:
		return NAN;
	}
}