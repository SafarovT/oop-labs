#pragma once
#include <string>

template <class Base>
class CPersonImpl : public Base
{
public:
	virtual ~CPersonImpl() {};
	CPersonImpl(std::string name)
		: m_name(name)
	{};

	std::string GetName() const
	{
		return m_name;
	}
private:
	std::string m_name;
};

