#include "Dictionary.h";
#include <fstream>
#include <algorithm>

namespace
{
	using namespace std;
	
	const char KEY_WORD_START = '[';
	const char KEY_WORD_END = ']';
	const char TRANSLATIONS_SEPARATOR = ',';

	bool IsElementFound(size_t foundIndex)
	{
		return foundIndex != string::npos;
	}

	void LeftTrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	void RighTrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	string Trim(std::string s) {
		RighTrim(s);
		LeftTrim(s);

		return s;
	}
	
	string Implode(TranslationVariants const& translationsToImplode, char separator)
	{
		string translationsString = translationsToImplode[0];
		for (auto translation = translationsToImplode.begin() + 1; translation < translationsToImplode.end(); translation++)
		{
			translationsString = translationsString + separator + ' ' + *translation;
		}

		return translationsString;
	}

	TranslationVariants Explode(string stringToExplode, char separator)
	{
		size_t translationSeparatorPos = stringToExplode.find(separator);
		TranslationVariants resultTranslations;
		while (IsElementFound(translationSeparatorPos))  
		{
			resultTranslations.push_back(Trim(stringToExplode.substr(0, translationSeparatorPos)));
			stringToExplode = stringToExplode.substr(translationSeparatorPos + 1);
			translationSeparatorPos = stringToExplode.find(separator);
		}
		resultTranslations.push_back(Trim(stringToExplode));

		return resultTranslations;
	}
}

void InsertRowInDictionary(Dictionary& dictionary, std::string const& keyWord, std::string const& translationsString)
{
	TranslationVariants translationVariants = Explode(translationsString, TRANSLATIONS_SEPARATOR);
	dictionary.translations.emplace(keyWord, translationVariants);
	for (string variant : translationVariants)
	{
		auto foundTranslation = dictionary.reversedTranslations.find(variant);
		if (foundTranslation != dictionary.reversedTranslations.end())
		{
			foundTranslation->second.push_back(keyWord);
		}
		else
		{
			TranslationVariants wrappedKeyWord = { keyWord };
			dictionary.reversedTranslations.emplace(variant, wrappedKeyWord);
		}
	}
}

optional<Dictionary> GetDictionary(istream& input)
{
	string readLine;
	Dictionary dictionary;
	while (getline(input, readLine))
	{
		size_t keyWordStartPos = readLine.find(KEY_WORD_START);
		size_t keyWordEndPos = readLine.find(KEY_WORD_END);
		if (IsElementFound(keyWordStartPos) && IsElementFound(keyWordStartPos))
		{
			string keyWord = Trim(readLine.substr(keyWordStartPos + 1, keyWordEndPos - keyWordStartPos - 1));
			if (keyWord.empty())
			{
				continue;
			}

			InsertRowInDictionary(dictionary, keyWord, readLine.substr(keyWordEndPos + 1));
		}
		else
		{
			cout << "Error while reading a dictionary from file" << endl;
			return nullopt;
		}
	}

	return dictionary;
}

optional<Dictionary> GetDictionary(string const& inputFilePath)
{
	ifstream inputFile;
	inputFile.open(inputFilePath);
	if (!inputFile.is_open())
	{
		cout << "Failed to open file " << inputFilePath << endl;

		return nullopt;
	}

	auto dictionary = GetDictionary(inputFile);

	if (inputFile.bad() || !dictionary)
	{
		cout << "Failed to read data from file " << inputFilePath << endl;
		return nullopt;
	}

	return dictionary;
}
optional<string> GetWordTranslations(Dictionary const& dictionary, string const& wordToTranslate)
{
	auto foundTranslations = dictionary.translations.find(wordToTranslate);
	if (foundTranslations != dictionary.translations.end())
	{
		return Implode(foundTranslations->second, TRANSLATIONS_SEPARATOR);
	}

	auto foundReversedTranslations = dictionary.reversedTranslations.find(wordToTranslate);
	if (foundReversedTranslations != dictionary.reversedTranslations.end())
	{
		return Implode(foundReversedTranslations->second, TRANSLATIONS_SEPARATOR);
	}

	return nullopt;
}

bool SaveDictionary(Dictionary const& dictionary, std::ostream& output)
{
	for (const auto& translationPair : dictionary.translations)
	{
		output << "[" + translationPair.first + "]" + " " << Implode(translationPair.second, TRANSLATIONS_SEPARATOR) << endl;//TODO: use const
	}

	return true;
}

bool SaveDictionary(Dictionary const& dictionary, std::string const& outputFilePath)
{
	ofstream outputFile;
	outputFile.open(outputFilePath);
	if (!outputFile.is_open())
	{
		cout << "Failed to open file " << outputFilePath << endl;

		return false;
	}

	SaveDictionary(dictionary, outputFile);

	if (!outputFile.flush())
	{
		cout << "Failed to write data from file " << outputFilePath << endl;
		return false;
	}

	return true;
}