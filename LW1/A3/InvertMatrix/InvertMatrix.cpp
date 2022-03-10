#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
    int matrix[3][3];
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <MatrixFile.txt>\n";
		return std::nullopt;
	}
	std::ifstream inputFile;
	inputFile.open(argv[1]);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file for reading \n";
		return std::nullopt;
	}

	Args args;
	int matrix[3][3];

	int inValue;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (inputFile >> inValue)
			{
				matrix[i][j] = inValue;
			}
			else
			{
				std::cout << "Enter a correct matrix with numbers";
				return std::nullopt;
			}
		}
	}

	args.matrix = matrix;

	if (inputFile.bad())
	{
		std::cout << "Failed to read data from input file \n";
		return std::nullopt;
	}
}

int main(int argc, char* argv[])
{
}