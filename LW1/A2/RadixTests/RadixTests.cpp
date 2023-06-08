#include "../../../external/catch2/catch.hpp"
#include "../Radix/Radix.h"

using namespace std;

TEST_CASE("StringToInt: some number in min radix")
{
	string str = "101";
	int number = StringToInt(str, 2);
	REQUIRE(number == 5);
}

TEST_CASE("StringToInt: some number in max radix")
{
	string str = "ZY";
	int number = StringToInt(str, 36);
	REQUIRE(number == 1294);
}

TEST_CASE("StringToInt: 0 number")
{
	string str = "0";
	int number = StringToInt(str, 12);
	REQUIRE(number == 0);
}

TEST_CASE("StringToInt: negative number")
{
	string str = "-ZY";
	int number = StringToInt(str, 36);
	REQUIRE(number == -1294);
}

TEST_CASE("StringToInt: radix < MIN_RADIX")
{
	string str = "10";
	try
	{
		int number = StringToInt(str, 1);
		REQUIRE(false);
	}
	catch (invalid_argument& e)
	{
		REQUIRE(true);
	}
}

TEST_CASE("StringToInt: radix > MAX_RADIX")
{
	string str = "10";
	try
	{
		int number = StringToInt(str, 37);
		REQUIRE(false);
	}
	catch (invalid_argument& e)
	{
		REQUIRE(true);
	}
}

TEST_CASE("StringToInt: not a number in str")
{
	string str = "12$%^";
	try
	{
		int number = StringToInt(str, 36);
		REQUIRE(false);
	}
	catch (invalid_argument& e)
	{
		REQUIRE(true);
	}
}

TEST_CASE("StringToInt: digit >= radix")
{
	string str = "1A1";
	try
	{
		int number = StringToInt(str, 10);
		REQUIRE(false);
	}
	catch (invalid_argument& e)
	{
		REQUIRE(true);
	}
}

TEST_CASE("IntToString: number to min radix")
{
	int num = 5;
	string str = IntToString(num, 2);
	REQUIRE(str == "101");
}

TEST_CASE("IntToString: number to MAX radix")
{
	int num = 1294;
	string str = IntToString(num, 36);
	REQUIRE(str == "ZY");
}

TEST_CASE("IntToString: 0 number")
{
	int num = 0;
	string str = IntToString(num, 15);
	REQUIRE(str == "0");
}

TEST_CASE("IntToString: negative number")
{
	int num = -1294;
	string str = IntToString(num, 36);
	REQUIRE(str == "-ZY");
}

TEST_CASE("IntToString: radix < MIN_RADIX")
{
	int num = 10;
	try
	{
		string str = IntToString(num, 1);
		REQUIRE(false);
	}
	catch (invalid_argument& e)
	{
		REQUIRE(true);
	}
}

TEST_CASE("IntToString: radix > MAX_RADIX")
{
	int num = 10;
	try
	{
		string str = IntToString(num, 37);
		REQUIRE(false);
	}
	catch (invalid_argument& e)
	{
		REQUIRE(true);
	}
}

TEST_CASE("Checking MAX_INT to be correctly read")
{
	string str = "2147483647";
	int num = StringToInt(str, 10);
	CHECK(num == numeric_limits<int>::max());
}

TEST_CASE("Checking MIN_INT to be correctrly read")
{
	string str = "-2147483647";
	int num = StringToInt(str, 10);
}