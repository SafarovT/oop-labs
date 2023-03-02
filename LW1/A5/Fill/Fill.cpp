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
const char endOfLineSymbols[3] = { '\n', '\r', '\r\n' };

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

void ReadCanvasAndSeeds(std::ifstream& inputFile, Canvas& canvas, CoordinatesVector& seedsCoordinates)
{
    std::fill(&canvas[0][0], &canvas[0][0] + sizeof(canvas), symbolToReplaceByFill);
    size_t y = 0; // TODO Заменить i j на x y
    std::string readedLine;

    auto IsEOLN = [](char symbol)
    {
        return !std::count(std::begin(endOfLineSymbols), std::end(endOfLineSymbols), symbol);
    };

    while (y < maxSizeY && std::getline(inputFile, readedLine))
    {
        size_t x = 0;
        while (x < maxSizeX && x < readedLine.length() && IsEOLN(readedLine[x]))
            // TODO Сделать функцию, которая будет возвращать bool если символ EOLN (лямбда функция предпочтительнее)
        {
            canvas[y][x] = readedLine[x];
            if (readedLine[x] == seedSymbol)
            {
                seedsCoordinates.push_back({ x, y });
            }
            x++;
        }
        y++;
    }
}

void FillFigure(Canvas& canvas, const Coordinates& startCoordinates) // TODO  Coordinates
{
    canvas[startCoordinates.y][startCoordinates.x] = symbolToReplaceByFill;
    std::stack<Coordinates> stack;
    stack.push({startCoordinates.x, startCoordinates.y});
    while (!stack.empty() && stack.size() != std::numeric_limits<std::deque<Coordinates>::size_type>::max())
    {
        Coordinates point = stack.top();
        stack.pop();
        size_t y = point.y; // TODO replace with y

        while (y < maxSizeY && canvas[y][point.x] == symbolToReplaceByFill) y--;
        y++;

        bool spanLeft = false, spanRight = false; // TODO bool
        while (y < maxSizeY && canvas[y][point.x] == symbolToReplaceByFill)
        {
            canvas[y][point.x] = symbolToFillWith;
            if (!spanLeft && point.x - 1 < maxSizeX && canvas[y][point.x - 1] == symbolToReplaceByFill)
            {
                stack.push({point.x - 1, y});
                spanLeft = true;
            }
            else if (spanLeft && point.x - 1 < maxSizeX && canvas[y][point.x - 1] != symbolToReplaceByFill)
            {
                spanLeft = false;
            }

            if (!spanRight && point.x + 1 < maxSizeX && canvas[y][point.x + 1] == symbolToReplaceByFill)
            {
                stack.push({ point.x + 1, y });
                spanRight = true;
            }
            else if (spanRight && point.x + 1 < maxSizeX && canvas[y][point.x + 1] != symbolToReplaceByFill)
            {
                spanRight = false;
            }

            y++;
        }
    }
    canvas[startCoordinates.y][startCoordinates.x] = seedSymbol;
}

void FillAllSeeds(Canvas& canvas, const CoordinatesVector& seeds)
{
    for (Coordinates seedCoordinates : seeds)
        FillFigure(canvas, seedCoordinates);
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
    Canvas canvas;
    ReadCanvasAndSeeds(inputFile, canvas, seedsCoordinates); // TODO Оба по ссылке
    FillAllSeeds(canvas, seedsCoordinates);
    PrintCanvas(outputFile, canvas);

    if (IsWorkWithFilesFailed(inputFile, outputFile))
    {
        return ProgramEndCode::Error;
    }

    return ProgramEndCode::Success;
}