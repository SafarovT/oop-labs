#include "CStringStack.h"
#include <iostream>

namespace
{
	using namespace std;

	const string EMPTY_STACK_ERROR = "No elements in stack";
}

bool CStringStack::Empty() const
{
	return m_top == nullptr;
}

string CStringStack::GetTop() const
{
	if (Empty())
	{
		throw logic_error(EMPTY_STACK_ERROR);
	}

	return m_top->value;
}

void CStringStack::Push(string str)
{
	if (m_size == SIZE_MAX)
	{
		throw logic_error("Stack is full of elements");
	}

	m_top = new StackNode(move(str), m_top);
	m_size++;
}

void CStringStack::Pop()
{
	if (Empty())
	{
		throw logic_error(EMPTY_STACK_ERROR);
	}

	StackNode* top = m_top;
	m_top = m_top->next;
	m_size--;
	delete top;
}

void CStringStack::Clear()
{
	while (!Empty())
	{
		Pop();
	}
}

size_t CStringStack::GetSize() const
{
	return m_size;
}

CStringStack::~CStringStack()
{
	Clear();
}

CStringStack::CStringStack(CStringStack const& stack)
	: m_size(stack.GetSize())
{
	StackNode* stackNode = stack.m_top;
	m_top = new StackNode(move(stackNode->value), nullptr);
	while (stackNode->next != nullptr)
	{
		stackNode = stackNode->next;
		m_top = new StackNode(move(stackNode->value), m_top);
	}
}

CStringStack::CStringStack(CStringStack&& stack) noexcept
	: m_top(stack.m_top)
	, m_size(stack.m_size)
{
	stack.m_top = nullptr;
	stack.m_size = 0;
}

CStringStack& CStringStack::operator =(CStringStack const& stack)
{
	if (&stack != this)
	{
		*this = CStringStack(stack);
	}

	return *this;
}

CStringStack& CStringStack::operator =(CStringStack&& stack) noexcept
{
	if (&stack != this)
	{
		*this = CStringStack(stack);
	}

	return *this;
}