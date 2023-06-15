#pragma once
#include <stdexcept>

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