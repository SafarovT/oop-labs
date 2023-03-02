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

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString
)
{
	size_t pos = 0;
	//Уточнить есть ли инициализация по умолчанию
	std::string result = "";
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

void CopyFileWithReplacing(
	std::istream& input,
	std::ostream& output,
	const std::string& searchString,
	const std::string& replacementString
)
{
	std::string line = "";

	//3. if/else можно поменять с while. Это уберет лишнее дублирование кода
	while (std::getline(input, line))
	{
		if (!searchString.empty())
		{
			output << ReplaceString(line, searchString, replacementString) << "\n";

		}
		else
		{
			output << line << "\n";
		}
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

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return ProgramEndCode::Error;
	}

	//4. Попробуй разнести по функциям
	std::ifstream inputFile;
	std::ofstream outputFile;

	if (!OpenFiles(inputFile, outputFile, args->inputFilePath, args->outputFilePath))
	{
		return ProgramEndCode::Error;
	}

	std::string search = args->searchString;
	std::string replace = args->replacementString;

	CopyFileWithReplacing(inputFile, outputFile, search, replace);

	if (IsWorkWithFilesFailed(inputFile, outputFile))
	{
		return ProgramEndCode::Error;
	}

	return ProgramEndCode::Success;
}