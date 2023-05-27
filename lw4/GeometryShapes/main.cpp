#include <iostream>
#include "CommandHandler.h"

int main()
{
	CommandHandler commandHandler(std::cin, std::cout);

	commandHandler.StartListening();
	commandHandler.PrintResult();
	commandHandler.DrawResult();

	return EXIT_SUCCESS;
}