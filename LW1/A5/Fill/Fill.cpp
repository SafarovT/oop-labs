#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <stack>

enum ProgramEndCode
{
    Success = 0, Error = 1
};

struct Coordinates
{
    size_t x;
    size_t y;
};

const size_t maxSizeX = 100;
const size_t maxSizeY = 100;
const char symbolToReplaceByFill = ' ';
const char symbolToFillWith = '—';
const char seedSymbol = 'O';

using Canvas = std::array<std::array<char, maxSizeY>, maxSizeX>;
using CoordinatesVector = std::vector<Coordinates>;

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

Canvas ReadCanvasForFilling(std::ifstream& inputFile, CoordinatesVector& seedsCoordinates)
{
    Canvas canvas;
    std::fill(&canvas[0][0], &canvas[0][0] + sizeof(canvas), symbolToReplaceByFill);
    size_t i = 0;
    std::string readedLine;
    while (i < maxSizeY && std::getline(inputFile, readedLine))
    {
        size_t j = 0;
        while (j < maxSizeX && j < readedLine.length() && !(readedLine[j] == '\r' || readedLine[j] == '\n' || readedLine[j] == '\r\n'))
        {
            canvas[i][j] = readedLine[j];
            if (readedLine[j] == seedSymbol)
            {
                seedsCoordinates.push_back({ j, i });
            }
            j++;
        }
        i++;
    }

    return canvas;
}

void FillFigure(Canvas& canvas, size_t startX, size_t startY)
{
    canvas[startY][startX] = symbolToReplaceByFill;
    std::stack<Coordinates> stack;
    stack.push({startX, startY});
    while (!stack.empty() && stack.size() != std::numeric_limits<std::deque<Coordinates>::size_type>::max())
    {
        Coordinates point = stack.top();
        stack.pop();
        size_t y1 = point.y;

        while (y1 < maxSizeX && canvas[y1][point.x] == symbolToReplaceByFill) y1--;
        y1++;

        size_t spanLeft = 0; size_t spanRight = 0;
        while (y1 < maxSizeY && canvas[y1][point.x] == symbolToReplaceByFill)
        {
            canvas[y1][point.x] = symbolToFillWith;
            if (spanLeft == 0 && point.x - 1 < maxSizeX && canvas[y1][point.x - 1] == symbolToReplaceByFill)
            {
                stack.push({point.x - 1, y1});
                spanLeft = 1;
            }
            else if (spanLeft == 1 && point.x - 1 < maxSizeX && canvas[y1][point.x - 1] != symbolToReplaceByFill)
            {
                spanLeft = 0;
            }

            if (spanRight == 0 && point.x + 1 < maxSizeX && canvas[y1][point.x + 1] == symbolToReplaceByFill)
            {
                stack.push({ point.x + 1, y1 });
                spanRight = 1;
            }
            else if (spanRight == 1 && point.x + 1 < maxSizeX && canvas[y1][point.x + 1] != symbolToReplaceByFill)
            {
                spanRight = 0;
            }

            y1++;
        }
    }
    canvas[startY][startX] = seedSymbol;
}

void FillAllSeeds(Canvas& canvas, const CoordinatesVector& seeds)
{
    for (Coordinates seedCoordinates : seeds)
        FillFigure(canvas, seedCoordinates.x, seedCoordinates.y);
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

    CoordinatesVector seedsCoordinates;
    Canvas canvas = ReadCanvasForFilling(inputFile, seedsCoordinates);
    FillAllSeeds(canvas, seedsCoordinates);
    PrintCanvas(outputFile, canvas);

    if (IsWorkWithFilesFailed(inputFile, outputFile))
    {
        return ProgramEndCode::Error;
    }

    return ProgramEndCode::Success;
}