#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>

namespace
{
    using namespace std;

    using WordData = unordered_map<char, size_t>;
    using Dictionary = map<string, WordData>;

    WordData ReadWordData(string word)
    {
        if (word.empty())
        {
            return WordData();
        }

        if (word.size() == 1)
        {
            return WordData({ {word[0], 1} });
        }

        WordData wordData;
        sort(word.begin(), word.end());
        char symbol = word[0];
        size_t symbolsCount = 1;
        size_t wordLength = word.size();
        for (size_t i = 1; i < wordLength; i++)
        {
            if (symbol != word[i])
            {
                wordData.emplace(symbol, symbolsCount);
                symbolsCount = 1;
                symbol = word[i];
            }
            else
            {
                symbolsCount++;
            }
        }
        wordData.emplace(symbol, symbolsCount);

        return wordData;
    }

    Dictionary ReadDictionary(const string& file_name)
    {
        ifstream in{ file_name };
        string word;
        Dictionary dictionary;
        while (getline(in, word))
        {
            dictionary.emplace(word, ReadWordData(word));
        }

        return dictionary;
    }

    void ReadEternalWord(string& str)
    {
        str.clear();
        do
        {
            cout << "Eternal string: ";
            getline(cin, str);
        } while (str.empty());
    }

    /*
       * Возвращает множество слов из dictionary, которые можно составить из букв слова word.
       * Каждый символ строки word можно использовать только один раз.
       *
       * Например, из букв слова "машина" можно составить слово "шина" и "маша", но нельзя слово "мама", так как
       * недостаточно букв "м".
       *
       * Гарантируется, что word и строки в dictionary непустые и состоят только из строчных символов английского алфавита.
       * Размер dictionary - порядка нескольких сотен тысяч элементов
    */
    set<string> GetSubWords(const string& word, const Dictionary& dictionary)
    {
        set<string> subWords;
        WordData givenWordData = ReadWordData(word);

        for (auto wordFromDictionary : dictionary)
        {
            bool isSubWord = true;
            for (auto symbolData : wordFromDictionary.second)
            {
                auto givenWordSymbolData = givenWordData.find(symbolData.first);
                bool isSymbolFound = givenWordSymbolData == givenWordData.end();
                if (isSymbolFound || givenWordSymbolData->second < symbolData.second)
                {
                    isSubWord = false;
                }
            }

            if (isSubWord)
            {
                subWords.emplace_hint(subWords.end(), wordFromDictionary.first);
            }
        }

        return subWords;
    }
}

int main()
{
    using namespace std::chrono;

    auto dictionary = ReadDictionary("dict.txt");
    string word;
    ReadEternalWord(word);

    while (word != "...")
    {
        const auto startTime = steady_clock::now();
        const auto subWords = GetSubWords(word, dictionary);
        const auto dur = steady_clock::now() - startTime;

        for (const auto& sub_word : subWords) {
            std::cout << sub_word << std::endl;
        }

        std::cout << subWords.size() << " words have been found in "s
            << duration<double>(dur).count() << " seconds" << std::endl;

        ReadEternalWord(word);
    }


    return EXIT_SUCCESS;
}