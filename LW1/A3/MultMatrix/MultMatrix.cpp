#include <iostream>
#include <optional>
#include <fstream>
#include <math.h>

struct Args
{
    std::string inputMatrixFile1;
    std::string inputMatrixFile2;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n "
            << "Usage: multmatrix.exe <M<atrixFile1> <MatrixFile2>\n";
        return std::nullopt;
    };
    Args args;
    args.inputMatrixFile1 = argv[1];
    args.inputMatrixFile2 = argv[2];
    return args;
}

bool IsFileOpeningFailed(std::ifstream& file1, std::ifstream& file2)
{
    if (!file1.is_open())
    {
        std::cout << "Failed to open file for reading \n";
        return true;
    }
    if (!file2.is_open())
    {
        std::cout << "Failed to open file for writing \n";
        return true;
    }
    return false;
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

void GetMultedMatrix(double matrix1[3][3], double matrix2[3][3], double multedMatrix[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            multedMatrix[i][j] = (matrix1[i][0] * matrix2[0][j])
                + (matrix1[i][1] * matrix2[1][j])
                + (matrix1[i][2] * matrix2[2][j]);
        }
    }
}

void WriteMatrix(double matrix[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << floor(matrix[i][j] * 1000) / 1000 << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::ifstream inputFile1;
    std::ifstream inputFile2;

    inputFile1.open(args->inputMatrixFile1);
    inputFile2.open(args->inputMatrixFile2);

    if (IsFileOpeningFailed(inputFile1, inputFile2))
    {
        return 1;
    }

    double matrix1[3][3], matrix2[3][3];

    if (!(ReadMatrix(inputFile1, matrix1) && ReadMatrix(inputFile2, matrix2)))
    {
        return 1;
    }

    double multedMatrix[3][3];
    GetMultedMatrix(matrix1, matrix2, multedMatrix);

    WriteMatrix(multedMatrix);
    return 0;
}
