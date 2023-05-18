#include "../../../../external/catch2/catch.hpp"
#include "../Calculator/Calculator.h"

SCENARIO("Объявление, присваивание и вывод значений переменных")
{
	GIVEN("Одна переменная (x) без начального значения")
	{
		Calculator calculator;
		calculator.InitVariable("x");
		WHEN("Получаем значение переменной")
		{
			double xValue = calculator.GetValue("x");
			THEN("Значение будет NAN")
			{
				CHECK(std::isnan(xValue));
			}
		}

		WHEN("Присваиваем этой переменной определенное значение и затем берем ее значение")
		{
			calculator.InitVariable("x", (double)42);

			THEN("Значение будет таким, которое мы указали")
			{
				double xValue = calculator.GetValue("x");
				CHECK(xValue == 42);
			}
			
			AND_WHEN("Пытаемся изменить значение")
			{
				calculator.InitVariable("x", 1.2345);
				
				THEN("Значение изменилось")
				{
					double xValue = calculator.GetValue("x");
					CHECK(xValue == 1.2345);
				}

				AND_WHEN("Создаем новую переменную, значение которой берется из перменной x")
				{
					calculator.InitVariable("y", "x");

					THEN("При изменении изначальной переменной, созданная на ее базе не меняется")
					{
						calculator.InitVariable("x", 99);
						auto variables = calculator.GetVariables();
						CHECK((variables["x"].GetValue() == 99 && variables["y"].GetValue() == 1.2345));
					}
				}
			}
		}

		WHEN("Создаем переменную начинающаюся с символов")
		{
			bool success = calculator.InitVariable("123x");
			
			THEN("Ошибка")
			{
				CHECK(!success);
				//проверить что переменной действительно нет
			}
		}
	}
}

SCENARIO("Объявление функций, работа с ними")
{
	GIVEN("Создается калькулятор с двумя переменными")
	{
		Calculator calculator;

		calculator.InitVariable("x", 10);
		calculator.InitVariable("y", 15);

		WHEN("Создается функция с именем перемнной")
		{
			bool success = calculator.InitFunction("x", "y");

			THEN("Ошибка")
			{
				CHECK(!success);
			}
		}

		WHEN("Создается функция складывающая эти две перменные")
		{
			calculator.InitFunction("xPLUSy", "x", '+', "y");

			THEN("Значение функции высчитывается правильно")
			{
				CHECK(calculator.GetValue("xPLUSy") == 25);
			}

			AND_WHEN("Пытаемся создать переменную с таким же именем")
			{
				bool success = calculator.InitVariable("xPLUSy");

				THEN("Ошибка")
				{
					CHECK(!success);
				}
			}

			AND_WHEN("Создаем переменную со значением функции")
			{
				calculator.InitVariable("z", "xPLUSy");

				THEN("Значение равно значению функции")
				{
					CHECK(calculator.GetValue("z") == 25);

					AND_WHEN("Меняем одну из переменных, так чтобы функция имела другое значние")
					{
						calculator.InitVariable("x", 15);

						THEN("Значение функции изменилось, а переменной нет")
						{
							CHECK(((calculator.GetValue("z") == 25) && (calculator.GetValue("xPLUSy") == 30)));
						}
					}
				}
			}

			AND_WHEN("Пытаемся пересоздать функцию")
			{
				bool success = calculator.InitVariable("xPLUSy", "x");

				THEN("Ошибка")
				{
					CHECK(!success);
				}
			}
		}
		
		WHEN("Создается функция вычитающая эти две перменные")
		{
			calculator.InitFunction("yMINUSx", "y", '-', "x");

			THEN("Значение функции высчитывается правильно")
			{
				CHECK(calculator.GetValue("yMINUSx") == 5);
			}

			AND_WHEN("Создается функция делящая y на результат (y - x) ")
			{
				calculator.InitFunction("division", "y", '/', "yMINUSx");

				THEN("Значение функции высчитывается правильно")
				{
					CHECK(calculator.GetValue("division") == 3);
				}
			}
		}

		WHEN("Создается функция умнощающая эти две перменные")
		{
			calculator.InitFunction("xMULTy", "x", '*', "y");

			THEN("Значение функции высчитывается правильно")
			{
				CHECK(calculator.GetValue("xMULTy") == 150);
			}
		}

		WHEN("Создается функция равная одной из переменных")
		{
			calculator.InitFunction("fnX", "x");

			THEN("Переменная хранит x")
			{
				CHECK(calculator.GetValue("fnX") == 10);
			}

			AND_WHEN("Переменная изменяется")
			{
				calculator.InitVariable("x", 100);

				THEN("Значение функции так же изменилось")
				{
					CHECK(calculator.GetValue("fnX") == 100);
				}
			}
		}
	}
}