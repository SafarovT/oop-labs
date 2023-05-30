#pragma once
#include "Month.h"
#include "Year.h"
#include "WeekDay.h"

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);

	CDate(unsigned timestamp)
		: m_timestamp(timestamp)
	{};

	CDate& operator ++()
	{
		++m_timestamp;
		return *this;
	}

	CDate operator ++(int)
	{
		CDate tmpCopy(*this);
		++*this;
		return tmpCopy;
	}

	CDate& operator --()
	{
		--m_timestamp;
		return *this;
	}

	CDate& operator --(int)
	{	
		CDate tmpCopy(*this);
		--*this;
		return tmpCopy;
	}

	CDate operator +(int daysCount) const
	{
		return CDate(this->m_timestamp + daysCount);
	}

	CDate operator -(int daysCount) const
	{
		return CDate(this->m_timestamp - daysCount);
	}

	int operator -(CDate date) const
	{
		return this->m_timestamp - date.m_timestamp;
	}

	unsigned GetDay() const;

	Month GetMonth() const;

	unsigned GetYear() const;

	WeekDay GetWeekDay() const;

	bool IsValid() const;
private:
	static const unsigned MIN_YEAR = 1970;
	static const unsigned MAX_YEAR = 9999;
	static const WeekDay START_WEEK_DAY = WeekDay::THURSDAY;

	static unsigned GetMaxTimeStamp();
	bool m_isValid = true;
	unsigned m_timestamp = 0;
};