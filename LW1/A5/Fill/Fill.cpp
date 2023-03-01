#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>
#include <vector>

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
const char symbolToFillWith = '—';

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
    std::fill(&canvas[0][0], &canvas[0][0] + sizeof(canvas), ' ');
    size_t i = 0;
    std::string readedLine;
    while (i < maxSizeY && std::getline(inputFile, readedLine))
    {
        size_t j = 0;
        while (j < maxSizeX && j < readedLine.length() && !(readedLine[j] == '\r' || readedLine[j] == '\n'))
        {
            canvas[i][j] = readedLine[j];
            j++;
            if (readedLine[j] == 'O')
            {
                seedsCoordinates.push_back({j, i});
            }
        }
        i++;
    }

    return canvas;
}

void FillLine(Canvas& canvas, size_t x1, size_t x2, size_t y)
{
    size_t xLeft, xRight;

    if (y > maxSizeY)
        return;

    for (xLeft = x1; xLeft <= maxSizeX && canvas[y][xLeft] == ' '; --xLeft)
    {
        canvas[y][xLeft] = symbolToFillWith;
    }
    if (xLeft < x1) {
        FillLine(canvas, xLeft, x1, y - 1); // fill child
        FillLine(canvas, xLeft, x1, y + 1); // fill child
        ++x1;
    }
    for (xRight = x2; xRight <= maxSizeX && canvas[y][xRight] == ' '; ++xRight)
    { // scan right
        canvas[y][xRight] = symbolToFillWith;
    }
    if (xRight > x2 && xRight <= maxSizeX) {
        std::cout << xRight;
        FillLine(canvas, x2, xRight, y - 1); // fill child
        FillLine(canvas, x2, xRight, y + 1); // fill child
        --x2;
    }
    for (xRight = x1; xRight <= x2 && xRight <= maxSizeX; ++xRight) {  // scan between
        if (canvas[y][xRight])
        {
            if (canvas[y][xRight] == ' ') canvas[y][xRight] = symbolToFillWith;
        }
        else
        {
            if (x1 < xRight) {
                // fill child  
                FillLine(canvas, x1, xRight - 1, y - 1);
                // fill child
                FillLine(canvas, x1, xRight - 1, y + 1);
                x1 = xRight;
            }
            // Note: This function still works if this step is removed.
            for (; xRight <= x2 && xRight <= maxSizeX; ++xRight) { // skip over border
                if (canvas[y][xRight] == ' ') {
                    x1 = xRight--;
                    break;
                }
            }
        }
    }
}

/*bool IsPushInStackPossible(std::stack<LineSegment>& stack, size_t y, size_t dy)
{
    return stack.size() < std::numeric_limits<std::deque<LineSegment>::size_type>::max() && y + dy <= maxSizeY;
}

void FillCanvasFromSeed(Canvas& canvas, size_t x, size_t y)
{
    size_t left, x1, x2;
    int dy;

    std::stack<LineSegment> stack;

    stack.push({ x, x, y, 1 });
    stack.push({ x, x, y + 1, -1 });


    while (!stack.empty()) {
        LineSegment line = stack.top();
        x1 = line.x1;
        x2 = line.x2;
        y = line.y;
        dy = line.dy;
        stack.pop();

        for (x = line.x1; canvas[y][x] = ' '; --x)
            canvas[y][x] = ' ';

        if (x >= x1)
            goto SKIP;

        left = x + 1;
        if (left < x1 && IsPushInStackPossible(stack, y, dy))
            PUSH(y, left, x1 - 1, -dy);

        x = x1 + 1;

        do {
            for (; x <= nMaxX && GetPixel(x, y) == old_color; ++x)
                SetPixel(x, y, new_color);

            PUSH(left, x - 1, y, dy);

            if (x > x2 + 1)
                PUSH(x2 + 1, x - 1, y, -dy);

        SKIP:        for (++x; x <= x2 && GetPixel(x, y) != old_color; ++x) { ; }

            left = x;
        } while (x <= x2);
    }
}*/


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
    FillLine(canvas, seedsCoordinates[0].x - 1, seedsCoordinates[0].x, seedsCoordinates[0].y);
    PrintCanvas(outputFile, canvas);

    if (IsWorkWithFilesFailed(inputFile, outputFile))
    {
        return ProgramEndCode::Error;
    }

    return ProgramEndCode::Success;
}