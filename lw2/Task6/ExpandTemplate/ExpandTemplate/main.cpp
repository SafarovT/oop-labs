#include "ExpandTemplate.h"
#include <iostream>
#include <optional>
#include <fstream>

struct Args
{
    std::string inputFilePath;
    std::string outputFilePath;
    TemplateParams params;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: expand_template.exe <inputFile.txt> <outputFile.txt> [<param> <value> [<param> <value> …]]\n";
        return std::nullopt;
    }
    Args args;
    args.inputFilePath = argv[1];
    args.outputFilePath = argv[2];
    TemplateParams params;
    for (size_t i = 3; i <= argc - 2; i += 2)
    {
        params.emplace(argv[i], argv[i + 1]);
    }
    args.params = params;

    return args;
}

void CopyAndExpandWithParams(std::istream& input, std::ostream& output, TemplateParams const& params)
{
    std::string readLine;
    while (std::getline(input, readLine))
    {
        output << ExpandTemplate(readLine, params);
    }
}

bool CopyAndExpandWithParams(std::string& inputFilePath, std::string& outputFilePath, TemplateParams const& params)
{
    std::ifstream input;
    std::ofstream output;
    input.open(inputFilePath);
    output.open(outputFilePath);
    if (!input.is_open() || !output.is_open())
    {
        std::cout << "Failed to open files" << std::endl;
        return false;
    }

    CopyAndExpandWithParams(input, output, params);

    if (input.bad() || !output.flush())
    {
        std::cout << "Failed to work with files" << std::endl;
        return false;
    }

    return true;
}


int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    if (!CopyAndExpandWithParams(args->inputFilePath, args->outputFilePath, args->params))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}