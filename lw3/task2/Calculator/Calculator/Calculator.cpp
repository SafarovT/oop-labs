#include "Calculator.h"


void Calculator::StartWork(std::istream& inputStream, std::ostream& outputStream)
{
	std::string input = ReadUserCommand(inputStream, outputStream);
	while (input != EXIT_COMMAND)
	{

	}
}

std::string Calculator::ReadUserCommand(std::istream& inputStream, std::ostream& outputStream) const
{
	std::string input;
	do
	{
		outputStream << BEFORE_USER_INPUT_MESSAGE;
		std::getline(inputStream, input);
	} while (input.empty());

	return input;
}