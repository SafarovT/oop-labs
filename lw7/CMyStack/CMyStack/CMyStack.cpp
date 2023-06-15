#include "CMyStack.h"

namespace
{
	using namespace std;

	const char* EMPTY_STACK_ERROR = "No elements in stack";
}

template <typename T>
bool CMyStack<T>::Empty() const
{
	return m_top == nullptr;
}

template <typename T>
T CMyStack<T>::GetTop() const
{
	if (Empty())
	{
		throw logic_error(EMPTY_STACK_ERROR);
	}

	return m_top->value;
}

template <typename T>
void CMyStack<T>::Push(T item)
{
	if (m_size == SIZE_MAX)
	{
		throw logic_error("Stack is full of elements");
	}

	m_top = new StackNode(move(item), m_top);
	m_size++;
}

template <typename T>
void CMyStack<T>::Pop()
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

template <typename T>
void CMyStack<T>::Clear()
{
	while (!Empty())
	{
		Pop();
	}
}

template <typename T>
size_t CMyStack<T>::GetSize() const
{
	return m_size;
}

template <typename T>
CMyStack<T>::~CMyStack()
{
	Clear();
}

template <typename T>
CMyStack<T>::CMyStack(CMyStack<T> const& stack)
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

template <typename T>
CMyStack<T>::CMyStack(CMyStack<T>&& stack) noexcept
	: m_top(stack.m_top)
	, m_size(stack.m_size)
{
	stack.m_top = nullptr;
	stack.m_size = 0;
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator =(CMyStack<T> const& stack)
{
	if (&stack != this)
	{
		*this = CMyStack(stack);
	}

	return *this;
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator =(CMyStack<T>&& stack) noexcept
{
	if (&stack != this)
	{
		*this = CMyStack(stack);
	}

	return *this;
}