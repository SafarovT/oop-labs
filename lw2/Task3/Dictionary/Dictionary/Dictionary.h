#pragma once
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>
#include <algorithm>

namespace
{
	std::string StringToLowerCase(std::string stringToTransform)
	{
		std::transform(stringToTransform.cbegin(), stringToTransform.cend(), stringToTransform.begin(), tolower);

		return stringToTransform;
	}

	struct CaseInsansitiveComparator
	{
		bool operator() (std::string const& s1, std::string const& s2) const
		{
			return  StringToLowerCase(s1) < StringToLowerCase(s2);
		}
	};
}

using TranslationVariants = std::vector<std::string>;
using Translations = std::map<std::string, TranslationVariants, CaseInsansitiveComparator>;
using Dictionary = struct {
	Translations translations;
	Translations reversedTranslations;
};

std::optional<std::string> GetWordTranslations(Dictionary const& dictionary, std::string const& wordToTranslate);
std::optional<Dictionary> GetDictionary(std::istream& input);
std::optional<Dictionary> GetDictionary(std::string const& inputFileName);
void InsertRowInDictionary(Dictionary& dictionary, std::string const& keyWord, std::string const& translationsString);
bool SaveDictionary(Dictionary const& dictionary, std::ostream& output);
bool SaveDictionary(Dictionary const& dictionary, std::string const& outputFilePath);
