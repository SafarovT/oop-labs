#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <MatrixFile.txt>\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
}

bool FileOpened(std::ifstream& inputFile, std::string inputFileName)
{
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file for reading \n";
		return false;
	}
	return true;
}

bool MatrixRead(int matrix[3][3], std::ifstream& inputFile)
{
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
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream inputFile;
	if (!FileOpened)
	{
		return 1;
	}

	int matrix[3][3];

	if (!MatrixRead(matrix, inputFile))
	{
		return 1;
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}