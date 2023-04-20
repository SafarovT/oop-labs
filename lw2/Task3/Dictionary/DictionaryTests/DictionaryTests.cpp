#include "../../../../external/catch2/catch.hpp"
#include "../Dictionary/Dictionary.h"
#include <sstream>


TEST_CASE("GetDictionary: not valid input")
{
	std::istringstream inputString("abcd");
	auto dictionary = GetDictionary(inputString);

	REQUIRE(!dictionary);
}

TEST_CASE("GetDictionary: valid input")
{
	std::istringstream inputString("   [CAT] Кошка,    Кот\n[DOG]Собака,Кот");
	auto dictionary = GetDictionary(inputString);
	Translations correctResult = { {"CAT", {"Кошка", "Кот"}}, {"DOG", {"Собака", "Кот"}}};
	Translations correctResultReversed = { {"Кошка", {"CAT"}}, {"Кот", {"CAT", "DOG"}}, {"Собака", {"DOG"}}};

	bool areResultsCorrect = (dictionary->translations == correctResult) && (dictionary->reversedTranslations == correctResultReversed);
	REQUIRE(areResultsCorrect);
}

TEST_CASE("GetDictionary: input with []")
{
	std::istringstream inputString("   [] Кошка,    Кот\n[DOG]Собака");
	auto dictionary = GetDictionary(inputString);
	Translations correctResult = { {"DOG", {"Собака"}} };
	Translations correctResultReversed = { {"Собака", {"DOG"}} };

	bool areResultsCorrect = (dictionary->translations == correctResult) && (dictionary->reversedTranslations == correctResultReversed);
	REQUIRE(areResultsCorrect);
}

TEST_CASE("GetWordTranslations: Key word")
{
	std::istringstream inputString("   [CAT] Кошка,   Kot\n[DOG]Собака,KOt");
	auto dictionary = GetDictionary(inputString);
	auto translations = GetWordTranslations(*dictionary, "cAt");
	auto translationsReversed = GetWordTranslations(*dictionary, "kOT");
	bool areResultsCorrect = (*translations == "Кошка, Kot") && (*translationsReversed == "CAT, DOG");
	REQUIRE(areResultsCorrect);
}

TEST_CASE("SaveDictionary")
{
	std::istringstream inputString("   [CAT] Koshka,    kot\n[DOG]sobaka,kot");
	auto dictionary = GetDictionary(inputString);
	std::ostringstream outputString("");
	SaveDictionary(*dictionary, outputString);

	REQUIRE(outputString.str() == "[CAT] Koshka, kot\n[DOG] sobaka, kot\n");
}