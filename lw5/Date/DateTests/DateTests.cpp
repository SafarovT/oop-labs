#include "../../../external/catch2/catch.hpp"
#include "../Date/CDate.h"
#include <sstream>

SCENARIO("Создание различных дат и проверка их валидности")
{
	WHEN("Создаем дату, иницилизируя каждое из полей")
	{
		CDate date(10, Month::JULY, 2004);

		THEN("Все поля проинициализированны верно")
		{
			CHECK(date.GetDay() == 10);
			CHECK(date.GetMonth() == Month::JULY);
			CHECK(date.GetYear() == 2004);
			CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
		}
	}

	WHEN("Создаем 29 фераля в невесокосный год")
	{
		CDate date(29, Month::FEBRUARY, 2001);

		THEN("Проставится 28 фераля")
		{
			CHECK(date.GetDay() == 28);
		}
	}

	WHEN("Создаем дату через timestamp < 1 month")
	{
		CDate date(30);

		THEN("Все поля проинициализированны верно")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
		}
	}

	WHEN("Создаем дату через timestamp < 1 year")
	{
		CDate date(355);

		THEN("Все поля проинициализированны верно")
		{
			CHECK(date.GetDay() == 22);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("Создаем дату с timestamp = 1 year")
	{
		CDate date(365);

		THEN("Мы получим 1 января следующего года")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1971);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("Создаем дату в високосном году 29 феврадя через timestamp")
	{
		CDate date(789);

		THEN("Все поля проинициализированны верно")
		{
			CHECK(date.GetDay() == 29);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 1972);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("Создаем дату с timestamp на 29 февраля 2000 год")
	{
		CDate date(11016);

		THEN("Должно быть 29 февраля")
		{
			CHECK(date.GetDay() == 29);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 2000);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("Создаем дату с timestamp на 29 февраля 2100 года")
	{
		CDate date(47541);

		THEN("Должно быть 1 марта, так как 2100 - не високосный год")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::MARCH);
			CHECK(date.GetYear() == 2100);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}
}

SCENARIO("Проверка определения валидности дат")
{
	WHEN("Создаем дату соответсвующую нижней границе")
	{
		CDate date(1, Month::JANUARY, 1970);

		THEN("Дата валидна")
		{
			CHECK(date.IsValid());
		}

		AND_WHEN("Декриментируем дату")
		{
			date--;
			THEN("Результат не валиден")
			{
				CHECK(!date.IsValid());
			}
		}
	}

	WHEN("Создаем дату соответсвующую верхней границе")
	{
		CDate date(31, Month::DECEMBER, 9999);

		THEN("Дата валидна")
		{
			CHECK(date.IsValid());
		}

		AND_WHEN("Инкриментируем дату")
		{
			date++;

			THEN("Результат не валиден")
			{
				CHECK(!date.IsValid());
			}
		}
	}
}

SCENARIO("Проверка работы операций инкримента и декримента и изменения пограничных значений при помощи них")
{
	GIVEN("Случайная дата посреди меcяца")
	{
		CDate date(15, Month::JUNE, 2000);

		WHEN("Инкриментируем дату")
		{
			date++;

			THEN("Дата стала на одну больше")
			{
				CHECK(date.GetDay() == 16);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2000);
			}
		}

		WHEN("Декриментируем дату")
		{
			date--;

			THEN("Дата стала на один день меньше")
			{
				CHECK(date.GetDay() == 14);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2000);
			}
		}
		
		WHEN("Создаем копию даты используя префиксный инкримент")
		{
			CDate dateCopy = ++date;

			THEN("Дата будет со следующим числом")
			{
				CHECK(dateCopy.GetDay() == 16);
			}
		}

		WHEN("Создаем копию даты используя постфиксный инкримент")
		{
			CDate dateCopy = date++;

			THEN("Дата будет с числом до увеличения")
			{
				CHECK(dateCopy.GetDay() == 15);
			}
		}

		WHEN("Создаем копию даты используя префиксный декримент")
		{
			CDate dateCopy = --date;

			THEN("Дата будет с предыдущим числом")
			{
				CHECK(dateCopy.GetDay() == 14);
			}
		}

		WHEN("Создаем копию даты используя постфиксный декримент")
		{
			CDate dateCopy = date--;

			THEN("Дата будет с тем же числом")
			{
				CHECK(dateCopy.GetDay() == 15);
			}
		}
	}

	GIVEN("Дата в начале года")
	{
		CDate date(1, Month::JANUARY, 2000);

		WHEN("Декриментируем дату")
		{
			date--;

			THEN("Получаем последний день предыдущего года")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 1999);
			}
		}
	}

	GIVEN("Дата в конце года")
	{
		CDate date(31, Month::DECEMBER, 1999);

		WHEN("Инкриментируем дату")
		{
			date++;

			THEN("Получаем первый день следующего года")
			{
				CHECK(date.GetDay() == 1);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 2000);
			}
		}
	}

	GIVEN("28 фераля в високосный год")
	{
		CDate date(28, Month::FEBRUARY, 2000);

		WHEN("Инкриментируем")
		{
			date++;

			THEN("Получаем 29-ое число")
			{
				CHECK(date.GetDay() == 29);
			}
		}
	}

	GIVEN("28 фераля в не високосный год")
	{
		CDate date(28, Month::FEBRUARY, 2100);

		WHEN("Инкриментируем")
		{
			date++;

			THEN("Получаем 29-ое число")
			{
				CHECK(date.GetDay() == 1);
				CHECK(date.GetMonth() == Month::MARCH);
			}
		}
	}
}

SCENARIO("Проведение операция сложения и вычитания из даты числа и проверка перевода даты")
{
	GIVEN("Случайно число")
	{
		CDate date(15, Month::MAY, 2023);

		WHEN("Прибавляем количество дней, чтобы не выйти за месяц")
		{
			date = date + 10;

			THEN("Числое дней увеличилось корректно")
			{
				CHECK(date.GetDay() == 25);
			}
		}

		WHEN("Прибавляем отрицательное количество дней")
		{
			date = date + -10;

			THEN("Числое дней уменьшилось корректно")
			{
				CHECK(date.GetDay() == 5);
			}
		}

		WHEN("Прибавляем количество дней, чтобы выйти за месяц")
		{
			date = date + 17;

			THEN("Числое дней увеличилось корректно")
			{
				CHECK(date.GetDay() == 1);
				CHECK(date.GetMonth() == Month::JUNE);
			}
		}

		WHEN("Прибавляем ровно год в днях")
		{
			date = date + 366;

			THEN("Все отслось тем же, а год изменился")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::MAY);
				CHECK(date.GetYear() == 2024);
			}
		}

		WHEN("Вычитаем количество дней, чтобы не выйти за месяц")
		{
			date = date - 10;

			THEN("Числое дней уменьшилос корректно")
			{
				CHECK(date.GetDay() == 5);
			}
		}

		WHEN("Вычитаем отрицательное количество дней")
		{
			date = date - -10;

			THEN("Числое дней увеличилось корректно")
			{
				CHECK(date.GetDay() == 25);
			}
		}

		WHEN("Вычитаем количество дней, чтобы выйти за месяц")
		{
			date = date - 15;

			THEN("Числое дней уменьшилось корректно")
			{
				CHECK(date.GetDay() == 30);
				CHECK(date.GetMonth() == Month::APRIL);
			}
		}

		WHEN("Вычитаем ровно год в днях")
		{
			date = date - 365;

			THEN("Все отслось тем же, а год изменился")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::MAY);
				CHECK(date.GetYear() == 2022);
			}
		}
	}
}

SCENARIO("Проверка работы операции минусы для нахождения разности дат")
{
	GIVEN("Дата 01.01.2010")
	{
		CDate date1(1, Month::JANUARY, 2010);

		AND_GIVEN("Дата в прошлом году (25.12.2009)")
		{
			CDate date2(25, Month::DECEMBER, 2009);

			THEN("Разница между ними будет равной 7")
			{
				int dif = date1 - date2;
				CHECK(dif == 7);
			}
		}

		AND_GIVEN("Дата после данной нам (03.01.2010)")
		{
			CDate date2(3, Month::JANUARY, 2010);

			THEN("Разница будет равна -2")
			{
				int dif = date1 - date2;
				CHECK(dif == -2);
			}
		}
	}
}

SCENARIO("Проверка операторов += и -=")
{
	GIVEN("Дата 12.12.2012")
	{
		CDate date(12, Month::DECEMBER, 2012);

		WHEN("Прибавляем к дате 10 дней")
		{
			date += 10;

			THEN("Дата стала 22.12.2012")
			{
				CHECK(date.GetDay() == 22);
			}
		}

		WHEN("Вычитаем из даты 10 дней")
		{
			date -= 10;

			THEN("Дата стала 02.12.2012")
			{
				CHECK(date.GetDay() == 2);
			}
		}
	}
}

SCENARIO("Проверка операторов ввода вывода")
{
	/*GIVEN("Дата 29.2.8000")
	{
		CDate date(29, Month::FEBRUARY, 8000);

		AND_GIVEN("Поток в который необходимо вывести дату")
		{
			std::ostringstream output;

			WHEN("Выводим дату")
			{
				output << date;

				THEN("В потоке находится заданная нами дата")
				{
					CHECK(output.str() == "29.2.8000");
				}
			}
		}
	}

	GIVEN("Входной поток в котором лежит корректная дата")
	{
		std::istringstream input("9.7.2010");

		AND_GIVEN("Дата, в которую нужно прочесть дату")
		{
			CDate date;

			WHEN("Читаем дату из входного потока")
			{
				input >> date;

				THEN("В дате лежат все заданные нами значения")
				{
					CHECK(date.GetDay() == 9);
					CHECK(date.GetMonth() == Month::JULY);
					CHECK(date.GetYear() == 2010);
				}
			}
		}
	}*/
}

SCENARIO("Проверка операторов сравнения")
{
	WHEN("Берем два одинаковых числа")
	{
		CDate date(1241);
		CDate date2(1241);

		THEN("Вычисления соответсвуют булевой логике")
		{
			CHECK((date == date2));
			CHECK(!(date != date2));
			CHECK(!(date < date2));
			CHECK(!(date > date2));
			CHECK((date <= date2));
			CHECK((date >= date2));
		}
	}

	WHEN("Берем два разных числа")
	{
		CDate date(100);
		CDate date2(101);

		THEN("Вычилсения соответсвуют булевой логике")
		{
			CHECK(!(date == date2));
			CHECK((date != date2));
			CHECK((date < date2));
			CHECK(!(date > date2));
			CHECK((date <= date2));
			CHECK(!(date >= date2));
		}
	}
}