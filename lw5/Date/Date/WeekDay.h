#pragma once

const unsigned DAYS_IN_WEEK = 7;
// все же переделать в класс с переопределенными операциями

enum class WeekDay : char
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

WeekDay GetNextWeekDay(WeekDay weekDay);