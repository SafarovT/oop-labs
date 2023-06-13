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
	std::string Top() const;
	void Push(std::string str);
	void Pop();

	CStringStack() = default;
	~CStringStack();
	CStringStack(CStringStack const& stack);
	CStringStack(CStringStack&& stack) noexcept;
private:
	StackNode* m_top = nullptr;
};