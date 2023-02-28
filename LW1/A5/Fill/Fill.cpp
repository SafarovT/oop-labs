#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>

enum ProgramEndCode
{
    Success = 0, Error = 1
};

const size_t maxSizeX = 100;
const size_t maxSizeY = 100;

using Canvas = std::array<std::array<char, maxSizeY>, maxSizeX>;

struct Args
{
    std::string inputFilePath;
    std::string outputFilePath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: fill.exe <inputFile.txt> <outputFile.txt>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFilePath = argv[1];
    args.outputFilePath = argv[2];

    return args;
}

bool OpenFiles(
    std::ifstream& inputFile,
    std::ofstream& outputFile,
    std::string& inputFilePath,
    std::string& outputFilePath
)
{
    inputFile.open(inputFilePath, std::ios::binary);
    outputFile.open(outputFilePath, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cout << "Failed to open file\n";
        return false;
    }

    return true;
}

bool IsWorkWithFilesFailed(std::ifstream& inputFile, std::ofstream& outputFile)
{
    if (inputFile.bad())
    {
        std::cout << "Failed to read data from input file \n";
        return true;
    }

    if (!outputFile.flush())
    {
        std::cout << "Failed to write data to output file \n";
        return true;
    }
    return false;
}

void PrintCanvas(std::ofstream& outputFile, Canvas& canvas)
{
    for (size_t i = 0; i < maxSizeY; ++i)
    {
        for (size_t j = 0; j < maxSizeY; ++j)
        {
            outputFile << canvas[i][j];
        }
        outputFile << std::endl;
    }
}

Canvas ReadCanvas(std::ifstream& inputFile)
{
    Canvas canvas;
    std::fill(&canvas[0][0], &canvas[0][0] + sizeof(canvas), ' ');

    return canvas;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return ProgramEndCode::Error;
    }

    std::ifstream inputFile;
    std::ofstream outputFile;

    if (!OpenFiles(inputFile, outputFile, args->inputFilePath, args->outputFilePath))
    {
        return ProgramEndCode::Error;
    }

    Canvas canvas = ReadCanvas(inputFile);
    PrintCanvas(outputFile, canvas);

    if (IsWorkWithFilesFailed(inputFile, outputFile))
    {
        return ProgramEndCode::Error;
    }

    return ProgramEndCode::Success;
}