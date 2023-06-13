#include "../../../external/catch2/catch.hpp"
#include "../FindMaxEx/FindMaxEx.cpp"
#include "CPerson.h"

TEST_CASE("Vector of integer")
{
	std::vector<int> arr = { -20, 2, 1, 3, 9, 8 };
	int maxValue = 0;
	bool isOperationSuccess = FindMax(arr, maxValue);
	CHECK(isOperationSuccess);
	CHECK(maxValue == 9);
}

TEST_CASE("Empty vector")
{
	std::vector<int> arr = {};
	int maxValue = 1;
	bool isOperationSuccess = FindMax(arr, maxValue);
	CHECK_FALSE(isOperationSuccess);
	CHECK(maxValue == 1);
}

TEST_CASE("Vector of double")
{
	std::vector<double> arr = { -1.3, 2.0, 9.99998, 9.99999 };
	double maxValue = 1;
	bool isOperationSuccess = FindMax(arr, maxValue);
	CHECK(isOperationSuccess);
	CHECK(maxValue == 9.99999);
}

TEST_CASE("Vector of std::string")
{
	std::vector<std::string> arr = { "", "abcdefg", "abcdefG" };
	std::string maxValue = "err value";
	bool isOperationSuccess = FindMax(arr, maxValue);
	CHECK(isOperationSuccess);
	CHECK(maxValue == "abcdefg");
}

TEST_CASE("Vector of persons by their height")
{
	CPerson person1("Safarov Tahir Maratovich", 179, 69);
	CPerson person2("Safarov Marat Gazyamovych", 186, 100);
	CPerson person3("Max height person", 187, 50);
	std::vector<CPerson> arr = { person2, person1, person3 };
	CPerson maxValue;

	auto lessBaseOnHeight = [](CPerson person1, CPerson person2)
	{
		return person1.GetHeight() < person2.GetHeight();
	};

	bool isOperationSuccess = FindMax(arr, maxValue, lessBaseOnHeight);
	CHECK(isOperationSuccess);
	CHECK((maxValue == person3));
}

TEST_CASE("Vector of persons by their weight")
{
	CPerson person1("Min weight person", 200, 99);
	CPerson person2("Avarage weight person", 100, 100);
	CPerson person3("Max height person", 50, 101);
	std::vector<CPerson> arr = { person2, person1, person3 };
	CPerson maxValue;

	auto lessBaseOnWeight = [](CPerson person1, CPerson person2)
	{
		return person1.GetWeight() < person2.GetWeight();
	};

	bool isOperationSuccess = FindMax(arr, maxValue, lessBaseOnWeight);
	CHECK(isOperationSuccess);
	CHECK((maxValue == person3));
}