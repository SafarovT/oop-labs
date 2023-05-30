#include "WeekDay.h"

WeekDay GetNextWeekDay(WeekDay weekDay)
{
	char currentWeekDayPos = static_cast<char>(weekDay);
	char nextWeekDayPos = ++currentWeekDayPos;
	char firstWeekDayPos = static_cast<char>(WeekDay::SUNDAY);
	char lastWeekDayPos = static_cast<char>(WeekDay::SATURDAY);
	if (nextWeekDayPos > lastWeekDayPos)
	{
		nextWeekDayPos = firstWeekDayPos;
	}

	return static_cast<WeekDay>(nextWeekDayPos);
}