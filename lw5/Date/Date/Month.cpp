#include "Month.h"

unsigned GetDaysInMonth(bool isYearLeap, Month month)
{
	switch (month)
	{
	case Month::JANUARY:
		return 31;
	case Month::FEBRUARY:
		return isYearLeap ? 29 : 28;
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

Month GetNextMonth(Month month)
{
	char currentMonthPos = static_cast<char>(month);
	char nextMonthPos = ++currentMonthPos;
	char firstMonthPos = static_cast<char>(Month::JANUARY);
	char lastMonthPos = static_cast<char>(Month::DECEMBER);
	if (nextMonthPos > lastMonthPos)
	{
		nextMonthPos = firstMonthPos;
	}
	
	return static_cast<Month>(nextMonthPos);
}