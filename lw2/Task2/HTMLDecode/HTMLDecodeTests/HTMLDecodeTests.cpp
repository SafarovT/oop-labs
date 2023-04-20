#include "../../../../external/catch2/catch.hpp"
#include "../HTMLDecode/HTMLDecode.h"

TEST_CASE("HTMLDecode: Simple input")
{
	std::string testString = "abcd &quot;S efg";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "abcd \"S efg");
}

TEST_CASE("HTMLDecode: Nothing to change")
{
	std::string testString = "abcd &quotS efg";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "abcd &quotS efg");
}

TEST_CASE("HTMLDecode: Coded symbol after another uncompleted")
{
	std::string testString = "abcd &quo&gt; efg";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "abcd &quo> efg");
}

TEST_CASE("HTMLDecode: Coded symbol immideately after another")
{
	std::string testString = "abcd &apos;&lt; efg";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "abcd \'< efg");
}

TEST_CASE("HTMLDecode: Coded symbol right before eoln")
{
	std::string testString = "&amp;";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "&");
}

TEST_CASE("rustam")
{
	std::string testString = "&ap&apos;os;;;;";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "&ap'os;;;;");
}

TEST_CASE("HTMLDecode: Coded symbol after &amp;")
{
	std::string testString = "&amp;lt;";
	std::string result = HTMLDecode(testString);
	REQUIRE(result == "&lt;");
}