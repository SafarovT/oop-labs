#include "../../../external/catch2/catch.hpp"
#include "../WorkWithVector/VectorHandler.h"
#include <sstream>

TEST_CASE("ReadVector: Empty input")
{
	VectorType vector;
	std::istringstream input("");
	REQUIRE(!ReadVector(input, vector));
}

TEST_CASE("ReadVector: Normal vector")
{
	VectorType vector;
	VectorType expectedResultVector = { -1, 2, 3, 0, 4 };
	std::istringstream input("-1 2 3 0 4");
	ReadVector(input, vector);
	REQUIRE(vector == expectedResultVector);
}

TEST_CASE("MultVectorOnMinValue: Mult on min (negative) element")
{
	VectorType vector = { -1, -1, 2, 3, 0, 4 };
	VectorType expectedResultVector = { 1, 1, -2, -3, 0, -4 };
	MultVectorOnMinValue(vector);
	REQUIRE(vector == expectedResultVector);
}

TEST_CASE("MultVectorOnMinValue: Mult one-element-input on 1")
{
	VectorType vector = { 1 };
	VectorType expectedResultVector = { 1 };
	MultVectorOnMinValue(vector);
	REQUIRE(vector == expectedResultVector);
}

TEST_CASE("PrintVectorSorted: Print not sorted vector")
{
	VectorType vector = { 1, -10, 0, -3, 0, 4, 3, 5 };
	std::ostringstream expectedOutput("-10 -3 0 0 1 3 4 5 ");
	std::ostringstream output("");

	PrintVectorSorted(output, vector);
	REQUIRE(output.str() == expectedOutput.str());
}

TEST_CASE("PrintVectorSorted: Print already sorted vector ")
{
	VectorType vector = { -2, -1, 0, 1, 2 };
	std::ostringstream expectedOutput("-2 -1 0 1 2 ");
	std::ostringstream output("");

	PrintVectorSorted(output, vector);
	REQUIRE(output.str() == expectedOutput.str());
}


TEST_CASE("PrintVectorSorted: Mult on zero ")
{
	VectorType vector = { 0, 1, 2, 3, 4 };
	std::ostringstream expectedOutput("0 0 0 0 0 ");
	std::ostringstream output("");

	MultVectorOnMinValue(vector);
	PrintVectorSorted(output, vector);
	REQUIRE(output.str() == expectedOutput.str());
}