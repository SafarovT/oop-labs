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
    unsigned int x; // TODO use int
    unsigned int y;
};

const unsigned int MAX_SIZE_X = 100;
const unsigned int MAX_SIZE_Y = 100;
const char SYMBOL_TO_REPLACY_BY_FILL = ' '; // UPPER_SNAKE_CASE
const char SYMBOL_TO_FILL_WITH = '—';
const char SEED_SYMBOL = 'O';
const char END_OF_LINE_SYMBOLS[3] = { '\n', '\r', '\r\n' };

// Перепутанно (проверить с неквадратным соотношением сторон)
using Canvas = std::array<std::array<char, MAX_SIZE_X>, MAX_SIZE_Y>;
using CoordinatesVector = std::vector<Coordinates>;
using CoordinatesStack = std::stack<Coordinates>;

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

bool PrintCanvasToFile(std::string& outputFilePath, Canvas& canvas)
{
    std::ofstream outputFile;
    outputFile.open(outputFilePath, std::ios::binary);
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open file\n";

        return false;
    }

    for (int i = 0; i < MAX_SIZE_Y; ++i)
    {
        for (int j = 0; j < MAX_SIZE_Y; ++j)
        {
            outputFile << canvas[i][j];
        }
        outputFile << std::endl;
    }

    if (!outputFile.flush())
    {
        std::cout << "Failed to write data to output file \n";
        return false;
    }

    return true;
}

bool ReadCanvasAndSeedsFromFile(std::string& inputFilePath, Canvas& canvas, CoordinatesVector& seedsCoordinates)
{
    std::ifstream inputFile;
    inputFile.open(inputFilePath, std::ios::binary);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open file\n";

        return false;
    }

    std::fill(&canvas[0][0], &canvas[0][0] + sizeof(canvas), SYMBOL_TO_REPLACY_BY_FILL);
    unsigned int y = 0; // TODO Заменить i j на x y
    std::string readedLine;

    auto IsEOLN = [](char symbol)
    {
        return !std::count(std::begin(END_OF_LINE_SYMBOLS), std::end(END_OF_LINE_SYMBOLS), symbol);
    };

    while (y < MAX_SIZE_Y && std::getline(inputFile, readedLine))
    {
        unsigned int x = 0;
        while (x < MAX_SIZE_X && x < readedLine.length() && IsEOLN(readedLine[x]))
            // TODO Сделать функцию, которая будет возвращать bool если символ EOLN (лямбда функция предпочтительнее)
        {
            canvas[y][x] = readedLine[x];
            if (readedLine[x] == SEED_SYMBOL)
            {
                seedsCoordinates.push_back({ x, y });
            }
            x++;
        }
        y++;
    }

    if (inputFile.bad())
    {
        std::cout << "Failed to read data from input file \n";
        return false;
    }

    return true;
}

// const&
// remove stack from this function
// sideSpan -> enum?
bool ShouldFieldLine(bool& checkSide, Coordinates const& pointOnLine, Canvas const& canvas)
{
    if (!checkSide && pointOnLine.x < MAX_SIZE_X && canvas[pointOnLine.y][pointOnLine.x] == SYMBOL_TO_REPLACY_BY_FILL)
    {
        checkSide = true;

        return true;
    }
    else if (checkSide && pointOnLine.x < MAX_SIZE_X && canvas[pointOnLine.y][pointOnLine.x] != SYMBOL_TO_REPLACY_BY_FILL)
    {
        checkSide = false;

        return false;
    }

    return false;
}

// попробовать упростить код
// TODO edit name (floodFill)
void FloodFill(Canvas& canvas, Coordinates const& startCoordinates) // TODO  Coordinates
{
    canvas[startCoordinates.y][startCoordinates.x] = SYMBOL_TO_REPLACY_BY_FILL;
    CoordinatesStack stack;
    stack.push({startCoordinates.x, startCoordinates.y});
    
    // Упростить условие
    while (!stack.empty() && stack.size() != SIZE_MAX)
    {
        const unsigned int x = stack.top().x;
        unsigned int y = stack.top().y; // TODO replace with y
        stack.pop();

        // Add {}
        while (y < MAX_SIZE_Y && canvas[y][x] == SYMBOL_TO_REPLACY_BY_FILL)
        {
            y--;
        }

        y++;
        // checking side
        bool checkLeft = false, checkRight = false; // TODO bool
        // addComent or change names | lambda
        while (y < MAX_SIZE_Y && canvas[y][x] == SYMBOL_TO_REPLACY_BY_FILL && stack.size() != SIZE_MAX)
        {
            canvas[y][x] = SYMBOL_TO_FILL_WITH;

            Coordinates pointOnLeftSide = { x - 1, y };
            if (ShouldFieldLine(checkLeft, pointOnLeftSide, canvas))
            {
                stack.push(pointOnLeftSide);
            }

            Coordinates pointOnRightSide = { x + 1, y };
            if (ShouldFieldLine(checkRight, pointOnRightSide, canvas))
            {
                stack.push(pointOnRightSide);
            }

            y++;
        }
    }
    canvas[startCoordinates.y][startCoordinates.x] = SEED_SYMBOL;
}

// TODO add from
void FloodFillFromEachSeed(Canvas& canvas, CoordinatesVector const& seeds)
{
    for (Coordinates seedCoordinates : seeds)
    {
        FloodFill(canvas, seedCoordinates);
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return ProgramEndCode::Error;
    }

    //TODO Чтение файла и запись в функциях принмающих имя файла

    CoordinatesVector seedsCoordinates;
    Canvas canvas;
    if (!ReadCanvasAndSeedsFromFile(args->inputFilePath, canvas, seedsCoordinates))
    {
        return ProgramEndCode::Error;
    }

    // TODO Оба по ссылке
    FloodFillFromEachSeed(canvas, seedsCoordinates);
    if (!PrintCanvasToFile(args->outputFilePath, canvas))
    {
        return ProgramEndCode::Error;
    }

    return ProgramEndCode::Success;
}