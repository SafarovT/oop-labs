#include "Function.h"

double Function::GetValue()
{
	// mutable
	// opt для отс. значений
	if (m_value == std::nullopt)
	{
		if (m_withOperation)
		{
			m_value.emplace(m_operation.Execute(m_leftOperand.GetValue(), m_rightOperand.GetValue()));
		}
		else
		{
			m_value.emplace(m_leftOperand.GetValue());
		}
	}

	return *m_value;
}

void Function::ResetValue()
{
	m_value.reset();
}

double Function::Operand::GetValue()
{
	if (m_variable != nullptr)
	{
		return m_variable->GetValue();
	}

	if (m_function != nullptr)
	{
		return m_function->GetValue();
	}

	return NAN;
}