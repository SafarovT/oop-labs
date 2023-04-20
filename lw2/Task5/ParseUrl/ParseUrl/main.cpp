#include "ParseURL.h";
#include <iostream>

const std::string USER_INPUT_TO_OFF_PROGRAM = "...";
const std::string STARTUP_MESSAGE = "Для завершения программы введите '...'";
const std::string INCORRECT_URL_MESSAGE = "Ссылка не распознана";
const std::string HOST_MESSAGE = "HOST: ";
const std::string PORT_MESSAGE = "PORT: ";
const std::string DOCUMENT_MESSAGE = "DOC: ";


void ReadUntilInputWithSymbols(std::string& input)
{
	do
	{
		std::getline(std::cin, input);
	} while (input.empty());
}

int main()
{
	std::string userInput;
	std::cout << STARTUP_MESSAGE << std::endl;
	do
	{
		ReadUntilInputWithSymbols(userInput);
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		if (ParseURL(userInput, protocol, port, host, document))
		{
			std::cout << HOST_MESSAGE << host << std::endl
				<< PORT_MESSAGE << port << std::endl
				<< DOCUMENT_MESSAGE << document << std::endl;
		}
		else
		{
			std::cout << INCORRECT_URL_MESSAGE << std::endl;
		}
	} while (userInput != USER_INPUT_TO_OFF_PROGRAM);

	return EXIT_SUCCESS;
}