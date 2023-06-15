﻿#include "../../../external/catch2/catch.hpp"
#include "../CMyStack/CMyStack.h"
#include <string>

SCENARIO("Работа со стеком строк, при помощи его методов")
{
	GIVEN("Пустой стек")
	{
		CMyStack<std::string> stack;

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

SCENARIO("Работа с несколькими стеками строк одновременно, присваивание, перемещающие конструкторы")
{
	GIVEN("Два стека, одни пустой, второй с тремя элементами")
	{
		CMyStack<std::string> stack1;
		CMyStack<std::string> stack2;
		stack2.Push("First");
		stack2.Push("Second");
		stack2.Push("Third");


		WHEN("Пустому стеку присваиваем заполненный")
		{
			stack1 = stack2;

			THEN("Второй стек остался незименными, в первом лежат теперь все три элемента в корректном порядке")
			{
				CHECK(stack2.GetTop() == stack1.GetTop());
				stack1.Pop();
				stack2.Pop();
				CHECK(stack2.GetTop() == stack1.GetTop());
				stack1.Pop();
				stack2.Pop();
				CHECK(stack2.GetTop() == stack1.GetTop());
				stack1.Pop();
				stack2.Pop();
				CHECK(stack1.Empty());
				CHECK(stack2.Empty());
			}

			AND_WHEN("Изменяем изначальный стек")
			{
				stack2.Push("Fouth");

				THEN("Первый остается без изменений")
				{
					CHECK(stack1.GetTop() == "Third");
					CHECK(stack1.GetSize() == 3);
				}
			}
		}

		WHEN("Пустому стеку присваиваем заполненный при помощи move конструктора")
		{
			stack1 = std::move(stack2);

			THEN("stack 2 пустой")
			{
				CHECK(stack2.Empty());
			}

			THEN("Второй стек остался незименными, в первом лежат теперь все три элемента в корректном порядке")
			{
				CHECK(stack1.GetTop() == "Third");
				stack1.Pop();
				CHECK(stack1.GetTop() == "Second");
				stack1.Pop();
				CHECK(stack1.GetTop() == "First");
			}
		}

		WHEN("Полному стеку присваиваем пустой")
		{
			stack2 = stack1;

			THEN("Оба стека пусты")
			{
				CHECK(stack1.Empty());
				CHECK(stack2.Empty());
			}
		}
	}
}

SCENARIO("Работа со стеками целочисленных значений")
{
	CMyStack<int> stack;

	THEN("Длина стека равна 0")
	{
		CHECK(stack.Empty());
	}

	WHEN("Кладем значение в стек")
	{
		stack.Push(1234);

		THEN("Значение стека изменилось")
		{
			CHECK(stack.GetSize() == 1);
			CHECK(stack.GetTop() == 1234);
		}

		AND_WHEN("Очищаем стек")
		{
			stack.Clear();

			THEN("Стек пустой")
			{
				CHECK(stack.Empty());
			}
		}

		AND_WHEN("Очищаем извлекая беря первый элемент")
		{
			stack.Pop();

			THEN("Стек пустой")
			{
				CHECK(stack.Empty());
			}
		}
	}
}

SCENARIO("Работа со стеками чисел с дробной частью значений")
{
	CMyStack<double> stack;

	THEN("Длина стека равна 0")
	{
		CHECK(stack.Empty());
	}

	WHEN("Кладем значение в стек")
	{
		stack.Push(1.3456);

		THEN("Значение стека изменилось")
		{
			CHECK(stack.GetSize() == 1);
			CHECK(stack.GetTop() == 1.3456);
		}

		AND_WHEN("Очищаем стек")
		{
			stack.Clear();

			THEN("Стек пустой")
			{
				CHECK(stack.Empty());
			}
		}

		AND_WHEN("Очищаем извлекая беря первый элемент")
		{
			stack.Pop();

			THEN("Стек пустой")
			{
				CHECK(stack.Empty());
			}
		}
	}
}
