#include "CDate.h"

bool CDate::IsYearLeap(unsigned year)
{
	auto isYearMultipleOf = [year](unsigned divider) { return year / divider; };

	return isYearMultipleOf(4) && (!isYearMultipleOf(100) || isYearMultipleOf(400));
}

unsigned CDate::GetDaysInYear(unsigned year)
{
	return IsYearLeap(year)? DAYS_IN_LEAP_YEAR: DAYS_IN_YEAR;
}

unsigned CDate::GetDaysInMonth(bool isYearLeap, Month month)
{
	switch (month)
	{
	case Month::JANUARY:
		return 31;
	case Month::FEBRUARY:
		return isYearLeap? 29: 28;
	case Month::MARCH:
		return 31;
	case Month::APRIL:
		return 30;
	case Month::MAY:
		return 31;
	case Month::JUNE:
		return 30;
	case Month::JULY:
		return 31;
	case Month::AUGUST:
		return 31;
	case Month::SEPTEMBER:
		return 30;
	case Month::OCTOBER:
		return 31;
	case Month::NOVEMBER:
		return 30;
	case Month::DECEMBER:
		return 31;
	default:
		return 0;
	}
}

CDate::CDate(unsigned timestamp = 0)
{
	m_year = MIN_YEAR;
	unsigned daysInYear = GetDaysInYear(m_year);
	while (timestamp - daysInYear >= 0)
	{
		timestamp -= daysInYear;
		m_year++;
		daysInYear = GetDaysInYear(m_year);
	}

	m_month = Month::JANUARY;
	bool isYearLeap = IsYearLeap(m_year);
	unsigned daysInMonth = GetDaysInMonth(isYearLeap, m_month);
	while (timestamp - daysInMonth >= 0 && m_month < Month::DECEMBER)
	{
		timestamp -= daysInMonth;
		m_month = static_cast<Month>(static_cast<char>(m_month) + 1);
		daysInMonth = GetDaysInMonth(isYearLeap, m_month);
	}

	m_day = timestamp;
}