#include "CDate.h"

CDate::Date CDate::TimestampToDate(unsigned timestamp)
{
	unsigned day = timestamp + 1;
	unsigned year = MIN_YEAR;
	unsigned daysInYear = GetDaysInYear(year); // попробовать за константное время
	while (day > daysInYear)
	{
		day -= daysInYear;
		year++;
		daysInYear = GetDaysInYear(year);
	}

	Month month = Month::JANUARY;
	bool isYearLeap = IsYearLeap(year);
	unsigned daysInMonth = GetDaysInMonth(isYearLeap, month);
	while (day > daysInMonth)
	{
		day -= daysInMonth;
		month = GetNextMonth(month);
		daysInMonth = GetDaysInMonth(isYearLeap, month);
	}

	return { day, month, year };
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	unsigned currentYear = MIN_YEAR;
	for (; currentYear < year && currentYear < MAX_YEAR; currentYear++) // O(1)
	{
		m_timestamp += GetDaysInYear(currentYear);
	}

	Month currentMonth = Month::JANUARY;
	bool isYearLeap = IsYearLeap(currentYear);
	while (currentMonth < month && currentMonth < Month::DECEMBER)
	{
		m_timestamp += GetDaysInMonth(isYearLeap, currentMonth);
		currentMonth = GetNextMonth(currentMonth);
	}

	m_timestamp += day - 1;
}

WeekDay CDate::GetWeekDay() const
{
	WeekDay weekDay = START_WEEK_DAY;
	unsigned daysPassedInLastWeek = m_timestamp % DAYS_IN_WEEK;
	for (unsigned i = 1; i <= daysPassedInLastWeek; i++)
	{
		weekDay = GetNextWeekDay(weekDay);
	}

	return weekDay;
}

unsigned CDate::GetDay() const
{
	return TimestampToDate(m_timestamp).day;
}

Month CDate::GetMonth() const
{
	return TimestampToDate(m_timestamp).month;
}

unsigned CDate::GetYear() const
{
	return TimestampToDate(m_timestamp).year;
}

bool CDate::IsValid() const
{
	return m_timestamp <= MAX_TIMESTAMP;
}