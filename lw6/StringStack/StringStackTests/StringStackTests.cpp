#include "../../../external/catch2/catch.hpp"
#include "../StringStack/CStringStack.h"
#include <iostream>

SCENARIO("Работа со стеком, при помощи его методов")
{
	GIVEN("Пустой стек")
	{
		CStringStack stack;

		THEN("Длина стека равна 0")
		{
			CHECK(stack.GetSize() == 0);
			CHECK(stack.Empty());
		}

		WHEN("Пытаемся взять элемент")
		{
			THEN("Выбрасывается исключение")
			{
				CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
			}
		}

		WHEN("Пытаемся удалить элемент")
		{
			THEN("Выбрасывается исключение")
			{
				CHECK_THROWS_AS(stack.Pop(), std::logic_error);
			}
		}

		WHEN("Добавляем в стек элемент")
		{
			std::string str = "Hello world";
			stack.Push(str);

			THEN("Элемент добавился в стек")
			{
				CHECK(stack.GetSize() == 1); 
				CHECK_FALSE(stack.Empty());
				CHECK(stack.GetTop() == str);
			}

			AND_WHEN("Меняем изначальную строку")
			{
				str = "Bye";

				THEN("Не изменяется элемент в стеке")
				{
					CHECK(stack.GetTop() == "Hello world");
				}
			}

			AND_WHEN("Убираем только что добавленный элемент")
			{
				stack.Pop();

				THEN("Стек снова пустой")
				{
					CHECK(stack.Empty());
					CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
				}
			}

			AND_WHEN("Добавляем еще пару элементов")
			{
				std::string str2 = "second string";
				std::string str3 = "some string";
				stack.Push(str2);
				stack.Push(str3);

				THEN("Размер стека изменился")
				{
					CHECK(stack.GetSize() == 3);

					AND_THEN("Все элементы извлекаются в корректном порядке")
					{
						CHECK(stack.GetTop() == str3);
						stack.Pop();
						CHECK(stack.GetTop() == str2);
						stack.Pop();
						CHECK(stack.GetTop() == str);
					}
				}

				AND_WHEN("Очищаем стек")
				{
					stack.Clear();
					
					THEN("Стек пустой")
					{
						CHECK(stack.Empty());
					}
				}
			}
		}
	}
}