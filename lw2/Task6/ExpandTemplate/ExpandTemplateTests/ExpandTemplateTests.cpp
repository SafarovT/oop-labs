#include "../../../../external/catch2/catch.hpp"
#include "../ExpandTemplate/ExpandTemplate.h"

TEST_CASE("ExpandTemplate: Empty string to replace in params")
{
	TemplateParams params = {
		{"%USER_NAME%", "Ivan Petrov"},
		{"{WEEK_DAY}", "Friday"},
		{"", "0"},
		{"Hello, ", ""}
	};
	std::string result = ExpandTemplate("Hello, %USER_NAME%. Today is {WEEK_DAY}.", params);
	REQUIRE(result == "Ivan Petrov. Today is Friday.");
}

TEST_CASE("ExpandTemplate: Recursive repetition of a template")
{
	TemplateParams params = {
		{"%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}"},
		{"{WEEK_DAY}", "Friday. {WEEK_DAY}"}
	};
	std::string result = ExpandTemplate("Hello, %USER_NAME%. Today is {WEEK_DAY}", params);
	REQUIRE(result == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}");
}

TEST_CASE("ExpandTemplate: Template with prefix equilate to ohter template")
{
	TemplateParams params = {
		{"A", "[a]"},
		{"AA", "[aa]"},
		{"BAA", "[baa]"},
		{"B", "[b]"},
		{"BE", "[be]"},
		{"C", "[c]"},
		{"CC", "[cc]"},
	};
	std::string result = ExpandTemplate("AABAABECCABCBAA", params);
	REQUIRE(result ==  "[aa][baa][be][cc][a][b][c][baa]");
}

TEST_CASE("ExpandTemplate: Lenochka")
{
	TemplateParams params = {
		{"ENOT", "[enot]"},
		{"NOTA", "[nota]"},
		{"NOCH", "[noch]"},
		{"NOCHKA", "[nochka]"},
	};
	std::string result = ExpandTemplate("LENOCHKE", params);
	REQUIRE(result == "LE[noch]KE");
}