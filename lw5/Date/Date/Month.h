#pragma once

enum class Month : char
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

unsigned GetDaysInMonth(bool isYearLeap, Month month);
Month GetNextMonth(Month month);