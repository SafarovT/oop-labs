#pragma once
#include <string>

class Operation
{
public:
	Operation() = default;

	Operation(char operationSign)
	{
		m_operationSign = operationSign;
	}

	double Execute(double leftOperand, double rightOperand) const;
private:
	char m_operationSign;
};

