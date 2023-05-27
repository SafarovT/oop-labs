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

unsigned GetDaysInMonth(unsigned year, Month month)
{
	switch (month)
	{
	case Month::JANUARY:
		break;
	case Month::FEBRUARY:
		break;
	case Month::MARCH:
		break;
	case Month::APRIL:
		break;
	case Month::MAY:
		break;
	case Month::JUNE:
		break;
	case Month::JULY:
		break;
	case Month::AUGUST:
		break;
	case Month::SEPTEMBER:
		break;
	case Month::OCTOBER:
		break;
	case Month::NOVEMBER:
		break;
	case Month::DECEMBER:
		break;
	default:
		return -1;
	}
}

CDate::CDate(unsigned timestamp = 0)
{
	m_year = MIN_YEAR;
	do
	{
		timestamp -= GetDaysInYear(m_year);
		m_year + 1;
	} while (timestamp >= 0);
	timestamp += GetDaysInYear(m_year - 1);


}