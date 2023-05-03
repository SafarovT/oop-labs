#pragma once
#include "Operand.h"

class Variable : public Operand
{
public:
	Variable(std::string name)
		:Operand(name)
	{
	}

	void SetValue(double value);
	double GetValue() const override;
};

