#include <iostream>
#include <optional>
#include <string>

enum class WorkMode
{
    Crypt, Decrypt
};

struct Args
{
    WorkMode workMode;
    std::string inputFilePath;
    std::string outputFilePath;
    unsigned char byte;
};

std::optional<Args> ParseArgs(int argc, char* [])
{
    if (argc != 5)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: crypt.exe <crypt | decrypt> <inputFile> <outputFile> <key>\n";
        return std::nullopt;
    }
    Args args;
    switch 
}

int main()
{
    
}