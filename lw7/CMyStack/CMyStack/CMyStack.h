#pragma once
#include <algorithm>
#include <stdexcept>

namespace
{
	const char* EMPTY_STACK_ERROR = "No elements in stack";
}

template <typename T>
class CMyStack
{
public:
	bool Empty() const;
	T GetTop() const;
	void Push(T str);
	void Pop();
	void Clear();
	size_t GetSize() const;

	CMyStack() = default;
	~CMyStack();
	CMyStack(CMyStack const& stack);
	CMyStack(CMyStack&& stack) noexcept;
	CMyStack& operator =(CMyStack const& stack);
	CMyStack& operator =(CMyStack&& stack) noexcept;
private:
	struct StackNode
	{
		StackNode(T initValue, StackNode* nextNode)
			: value(std::move(initValue))
			, next(nextNode)
		{}

		T value;
		StackNode* next;
	};

	StackNode* m_top = nullptr;
	size_t m_size = 0;
};

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
		throw std::logic_error(EMPTY_STACK_ERROR);
	}

	return m_top->value;
}

template <typename T>
void CMyStack<T>::Push(T item)
{
	if (m_size == SIZE_MAX)
	{
		throw std::logic_error("Stack is full of elements");
	}

	m_top = new StackNode(std::move(item), m_top);
	m_size++;
}

template <typename T>
void CMyStack<T>::Pop()
{
	if (Empty())
	{
		throw std::logic_error(EMPTY_STACK_ERROR);
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
			prev->next = new StackNode(node->value, nullptr);
		}
		catch (std::exception& exception)
		{
			Clear();
			throw; // просто throw чтобы перевыбросить
		}
		m_size++;
		prev = prev->next;
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
		CMyStack stackToCopy(stack);
		std::swap(m_top, stackToCopy.m_top);
		std::swap(m_size, stackToCopy.m_size);
	}

	return *this;
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator =(CMyStack<T>&& stack) noexcept
{
	if (&stack != this)
	{
		Clear();
		m_top = stack.m_top;
		m_size = stack.m_size;
		stack.m_top = nullptr;
		stack.m_size = 0;
	}

	return *this;
}