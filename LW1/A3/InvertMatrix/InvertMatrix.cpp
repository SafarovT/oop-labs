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
	
	return args;
}

bool ReadMatrix(std::istream& inputFile, double matrix[3][3])
{
	double readedValue;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (inputFile >> readedValue)
			{
				matrix[i][j] = readedValue;
			}
			else
			{
				std::cout << "Please, enter a correst matrix with numbers\n";
				return false;
			}
		}
	}
	return true;
}

bool OpenFile(std::ifstream& inputFile, std::string filePath)
{
	inputFile.open(filePath);

	if (!inputFile.is_open()) {
		std::cout << "Failed to open file for reading \n";

		return false;
	}

	return true;
}

double FoundDeterminant2By2Matrix(double matrix[2][2])
{
	return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}


double FoundDeterminant3By3Matrix(double matrix[3][3])
{
	double determinant = 0;

	for (int i = 0; i < 3; ++i)
	{
		double tempMatrix[2][2];
		for (int j = 1; j < 3; ++j)
		{
			for (int k = 0, x = 0; k < 3; ++k)
			{
				if (k != i)
				{
					tempMatrix[j - 1][x] = matrix[j][k];
					x++;
				}
			}
		}
		determinant += pow(-1, i) * matrix[0][i] * FoundDeterminant2By2Matrix(tempMatrix);
	}

	return determinant;
}

void InverMatrix(double matrix[3][3])
{
	double determinant = FoundDeterminant3By3Matrix(matrix);
	if (determinant == 0)
	{
		std::cout << "Impossible to invert matrix: determinant is equal to 0\n";

		return;
	}

}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream inputFile;

	if (!OpenFile(inputFile, args->inputFileName))
	{
		return 1;
	}

	double matrix[3][3];

	if (!ReadMatrix(inputFile, matrix))
	{
		return 1;
	}

	InverMatrix(matrix);
	
	return 0;
}