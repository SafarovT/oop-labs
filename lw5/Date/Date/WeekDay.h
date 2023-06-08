#pragma once

const unsigned DAYS_IN_WEEK = 7;

enum class WeekDay : char
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

WeekDay GetNextWeekDay(WeekDay weekDay);