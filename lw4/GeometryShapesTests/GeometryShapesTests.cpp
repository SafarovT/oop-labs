#include "../../../../external/catch2/catch.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../GeometryShapes/CCircle.h"
#include "../GeometryShapes/CTriangle.h"
#include "../GeometryShapes/CRectangle.h"
#include "../GeometryShapes/CLineSegment.h"

SCENARIO("Создание фигур всех типов, проверка правильности вычисления их свойств")
{
	GIVEN("2 различных точек")
	{
		CPoint point1(0, 0);
		CPoint point2(3, 4);
		CPoint point3(0, 10);

		THEN("Все точки создались с верными координатами")
		{
			CHECK(point1.x == 0);
			CHECK(point1.y == 0);
			CHECK(point2.x == 3);
			CHECK(point2.y == 4);
			CHECK(point3.x == 0);
			CHECK(point3.y == 10);
		}

		WHEN("Создаем линию из точки 1 в точку 2 определенного цвета")
		{
			CLineSegment line(point1, point2, 0xFF00AA);

			THEN("Первая точка выставилась правильно")
			{
				CHECK(line.GetStartPoint().x == point1.x);
				CHECK(line.GetStartPoint().y == point1.y);
			}
			
			THEN("Вторая точка выставилась правильно")
			{
				CHECK(line.GetEndPoint().x == point2.x);
				CHECK(line.GetEndPoint().y == point2.y);
			}

			THEN("Периметер высчитывается правильно")
			{
				CHECK(line.GetPerimeter() == 5);
			}

			THEN("Площадь прямой равна 0")
			{
				CHECK(line.GetArea() == 0);
			}

			THEN("Цвет прямой стоит верный")
			{
				CHECK(line.GetOutlineColor() == 0xFF00AA);
			}
		}

		WHEN("Создается прямая нулевой длины")
		{
			CLineSegment line(point3, point3, 0);

			THEN("Длина равна 0")
			{
				CHECK(line.GetPerimeter() == 0);
			}
		}

		WHEN("Создается прямоугольник с определенным цветом заливки, проверяется его площадь и периметр")
		{
			CRectangle rect(point1, point2, 0xABCDEF, 0x123456);

			THEN("Левая вернхняя точка выставилась верно")
			{
				CHECK(rect.GetLeftTop().x == point1.x);
				CHECK(rect.GetLeftTop().y == point1.y);
			}

			THEN("Правая верхняя точка выставилась верно")
			{
				CHECK(rect.GetRightBottom().x == point2.x);
				CHECK(rect.GetRightBottom().y == point2.y);
			}

			THEN("Высота и ширина верны в нашей системы координат")
			{
				CHECK(rect.GetWidth() == 3);
				CHECK(rect.GetHeight() == 4);
			}

			THEN("Периметр высчитывается верно")
			{
				CHECK(rect.GetPerimeter() == 14);
			}

			THEN("Площадь верно высчитана")
			{
				CHECK(rect.GetArea() == 12);
			}
			
			THEN("Цвет заливки соотвествует указанному")
			{
				CHECK(rect.GetFillColor() == 0x123456);
			}
		}

		WHEN("Создается пряоугольник нулевой высота")
		{
			CRectangle rect(point1, point3, 0xABCDEF, 0x000000);

			THEN("Ширина равна нулю")
			{
				CHECK(rect.GetWidth() == 0);
			}

			THEN("Площадь равна нулю")
			{
				CHECK(rect.GetArea() == 0);
			}

			THEN("Периметр высчитывается верно")
			{
				CHECK(rect.GetPerimeter() == 20);
			}
		}

		WHEN("Создается круг с радиусом 16 в центре координат")
		{
			CCircle circle(point1, 16, 0x556677, 0x102345);

			THEN("Центр выставлен верно")
			{
				CHECK(circle.GetCenter().x == point1.x);
				CHECK(circle.GetCenter().y == point1.y);
			}

			THEN("Круг имеет ранее указанный адресс")
			{
				CHECK(circle.GetRadius() == 16);
			}

			THEN("Периметр высчитывается верно")
			{
				CHECK(circle.GetPerimeter() == 32 * M_PI);
			}

			THEN("Площад высчитывается верно")
			{
				CHECK(circle.GetArea() == 256 * M_PI);
			}
		}

		WHEN("Создается круг отрицательного радиуса")
		{
			CCircle circle(point1, -10, 0, 0);

			THEN("Радиус круга будет равен 0")
			{
				CHECK(circle.GetRadius() == 0);
			}

			THEN("Периметр круга равен нулю")
			{
				CHECK(circle.GetPerimeter() == 0);
			}

			THEN("Площадь круга равна нулю")
			{
				CHECK(circle.GetArea() == 0);
			}
		}

		WHEN("Создается треугольник")
		{
			CTriangle triangle(point1, point2, point3, 0, 0);

			THEN("Первая точка выставилась верно")
			{
				CHECK(triangle.GetVertex1().x == point1.x);
				CHECK(triangle.GetVertex1().y == point1.y);
			}

			THEN("Вторая точка выставилась верно")
			{
				CHECK(triangle.GetVertex2().x == point2.x);
				CHECK(triangle.GetVertex2().y == point2.y);
			}

			THEN("Третья точка выставилась верно")
			{
				CHECK(triangle.GetVertex3().x == point3.x);
				CHECK(triangle.GetVertex3().y == point3.y);
			}

			THEN("Периметр треугольника высчитывается верно")
			{
				CHECK(triangle.GetPerimeter() == (5 + 10 + 3 * sqrt(5)));
			}

			THEN("Площадь прямоугольника высчитывается верно")
			{
				CHECK(triangle.GetArea() == 15);
			}
		}

		WHEN("Создадим треугольник со всеми вершиннами в одной точке")
		{
			CTriangle triangle(point1, point1, point1, 1, 1);

			THEN("Периметр равен 0")
			{
				CHECK(triangle.GetPerimeter() == 0);
			}

			THEN("Площадь равна 0")
			{
				CHECK(triangle.GetArea() == 0);
			}
		}
	}
}