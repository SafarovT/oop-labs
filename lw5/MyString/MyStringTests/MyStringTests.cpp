#include "../../../external/catch2/catch.hpp"
#include "../MyString/CMyString.h"

namespace
{
	
bool AreStringsEqual(const char* str1, const char* str2)
	{
		return strcmp(str1, str2) == 0;
	}
}

SCENARIO("Создание строки класса CMyString всеми способами")
{
	WHEN("Создаем строку без изначальных данных")
	{
		CMyString str;

		THEN("Строка пустая и длина равна 0")
		{
			CHECK(AreStringsEqual(str.GetStringData(), ""));
			CHECK(str.GetLength() == 0);
			CHECK(str.GetStringData()[0] == '\0');
		}
	}

	GIVEN("Строка заданная при помощи const char*")
	{
		const char* sourceString = "Zero\0code";

		WHEN("Создаем строку")
		{
			CMyString str(sourceString);
			const char* resultUntilZeroCode = "Zero";

			THEN("Строка содержит все необходимые символы")
			{
				CHECK(AreStringsEqual(str.GetStringData(), resultUntilZeroCode));
				CHECK(str.GetLength() == 4);
				CHECK(str.GetStringData()[str.GetLength()] == '\0');

			}
			AND_WHEN("Создаем строку из всей изначальой строки символов")
			{
				CMyString str(sourceString, 9);

				THEN("Получаем полную изначальную строку")
				{
					CHECK(str.GetLength() == 9);
					CHECK(std::equal(str.GetStringData(), str.GetStringData() + str.GetLength(), sourceString));
					CHECK(str.GetStringData()[str.GetLength()] == '\0');
				}
			}
		}
	}

	GIVEN("stl строка")
	{
		std::string sourceString("Hello World!");

		WHEN("Создаем строчку на основе данной stl строки")
		{
			CMyString str(sourceString);

			THEN("Строка создалась верно")
			{
				CHECK(str.GetLength() == 12);
				CHECK(AreStringsEqual(str.GetStringData(), "Hello World!"));
				CHECK(str.GetStringData()[str.GetLength()] == '\0');
			}
		}
	}
}

SCENARIO("Тестирование методов CMyString")
{
	GIVEN("Строка Hello world!")
	{
		CMyString str("Hello world!");

		WHEN("Пробуем получить первое слово")
		{
			CMyString subStr = str.SubString(0, 5);

			THEN("Подстрока взята верно и последний символ - символ с нулевым кодом")
			{
				CHECK(AreStringsEqual(subStr.GetStringData(), "Hello"));
				CHECK(subStr.GetStringData()[subStr.GetLength()] == '\0');
			}
		}

		WHEN("Попытка взять из конца строки, но больше ее длина")
		{
			CMyString subStr = str.SubString(6, 20);

			THEN("Берется только доступное количество символов")
			{
				CHECK(subStr.GetLength() == 6);
				CHECK(AreStringsEqual(subStr.GetStringData(), "world!"));
			}
		}

		WHEN("Попытка взять подстроку из начальной позиции больше длины строки получаем исключение")
		{
			try
			{
				CMyString subStr = str.SubString(str.GetLength(), 1);
				CHECK(false);
			}
			catch (std::exception $excepton)
			{
				CHECK(true);
			}
		}

		WHEN("Очищаем строку")
		{
			str.Clear();

			THEN("Строка пустая и длина равна 0")
			{
				CHECK(AreStringsEqual(str.GetStringData(), ""));
				CHECK(str.GetLength() == 0);
				CHECK(str.GetStringData()[0] == '\0');
			}
		}
	}
}

SCENARIO("Проверка операций конкатенации")
{
	WHEN("Складываем строки типа CMyString") // проверять на maxLength
	{
		CMyString str1("Hello");
		CMyString space(" ");
		CMyString str2("world!");
		CMyString str = str1 + space + str2;

		THEN("Строка верно сложилась")
		{
			CHECK(str.GetLength() == 12);
			CHECK(AreStringsEqual(str.GetStringData(), "Hello world!"));
		}
	}

	WHEN("Складываем строки CMyString с std::string")
	{
		CMyString str1("Hello");
		std::string space(" ");
		std::string str2("world!");
		CMyString str = str1 + space + str2;

		THEN("Строка верно сложилась")
		{
			CHECK(str.GetLength() == 12);
			CHECK(AreStringsEqual(str.GetStringData(), "Hello world!"));
		}
	}

	WHEN("Складываем строки CMyString с const char*")
	{
		CMyString str1("Hello");
		const char* space = " ";
		const char* str2 = "world!";
		CMyString str = str1 + space + str2;

		THEN("Строка верно сложилась")
		{
			CHECK(str.GetLength() == 12);
			CHECK(AreStringsEqual(str.GetStringData(), "Hello world!"));
		}
	}
}

SCENARIO("Проверка операция булевой алгебры")
{
	GIVEN("Строка 1234")
	{
		CMyString str("1234");

		THEN("Сравнивая ее с различными строками получаем верный результат")
		{
			CHECK(str > CMyString("1233"));
			CHECK_FALSE(str > CMyString("1235"));
			CHECK(str < CMyString("1235"));
			CHECK_FALSE(str < CMyString("1233"));
			CHECK(str >= CMyString("1234"));
			CHECK_FALSE(str >= CMyString("1235"));
			CHECK(str <= CMyString("1234"));
			CHECK_FALSE(str <= CMyString("1233"));
			CHECK(str == CMyString("1234"));
			CHECK_FALSE(str == CMyString("12345"));
			CHECK(str != CMyString("12345"));
			CHECK_FALSE(str != CMyString("1234"));
		}
	}
}

SCENARIO("Проверка операций с потоками")
{
	GIVEN("Строка и поток")
	{
		CMyString str("Hello world!");
		std::stringstream stream;

		WHEN("Выводим строку в поток")
		{
			stream << str;

			THEN("Строка полностью и корректно вывелась в поток")
			{
				CHECK(stream.str() == "Hello world!");
			}

			AND_WHEN("Читаем выведенную строку из потока")
			{
				CMyString readStr;
				stream >> readStr;

				THEN("Строка равна изначально выведенной")
				{
					CHECK(readStr == str);
				}
			}
		}
	}
}

SCENARIO("Проверка копирования и перемещения строк")
{
	CMyString str("hello world!");
	CMyString str2("goodbye space?");

	WHEN("Присваеваем второй строке первую")
	{
		str2 = str;

		THEN("Получаем две одинаковые строки")
		{
			CHECK((str == str2));

			AND_THEN("В конце второй строки лежит символ с кодом 0")
			{
				CHECK(str2.GetStringData()[str2.GetLength()] == '\0');
			}
		}

		AND_WHEN("Добавляем к первой строке одно слово")
		{
			CMyString str3(" add");
			str += str3;

			THEN("Первая строка изменилась, вторая нет")
			{
				CHECK(AreStringsEqual(str.GetStringData(), "hello world! add"));
				CHECK(AreStringsEqual(str2.GetStringData(), "hello world!"));
			}
		}
	}

	WHEN("Создаем третью строку при помощи move конструктора")
	{
		CMyString str3(std::move(str));

		THEN("Получаем две одинаковые строки")
		{
			CHECK(AreStringsEqual(str3.GetStringData(), "hello world!"));

			AND_THEN("В конце третьей строки лежит символ с кодом 0")
			{
				CHECK(str3.GetStringData()[str3.GetLength()] == '\0');
			}
		}

		AND_WHEN("Инициализируем еще одну строку при помощи = c move контструктором")
		{
			CMyString str4 = std::move(str3);

			THEN("Получаем две одинаковые строки")
			{
				CHECK(AreStringsEqual(str4.GetStringData(), "hello world!"));

				AND_THEN("В конце четвертой строки лежит символ с кодом 0")
				{
					CHECK(str4.GetStringData()[str4.GetLength()] == '\0');
				}
			}
		}
	}
}

SCENARIO("Проверка оператора []")
{
	GIVEN("Строка std::string и созданная из не CMyString")
	{
		const std::string stlString = "Hello world!";
		CMyString str(stlString);

		WHEN("Берем первый элемент из строки")
		{
			char symbol = str[0];

			THEN("Он совпадает с элементом из изначальной строки")
			{
				CHECK(symbol == stlString[0]);
			}
		}

		WHEN("Берем последний элемент из строки")
		{
			const char symbol = str[str.GetLength() - 1];

			THEN("Он совпадает с элементом из изначальной строки")
			{
				CHECK(symbol == stlString[str.GetLength() - 1]);
			}
		}

		WHEN("Берем последний +1 элемент из строки")
		{

			THEN("Получаем исключение")
			{
				try
				{
					char symbol = str[str.GetLength()];
					CHECK(false);
				}
				catch (std::exception& exception)
				{
					CHECK(true);
				}
			}
		}
	}
}