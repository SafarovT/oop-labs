#pragma once
#include "IRacer.h"
#include "CPersonImpl.h"

class CRacer : public CPersonImpl<IRacer>
{
public:
	CRacer(std::string name, unsigned int awardsCount)
		: CPersonImpl(name)
		, m_awardsCount(awardsCount)
	{}

	unsigned int GetAwardsCount() const;
private:
	unsigned int m_awardsCount;
};