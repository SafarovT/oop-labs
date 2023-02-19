#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <array>

enum ProgramEndCode
{
	Success = 0, Error
};

using Mat3x3 = std::array<std::array<double, 3>, 3>;

std::optional<std::string> ParseArgs(int argc, char* argv[]) // TODO: replace args with string
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <MatrixFile.txt>\n";
		return std::nullopt;
	}
	
	return argv[1];
}

std::optional<Mat3x3> ReadMatrix(std::istream& inputFile)
{
	Mat3x3 resultMatrix;
	double readedValue;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (inputFile >> readedValue)
			{
				resultMatrix[i][j] = readedValue;
			}
			else
			{
				std::cout << "Please, enter a correst matrix with numbers\n";
				return std::nullopt;
			}
		}
	}
	return resultMatrix;
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

void WriteMatrix(Mat3x3 matrix)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			double numberToPrint = round(matrix[i][j] * 1000) / 1000;
			std::cout << numberToPrint << " ";
		}
		std::cout << std::endl;
	}
}

double GetDeterminant2By2Matrix(Mat3x3 matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

double GetDeterminantOfRemainderMatrix(Mat3x3 matrix, int x, int y)
{
	Mat3x3 remainderMatrix;
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

double GetDeterminant3By3Matrix(Mat3x3 matrix)
{
	double determinant = 0;

	for (int i = 0; i < 3; ++i)
	{
		determinant += pow(-1, i) * matrix[0][i] * GetDeterminantOfRemainderMatrix(matrix, i, 0);
	}

	return determinant;
}

Mat3x3 FindTranspose(Mat3x3 matrix)
{
	Mat3x3 resultMatrix;
	for (int i = 0, y = 0; i < 3; ++i)
	{
		for (int j = 0, x = 0; j < 3; ++j)
		{
			resultMatrix[j][i] = pow(-1, i + j) * GetDeterminantOfRemainderMatrix(matrix, j, i);
		}
	}

	return resultMatrix;
}

void MultMatrixOnNumber(Mat3x3 &matrix, double multiplier)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matrix[i][j] *= multiplier;
		}
	}
}

bool InvertMatrix(Mat3x3 &matrix) // TODO: если мы  назваем ф-ю invert, это не значит, что она будет печатать эту матрицу
{
	double determinant = GetDeterminant3By3Matrix(matrix);
	if (determinant == 0)
	{
		std::cout << "Impossible to invert matrix: determinant is equal to 0\n";

		return false;
	}

	matrix = FindTranspose(matrix);
	MultMatrixOnNumber(matrix, 1/determinant);

	return true;
}

int main(int argc, char* argv[])
{
	auto inputFilePath = ParseArgs(argc, argv);
	if (!inputFilePath)
	{
		return ProgramEndCode::Error; // use constant
	}

	std::ifstream inputFile;

	if (!OpenFile(inputFile, *inputFilePath))
	{
		return ProgramEndCode::Error;
	}

	auto matrix = ReadMatrix(inputFile);

	if (!matrix)
	{
		return ProgramEndCode::Error;
	}

	if (InvertMatrix(*matrix)) {
		WriteMatrix(*matrix);
	}

	
	return ProgramEndCode::Success;
}

// TODO use std::array