#include "PrimeNumbers.h"
#include <iostream>
#include <optional>
#include <string>

std::optional<Number> ParseArgs(int argc, char* argv[])
{
	Number number;
	if (argc != 2)
	{
		std::cout << "Invalid argument count" << std::endl
			<< "Usage: replace.exe <byte>" << std::endl;
		return std::nullopt;
	}
	try
	{
		number = std::stoi(argv[1]);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << "Please, enter a number in [0, 255]";
		return std::nullopt;
	}
	catch (std::out_of_range& e)
	{
		std::cout << "Please, enter a number in [0, 255]";
		return std::nullopt;
	}
	return number;
}

int main(int argc, char* argv[])
{
	auto upperBound = ParseArgs(argc, argv);
	if (!upperBound)
	{
		return EXIT_FAILURE;
	}

	NumbersSet primeNumbers = GeneratePrimeNumbersSet(*upperBound);
	std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<size_t>(std::cout, " "));

	return EXIT_SUCCESS;
}