#pragma once
#include <string>

class CPerson
{
public:
	CPerson() = default;

	CPerson(std::string fullName, double height, double weight)
		: m_fullName(std::move(fullName))
		, m_height(height)
		, m_weight(weight)
	{
	}

	bool operator == (CPerson const& person)
	{
		return (this->m_fullName == person.m_fullName)
			&& (this->m_height == person.m_height)
			&& (this->m_weight == person.m_weight);
	}

	std::string GetFullName() const;
	double GetHeight() const;
	double GetWeight() const;
private:
	std::string m_fullName = "";
	double m_height = 0;
	double m_weight = 0;
};