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

void WriteMatrix(double matrix[3][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << round(matrix[i][j] * 1000) / 1000 << " ";
		}
		std::cout << std::endl;
	}
}

double GetDeterminant2By2Matrix(double matrix[2][2])
{
	return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

double GetDeterminantOfRemainderMatrix(double matrix[3][3], int x, int y)
{
	double remainderMatrix[2][2];
	for (int i = 0, iRemainderMatrix = 0; i < 3; ++i)
	{
		if (i != y)
		{
			for (int j = 0, jRemainderMatrix = 0; j < 3; ++j)
			{
				if (j != x)
				{
					remainderMatrix[iRemainderMatrix][jRemainderMatrix] = matrix[i][j];
					jRemainderMatrix++;
				}
			}
			iRemainderMatrix++;
		}
	}

	return GetDeterminant2By2Matrix(remainderMatrix);
}

double GetDeterminant3By3Matrix(double matrix[3][3])
{
	double determinant = 0;

	for (int i = 0; i < 3; ++i)
	{
		determinant += pow(-1, i) * matrix[0][i] * GetDeterminantOfRemainderMatrix(matrix, i, 0);
	}

	return determinant;
}

void FindTranspose(double matrix[3][3], double resultMatrix[3][3])
{
	for (int i = 0, y = 0; i < 3; ++i)
	{
		for (int j = 0, x = 0; j < 3; ++j)
		{
			resultMatrix[j][i] = pow(-1, i + j) * GetDeterminantOfRemainderMatrix(matrix, j, i);
		}
	}
}

void MultMatrixOnNumber(double matrix[3][3], double multiplier)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matrix[i][j] *= multiplier;
		}
	}
}

void InvertMatrix(double matrix[3][3])
{
	double determinant = GetDeterminant3By3Matrix(matrix);
	if (determinant == 0)
	{
		std::cout << "Impossible to invert matrix: determinant is equal to 0\n";

		return;
	}

	double transpose[3][3];
	FindTranspose(matrix, transpose);
	MultMatrixOnNumber(transpose, 1/determinant);
	WriteMatrix(transpose);


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

	InvertMatrix(matrix);
	
	return 0;
}