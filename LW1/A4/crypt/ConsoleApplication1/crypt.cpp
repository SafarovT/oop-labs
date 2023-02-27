#include <fstream>
#include <iostream>
#include <optional>
#include <cmath>
#include <string>

enum WorkMode
{
    Crypt = 0, Decrypt = 1
};

enum ReturnCode
{
    Success = 0, Error = 1
};

struct Args
{
    WorkMode workMode;
    std::string inputFilePath;
    std::string outputFilePath;
    char key;
};

std::optional<char> ReadByte(std::string numberText)
{
    int byte = 0;
    std::string errorMessage = "Please, enter a key in [0, 255]";
    try
    {
        byte = std::stoi(numberText);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << errorMessage;
        return std::nullopt;
    }
    catch (std::out_of_range& e)
    {
        std::cout << errorMessage;
        return std::nullopt;
    }
    if (!(byte >= -127 && byte <= 127))
    {
        std::cout << errorMessage;
        return std::nullopt;
    }
    return static_cast<char>(byte);
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: crypt.exe <crypt | decrypt> <inputFile> <outputFile> <key>\n";
        return std::nullopt;
    }
    Args args;
    std::string enteredMode = argv[1];
    if (enteredMode == "crypt")
    {
        args.workMode = WorkMode::Crypt;
    }
    else if (enteredMode == "decrypt")
    {
        args.workMode = WorkMode::Decrypt;
    }
    else {
        std::cout << "Please select one of defined modes: crypt or decrypt\n"
            << "There is no mode line '" << argv[1] << "'";
        return std::nullopt;
    }
    args.inputFilePath = argv[2];
    args.outputFilePath = argv[3];
    auto readedByte = ReadByte(argv[4]);
    if (!readedByte)
    {
        return std::nullopt;
    }
    else
    {
        args.key = *readedByte;
        return args;
    }
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

void shuffleBitsBack(char& byte)
{
    char resultedByte = 0;
    resultedByte |= (byte & 0b00000001) << 5;
    resultedByte |= (byte & 0b00000010) << 5;
    resultedByte |= (byte & 0b00000100) >> 2;
    resultedByte |= (byte & 0b00001000) >> 2;
    resultedByte |= (byte & 0b00010000) >> 2;
    resultedByte |= (byte & 0b00100000) << 2;
    resultedByte |= (byte & 0b01000000) >> 3;
    resultedByte |= (byte & 0b10000000) >> 3;
    byte = resultedByte;
}

void shuffleBits(char& byte)
{
    char resultedByte = 0;
    // int i = 0;
    // static_cast<char>(pow(2, i++))
    resultedByte |= (byte & 0b00000001) << 2;
    resultedByte |= (byte & 0b00000010) << 2;
    resultedByte |= (byte & 0b00000100) << 2;
    resultedByte |= (byte & 0b00001000) << 3;
    resultedByte |= (byte & 0b00010000) << 3;
    resultedByte |= (byte & 0b00100000) >> 5;
    resultedByte |= (byte & 0b01000000) >> 5;
    resultedByte |= (byte & 0b10000000) >> 2;
    byte = resultedByte;
}

void CopyFileCrypted(std::ifstream& inputFile, std::ofstream& outputFile, char key)
{
    char readedByte;
    while (inputFile.get(readedByte))
    {
        readedByte ^= key;
        shuffleBits(readedByte);
        outputFile << readedByte;
    }
}

void CopyFileDecrypted(std::ifstream& inputFile, std::ofstream& outputFile, char key)
{
    char readedByte;
    while (inputFile.get(readedByte))
    {
        shuffleBitsBack(readedByte);
        readedByte ^= key; 
        outputFile << readedByte;
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return ReturnCode::Error;
    }

    std::ifstream inputFile;
    std::ofstream outputFile;

    if (!OpenFiles(inputFile, outputFile, args->inputFilePath, args->outputFilePath))
    {
        return ReturnCode::Error;
    }

    switch (args->workMode)
    {
    case WorkMode::Crypt:
    {
        CopyFileCrypted(inputFile, outputFile, args->key);

        break;
    }
    case WorkMode::Decrypt:
    {
        CopyFileDecrypted(inputFile, outputFile, args->key);
    }
    }

    char ch = 0b01011010;
    std::cout << ch;

    if (IsWorkWithFilesFailed(inputFile, outputFile))
    {
        return ReturnCode::Error;
    }

    return ReturnCode::Success;
}