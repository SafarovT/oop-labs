#include "../../../external/catch2/catch.hpp"
#include "../CMyArray/CMyArray.h"

SCENARIO("Проверка работы массива с целочисленными значениями")
{
	CMyArray<int> arr(2);
	arr.Push(1);
	arr.Push(2);
	arr.Clear();
}