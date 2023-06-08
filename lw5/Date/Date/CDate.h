#pragma once
#include <iostream>
#include "Month.h"
#include "Year.h"
#include "WeekDay.h"
#include <compare>

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
		if (IsValid())
		{
			++m_timestamp;
		}
		return *this;
	}

	CDate operator ++(int)
	{
		CDate tmpCopy(*this);
		if (IsValid())
		{
			++*this;
		}
		return tmpCopy;
	}

	CDate& operator --()
	{
		if (IsValid())
		{
			--m_timestamp;
		}
		return *this;
	}

	CDate& operator --(int)
	{	
		CDate tmpCopy(*this);
		if (IsValid())
		{
			--*this;
		}
		return tmpCopy;
	}

	CDate operator +(int daysCount) const // кол-во дней + дата
	{
		if (!IsValid())
		{
			return *this;
		}

		return CDate(this->m_timestamp + daysCount);
	}

	CDate friend operator +(int daysCount, CDate date);

	CDate operator -(int daysCount) const
	{
		if (!IsValid())
		{
			return *this;
		}

		return CDate(this->m_timestamp - daysCount);
	}

	int operator -(CDate date) const
	{
		if (!IsValid() || !date.IsValid())
		{
			throw std::invalid_argument("Invalid date");
		}

		return this->m_timestamp - date.m_timestamp;
	}

	CDate& operator +=(int daysCount)
	{
		if (IsValid())
		{
			m_timestamp += daysCount;
		}

		return *this;
	}

	CDate& operator -=(int daysCount)
	{
		if (IsValid())
		{
			m_timestamp -= daysCount;
		}

		return *this;
	}

	auto operator <=>(CDate const& date) const = default;


	unsigned GetDay() const;

	Month GetMonth() const;

	unsigned GetYear() const;

	WeekDay GetWeekDay() const;

	bool IsValid() const;
private:
	struct Date
	{
		unsigned day;
		Month month;
		unsigned year;
	};
	static const unsigned MIN_YEAR = 1970;
	static const unsigned MAX_YEAR = 9999;
	static const unsigned MAX_TIMESTAMP = 2932896;
	static const unsigned TIMESTAMP_400_YEARS = 146097;
	static const WeekDay START_WEEK_DAY = WeekDay::THURSDAY;

	static Date TimestampToDate(unsigned timestamp);
	unsigned m_timestamp = 0;
};

inline CDate operator +(int daysCount, CDate date)
{
	if (!date.IsValid())
	{
		return date;
	}

	return CDate(date.m_timestamp + daysCount);
}

inline std::ostream& operator<<(std::ostream& stream, CDate const& date)
{
	stream << date.GetDay() << '.' << static_cast<int>(date.GetMonth()) << '.' << date.GetYear();

	return stream;
}

inline std::istream& operator>>(std::istream& stream, CDate& date)
{
	unsigned day = 1;
	unsigned monthNumber = 1;
	unsigned year = 1;
	if (
		(stream >> day) && (stream.get() == '.')
		&& (stream >> monthNumber) && (stream.get() == '.')
		&& (stream >> year)
		)
	{
		date = CDate(day, static_cast<Month>(monthNumber), year);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}