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

struct Point // TODO: point
{
    unsigned int x;
    unsigned int y;
};

const unsigned int MAX_SIZE_X = 100;
const unsigned int MAX_SIZE_Y = 100;
const char SYMBOL_TO_REPLACY_BY_FILL = ' ';
const char SYMBOL_TO_FILL_WITH = '�';
const char SEED_SYMBOL = 'O';
const char END_OF_LINE_SYMBOLS[2] = {'\n', '\r'};

using Canvas = std::array<std::array<char, MAX_SIZE_X>, MAX_SIZE_Y>;
using CoordinatesVector = std::vector<Point>;
using CoordinatesStack = std::stack<Point>;

struct Args
{
    std::string inputFilePath;
    std::string outputFilePath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        // ���������� std::endl
        std::cout << "Invalid argument count" << std::endl
            << "Usage: fill.exe <inputFile.txt> <outputFile.txt>" << std::endl;
        return std::nullopt;
    }
    Args args;
    args.inputFilePath = argv[1];
    args.outputFilePath = argv[2];

    return args;
}

void PrintCanvasInFile(std::ofstream& outputFile, Canvas const& canvas)
{
    for (int i = 0; i < MAX_SIZE_Y; ++i)
    {
        for (int j = 0; j < MAX_SIZE_Y; ++j)
        {
            // �������� � ��������/��������� �������� istream � ostream
            outputFile << canvas[i][j];
        }
        outputFile << std::endl;
    }
}

bool PrintCanvasInFile(std::string const& outputFilePath, Canvas const& canvas)
{
    std::ofstream outputFile;
    outputFile.open(outputFilePath, std::ios::binary);
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open file " << outputFilePath << std::endl;

        return false;
    }

    PrintCanvasInFile(outputFile, canvas);

    if (!outputFile.flush())
    {
        std::cout << "Failed to write data to file " << outputFilePath << std::endl;
        return false;
    }

    return true;
}

void ReadCanvasAndSeedsFromFile(std::ifstream& inputFile, Canvas& canvas, CoordinatesVector& seedsCoordinates)
{
    // ��� ���� ����� ������� �� ������ istream/ostream
    std::fill(&canvas[0][0], &canvas[0][0] + sizeof(canvas), SYMBOL_TO_REPLACY_BY_FILL);
    unsigned int y = 0;
    std::string readedLine;

    auto IsEOLN = [](char symbol)
    {
        return !std::count(std::begin(END_OF_LINE_SYMBOLS), std::end(END_OF_LINE_SYMBOLS), symbol);
    };

    while (y < MAX_SIZE_Y && std::getline(inputFile, readedLine))
    {
        unsigned int x = 0;
        while (x < MAX_SIZE_X && x < readedLine.length() && IsEOLN(readedLine[x]))
            // TODO ������� �������, ������� ����� ���������� bool ���� ������ EOLN (������ ������� ����������������)
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
}

bool ReadCanvasAndSeedsFromFile(std::string const& inputFilePath, Canvas& canvas, CoordinatesVector& seedsCoordinates)
{
    std::ifstream inputFile;
    inputFile.open(inputFilePath, std::ios::binary);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open file " << inputFilePath << std::endl;

        return false;
    }

    ReadCanvasAndSeedsFromFile(inputFile, canvas, seedsCoordinates);

    if (inputFile.bad())
    {
        std::cout << "Failed to read data from file " << inputFilePath << std::endl;
        return false;
    }

    return true;
}

bool IsFillingLineEndUnreached(Point point, Canvas const& canvas)
{
    return (point.y < MAX_SIZE_Y && canvas[point.y][point.x] == SYMBOL_TO_REPLACY_BY_FILL);
}

// const&
// remove stack from this function
// sideSpan -> enum?
bool ShouldFillLine(bool& checkSide, Point const& pointOnLine, Canvas const& canvas)
{
    //����� ������� ������� ����� ������� � ���������� � ��������� ����������
    auto IsLineUnfilled = [](Point point, Canvas const& canvas)
    {
        return canvas[point.y][point.x] == SYMBOL_TO_REPLACY_BY_FILL;
    };

    if (!checkSide &&  pointOnLine.x < MAX_SIZE_X && IsLineUnfilled(pointOnLine, canvas))
    {
        checkSide = true;

        return true;
    }
    else if (checkSide && pointOnLine.x < MAX_SIZE_X && !IsLineUnfilled(pointOnLine, canvas))
    {
        checkSide = false;

        return false;
    }

    return false;
}

//TODO: ������������ ������� � ������ �����
int GetEndOfLineCoordinate(Point currentPoint, Canvas const& canvas)
{
    while (IsFillingLineEndUnreached(currentPoint, canvas))
    {
        currentPoint.y--;
    }

    return currentPoint.y + 1;
}

// ����������� ��������� ���
// TODO edit name (floodFill)
void FloodFill(Canvas& canvas, Point const& startCoordinates) // TODO  Coordinates
{
    //tOOD: coordinates->points
    CoordinatesStack coordinatesToFill;
    coordinatesToFill.push({startCoordinates.x, startCoordinates.y});
    
    // ��������� �������
    while (!coordinatesToFill.empty() && coordinatesToFill.size() != SIZE_MAX)
    {
        const unsigned int x = coordinatesToFill.top().x;
        unsigned int y = coordinatesToFill.top().y; // TODO replace with y
        coordinatesToFill.pop();

        y = GetEndOfLineCoordinate({x, y}, canvas);
       
        bool checkLeft = false;
        bool checkRight = false;

        // TODO bool
        // addComent or change names | lambda
        // ��������� �������, ����� ���� ����� 
        while (IsFillingLineEndUnreached({x, y}, canvas) && coordinatesToFill.size() != SIZE_MAX)
        {
            canvas[y][x] = SYMBOL_TO_FILL_WITH;

            Point pointOnLeftSide = { x - 1, y };
            if (ShouldFillLine(checkLeft, pointOnLeftSide, canvas))
            {
                coordinatesToFill.push(pointOnLeftSide);
            }

            Point pointOnRightSide = { x + 1, y };
            if (ShouldFillLine(checkRight, pointOnRightSide, canvas))
            {
                coordinatesToFill.push(pointOnRightSide);
            }

            y++;
        }
    }
}

void FloodFillWrapper(Canvas& canvas, Point const& startCoordinates)
{
    canvas[startCoordinates.y][startCoordinates.x] = SYMBOL_TO_REPLACY_BY_FILL;
    FloodFill(canvas, startCoordinates);
    canvas[startCoordinates.y][startCoordinates.x] = SEED_SYMBOL;
}

// TODO add from
void FloodFillFromEachSeed(Canvas& canvas, CoordinatesVector const& seeds)
{
    for (Point seedCoordinates : seeds)
    {
        FloodFillWrapper(canvas, seedCoordinates);
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return ProgramEndCode::Error;
    }

    //TODO ������ ����� � ������ � �������� ���������� ��� �����

    CoordinatesVector seedsCoordinates;
    Canvas canvas;
    if (!ReadCanvasAndSeedsFromFile(args->inputFilePath, canvas, seedsCoordinates))
    {
        return ProgramEndCode::Error;
    }

    // TODO ��� �� ������
    FloodFillFromEachSeed(canvas, seedsCoordinates);
    if (!PrintCanvasInFile(args->outputFilePath, canvas))
    {
        return ProgramEndCode::Error;
    }

    return ProgramEndCode::Success;
}