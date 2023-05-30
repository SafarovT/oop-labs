#pragma once
#include <iostream>
#include "Month.h"
#include "Year.h"
#include "WeekDay.h"

class CDate
{
public:
	CDate() = default;

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

	CDate& operator +=(int daysCount)
	{
		m_timestamp += daysCount;
		
		return *this;
	}

	CDate& operator -=(int daysCount)
	{
		m_timestamp -= daysCount;

		return *this;
	}

	bool operator ==(CDate const& date)
	{
		return this->m_timestamp == date.m_timestamp;
	}

	bool operator !=(CDate const& date)
	{
		return !(*this == date);
	}

	bool operator <(CDate const& date)
	{
		return this->m_timestamp < date.m_timestamp;
	}

	bool operator >(CDate const& date)
	{
		return this->m_timestamp > date.m_timestamp;
	}

	bool operator >=(CDate const& date)
	{
		return this->m_timestamp >= date.m_timestamp;
	}

	bool operator <=(CDate const& date)
	{
		return this->m_timestamp <= date.m_timestamp;
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
	unsigned m_timestamp = 0;
};

//std::ostream& operator<<(std::ostream& stream, CDate const& date)
//{
//	stream << date.GetDay() << '.' << static_cast<char>(date.GetMonth()) << '.' << date.GetYear();
//
//	return stream;
//}

//std::istream& operator>>(std::istream& stream, CDate& date)
//{
//	unsigned day = 1;
//	unsigned monthNumber = 1;
//	unsigned year = 1;
//	if (
//		(stream >> day) && (stream.get() == '.')
//		&& (stream >> monthNumber) && (stream.get() == '.')
//		&& (stream >> year)
//		)
//	{
//		date = CDate(day, static_cast<Month>(monthNumber), year);
//	}
//	else
//	{
//		stream.setstate(std::ios_base::failbit | stream.rdstate());
//	}
//
//	return stream;
//}