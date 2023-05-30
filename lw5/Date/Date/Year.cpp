#include "Year.h"

bool IsYearLeap(unsigned year)
{
	auto isYearMultipleOf = [year](unsigned divider) { return year % divider == 0; };

	return isYearMultipleOf(4) && (!isYearMultipleOf(100) || isYearMultipleOf(400));
}

unsigned GetDaysInYear(unsigned year)
{
	return IsYearLeap(year) ? DAYS_IN_LEAP_YEAR : DAYS_IN_YEAR;
}
