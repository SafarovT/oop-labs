#include "CDate.h"
#include <iostream>

unsigned CDate::GetMaxTimeStamp()
{
	return CDate(31, Month::DECEMBER, MAX_YEAR) - CDate(1, Month::JANUARY, MIN_YEAR);
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	unsigned currentYear = MIN_YEAR;
	for (; currentYear < year && currentYear < MAX_YEAR; currentYear++)
	{
		m_timestamp += GetDaysInYear(currentYear);
	}

	Month currentMonth = Month::JANUARY;
	bool isYearLeap = IsYearLeap(currentYear);
	while (currentMonth < month && currentMonth != Month::DECEMBER)
	{
		m_timestamp += GetDaysInMonth(isYearLeap, currentMonth);
		currentMonth = GetNextMonth(currentMonth);
	}

	if (day > GetDaysInMonth(isYearLeap, currentMonth))
	{
		day = GetDaysInMonth(isYearLeap, currentMonth);
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
	unsigned dayAfterStartDate = m_timestamp + 1;
	unsigned year = MIN_YEAR;
	unsigned daysInYear = GetDaysInYear(year);
	while (dayAfterStartDate > daysInYear)
	{
		dayAfterStartDate -= daysInYear;
		year++;
		daysInYear = GetDaysInYear(year);
	}

	Month month = Month::JANUARY;
	bool isYearLeap = IsYearLeap(year);
	unsigned daysInMonth = GetDaysInMonth(isYearLeap, month);
	while (dayAfterStartDate > daysInMonth)
	{
		dayAfterStartDate -= daysInMonth;
		month = GetNextMonth(month);
		daysInMonth = GetDaysInMonth(isYearLeap, month);
	}

	return dayAfterStartDate;
}

Month CDate::GetMonth() const
{
	unsigned dayAfterStartDate = m_timestamp + 1;
	unsigned year = MIN_YEAR;
	unsigned daysInYear = GetDaysInYear(year);
	while (dayAfterStartDate > daysInYear)
	{
		dayAfterStartDate -= daysInYear;
		year++;
		daysInYear = GetDaysInYear(year);
	}

	Month month = Month::JANUARY;
	bool isYearLeap = IsYearLeap(year);
	unsigned daysInMonth = GetDaysInMonth(isYearLeap, month);
	while (dayAfterStartDate > daysInMonth)
	{
		dayAfterStartDate -= daysInMonth;
		month = GetNextMonth(month);
		daysInMonth = GetDaysInMonth(isYearLeap, month);
	}

	return month;
}

unsigned CDate::GetYear() const
{
	unsigned dayAfterStartDate = m_timestamp + 1;
	unsigned year = MIN_YEAR;
	unsigned daysInYear = GetDaysInYear(year);
	while (dayAfterStartDate > daysInYear)
	{
		dayAfterStartDate -= daysInYear;
		year++;
		daysInYear = GetDaysInYear(year);
	}

	return year;
}

bool CDate::IsValid() const
{
	return m_timestamp <= GetMaxTimeStamp();
}