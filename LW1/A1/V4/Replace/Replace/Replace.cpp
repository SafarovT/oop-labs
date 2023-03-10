#include <iostream>
#include <fstream>
#include <string>
#include <optional>

enum ProgramEndCode
{
	Success = 0, Error = 1
};


struct Args
{
	std::string inputFilePath;
	std::string outputFilePath;
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
	 args.inputFilePath = argv[1];
	 args.outputFilePath = argv[2];
	 args.searchString = argv[3];
	 args.replacementString = argv[4];
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

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString
)
{
	size_t pos = 0;
	//Уточнить есть ли инициализация по умолчанию
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		//1. Протестировать ситуацию когда в строке 123123 меняется 123 на 123123
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

bool CopyFileWithReplacing(
	std::string& inputFilePath,
	std::string& outputFilePath,
	const std::string& searchString,
	const std::string& replacementString
)
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	if (!OpenFiles(inputFile, outputFile, inputFilePath, outputFilePath))
		return false;

	std::string line;

	//3. if/else можно поменять с while. Это уберет лишнее дублирование кода
	while (std::getline(inputFile, line))
	{
		if (!searchString.empty())
		{
			outputFile << ReplaceString(line, searchString, replacementString) << "\n";

		}
		else
		{
			outputFile << line << "\n";
		}
	}

	if (IsWorkWithFilesFailed(inputFile, outputFile))
		return false;

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
		return ProgramEndCode::Error;

	//4. Попробуй разнести по функциям

	std::string search = args->searchString;
	std::string replace = args->replacementString;

	if (!CopyFileWithReplacing(args->inputFilePath, args->outputFilePath, search, replace))
		return ProgramEndCode::Error;


	return ProgramEndCode::Success;
}