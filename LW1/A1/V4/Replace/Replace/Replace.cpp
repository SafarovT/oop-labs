// Replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

 std::optional<Args> ParseArgs(int argc, char* argv[])
{
	 if (argc != 5)
	 {
		 std::cout << "Invalid argument count\n"
			 << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		 return std::nullopt;
	 }
	 Args args;
	 args.inputFileName = argv[1];
	 args.outputFileName = argv[2];
	 args.searchString = argv[3];
	 args.replacementString = argv[4];
	 return args;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	//???????? ???? ?? ????????????? ?? ?????????
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		//1. ????? ??????????? replace
		//2. ?????????????? ???????? ????? ? ?????? 123123 ???????? 123 ?? 123123
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	if (!searchString.empty())
	{
		//3. if/else ????? ???????? ? while. ??? ?????? ?????? ???????????? ????
		while (std::getline(input, line))
		{
			output << ReplaceString(line, searchString, replacementString) << "\n";
		}
	}
	else
	{
		while (std::getline(input, line))
		{
			output << line << "\n";
		}
	}
}

bool IsFileOpeningFailed(std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file for reading \n";
		return true;
	}
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open file for writing \n";
		return true;
	}
	return false;
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

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	//4. ???????? ???????? ?? ????????
	std::ifstream inputFile;
	inputFile.open(args->inputFileName);

	std::ofstream outputFile;
	outputFile.open(args->outputFileName);

	if (IsFileOpeningFailed(inputFile, outputFile))
	{
		return 1;
	}

	std::string search = args->searchString;
	std::string replace = args->replacementString;

	CopyFileWithReplace(inputFile, outputFile, search, replace);
	if (IsWorkWithFilesFailed(inputFile, outputFile))
	{
		return 1;
	}

	return 0;
}