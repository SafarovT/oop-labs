#pragma once
#include "IPerson.h"

class IRacer : public IPerson
{
public:
	virtual ~IRacer() {};

	virtual unsigned int GetAwardsCount() const = 0;
};