#pragma once

enum class Month : char // in class with methods get all / get days
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay : char
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned yaer)
		: m_year(yaer)
		, m_month(month)
		, m_day(day)
	{};

	CDate(unsigned timestamp = 0);

	// возвращает день месяца (от 1 до 31)
	unsigned GetDay() const;

	// возвращает месяц
	Month GetMonth() const;

	// возвращает год
	unsigned GetYear() const;

	// возвращает день недели
	WeekDay GetWeekDay() const;

	// возвращает информацию о корректности хранимой даты.
	// Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	//	CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const;
private:
	static const unsigned DAYS_IN_YEAR = 365;
	static const unsigned DAYS_IN_LEAP_YEAR = 366;
	static const unsigned MIN_YEAR = 1970;
	static const unsigned MAX_YAER = 9999;

	unsigned m_year;
	Month m_month;
	unsigned m_day;

	static bool IsYearLeap(unsigned year);
	static unsigned GetDaysInYear(unsigned year);
	static unsigned GetDaysInMonth(bool isYearLeap, Month month);
};