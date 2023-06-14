#pragma once
#include <string>
#include <stdexcept>

struct StackNode
{
	StackNode(std::string initValue, StackNode* nextNode)
		: value(std::move(initValue))
		, next(nextNode)
	{}

	std::string value;
	StackNode* next;
};

class CStringStack
{
public:
	bool Empty() const;
	std::string GetTop() const;
	void Push(std::string str);
	void Pop();
	void Clear();
	size_t GetSize() const;

	CStringStack() = default;
	~CStringStack();
	CStringStack(CStringStack const& stack);
	CStringStack(CStringStack&& stack) noexcept;
	CStringStack& operator =(CStringStack const& stack);
	CStringStack& operator =(CStringStack&& stack) noexcept;
private:
	StackNode* m_top = nullptr;
	size_t m_size = 0;
};