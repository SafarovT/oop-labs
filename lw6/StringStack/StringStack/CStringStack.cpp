#include "CStringStack.h"
#include <algorithm>

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
	: m_size(0)
{
	StackNode* node = stack.m_top;
	if (node == nullptr)
	{
		m_top = nullptr;
		return;
	}
	m_top = new StackNode(node->value, nullptr);
	m_size++;
	StackNode* prev = m_top;
	while (node->next != nullptr)
	{
		node = node->next;
		try
		{
			// утечка памяти в случае исключения
			prev->next = new StackNode(node->value, nullptr);
			m_size++;
		}
		catch (std::exception& e)
		{
			Clear();
			throw;
		}
		prev = prev->next;
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
		CStringStack stackToCopy(stack);
		swap(m_top, stackToCopy.m_top);
		swap(m_size, stackToCopy.m_size);
	}

	return *this;
}

CStringStack& CStringStack::operator =(CStringStack&& stack) noexcept
{
	if (&stack != this)
	{
		// удалять остальные узлы
		Clear();
		m_top = stack.m_top;
		m_size = stack.m_size;
		stack.m_top = nullptr;
		stack.m_size = 0;
	}

	return *this;
}