#include "../../../../external/catch2/catch.hpp"
#include "../PrimeNumbers/PrimeNumbers.h"

TEST_CASE("GeneratePrimeNumbersSet: upperBound < 2")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(1);

	REQUIRE(resultSet.empty());
}

TEST_CASE("GeneratePrimeNumbersSet: upperBound = 2")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(2);
	NumbersSet expectedResult = { 2 };

	REQUIRE(resultSet == expectedResult);
}

TEST_CASE("GeneratePrimeNumbersSet: upperBound = 9; checking the loop before sqrt(upperBound)")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(9);
	NumbersSet expectedResult = { 2, 3, 5, 7 };

	REQUIRE(resultSet == expectedResult);
}

TEST_CASE("GeneratePrimeNumbersSet: upperBound = 97 - 1")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(96);
	NumbersSet expectedResult = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89 };

	REQUIRE(resultSet == expectedResult);
}

TEST_CASE("GeneratePrimeNumbersSet: upperBound = 97 + 1")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(98);
	NumbersSet expectedResult = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	REQUIRE(resultSet == expectedResult);
}

TEST_CASE("GeneratePrimeNumbersSet: upperBound = 97")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(97);
	NumbersSet expectedResult = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	REQUIRE(resultSet == expectedResult);
}

TEST_CASE("GeneratePrimeNumbersSet: upperBound = 100 000 000 (checking length)")
{
	NumbersSet resultSet = GeneratePrimeNumbersSet(100000000);

	REQUIRE(resultSet.size() == 5761455);
}