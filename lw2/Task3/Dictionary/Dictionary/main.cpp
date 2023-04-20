#include "Dictionary.h";

const std::string STARTUP_MESSAGE = "Введите слово чтобы перевести или '...', чтобы завершить работу программы";
const std::string UKNOWN_WORD_MESSAGE = "Неизвестное слово @. Введите переводы, или пустую строку для отказа"; //TODO: format
const std::string ENTER_TRANSLATIONS = "Введите возможные переводы для слова: ";
const std::string ENTER_WORD_TO_TRANSLATE = "Введите то слово, для которого он(-и) будут переводом: ";
const std::string ASK_TO_SAVE_DICTIONARY = "В словарь были внесены изменения, введите 'Y', чтобы сохранить данные в файл";
const std::string BEFORE_USER_INPUT_MESSAGE = ">";
const std::string USER_INPUT_TO_OFF_PROGRAM = "...";

std::optional<std::string> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <DictionaryFile.txt>\n";
		return std::nullopt;
	}

	return argv[1];
}

std::string getUnknownMessageWithWord(std::string const& word)//TODO: UpperCamelCase
{
	int wordInStringPosition = UKNOWN_WORD_MESSAGE.find("@");
	return UKNOWN_WORD_MESSAGE.substr(0, wordInStringPosition) + word + UKNOWN_WORD_MESSAGE.substr(wordInStringPosition + 1);
}

void ReadUntilInputWithSymbols(std::string& input)
{
	do
	{
		std::cout << BEFORE_USER_INPUT_MESSAGE << " ";
		std::getline(std::cin, input);
	} while (input.empty());
}

bool DialogueWithUser(Dictionary& dictionary)
{
	bool isDictionaryEdited = false;
	std::string inputedString;//TODO: 
	std::cout << STARTUP_MESSAGE << std::endl;
	ReadUntilInputWithSymbols(inputedString);
	while (inputedString != USER_INPUT_TO_OFF_PROGRAM)
	{
		auto translations = GetWordTranslations(dictionary, inputedString);
		if (!translations)
		{
			std::cout << getUnknownMessageWithWord(inputedString) << std::endl;
			std::string userAnswer;
			std::getline(std::cin, userAnswer);
			if (!userAnswer.empty())
			{
				InsertRowInDictionary(dictionary, inputedString, userAnswer);
				isDictionaryEdited = true;
			}
		}
		else
		{
			std::cout << *translations << std::endl;
		}
		ReadUntilInputWithSymbols(inputedString);
	}

	return isDictionaryEdited;
}

bool AskToSaveDictionary()
{
	std::string userAnswer;
	std::cout << ASK_TO_SAVE_DICTIONARY << std::endl;
	std::getline(std::cin, userAnswer);

	return userAnswer == "Y";
}

int main(int argc, char* argv[])
{
	auto fileName = ParseArgs(argc, argv);
	if (!fileName)
	{
		return EXIT_FAILURE;
	}
	auto dictionary = GetDictionary(*fileName);
	if (!dictionary)
	{
		return EXIT_FAILURE;
	}

	bool isDictionaryEdited = DialogueWithUser(*dictionary);
	if (isDictionaryEdited
		&& AskToSaveDictionary()
		&& !SaveDictionary(*dictionary, *fileName)
	)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}