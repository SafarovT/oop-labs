#include "CStringStack.h"
#include <iostream>

namespace
{
	using namespace std;
}

bool CStringStack::Empty() const
{
	return m_top == nullptr;
}

string CStringStack::Top() const
{
	if (Empty())
	{
		throw new logic_error("No elements in stack");
	}

	return m_top->value;
}

void CStringStack::Push(string str)
{
	m_top = new StackNode( move(str), m_top );
}

void CStringStack::Pop()
{
	if (Empty())
	{
		throw new logic_error("No elements in stack");
	}

	StackNode* top = m_top;
	m_top = m_top->next;
	delete top;
}

CStringStack::~CStringStack()
{
	while (!Empty())
	{
		Pop();
	}
}

CStringStack::CStringStack(CStringStack const& stack)
{

}

CStringStack::CStringStack(CStringStack&& stack) noexcept
{

}