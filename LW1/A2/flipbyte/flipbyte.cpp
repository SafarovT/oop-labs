#include <iostream>
#include <optional>
#include <string>

struct Args
{
	unsigned char byte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	int byte = 0;
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <byte>\n";
		return std::nullopt;
	}
	try
	{
		byte = std::stoi(argv[1]);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << "Please, enter a number in [0, 255]";
		return std::nullopt;
	}
	catch (std::out_of_range& e)
	{
		std::cout << "Please, enter a number in [0, 255]";
		return std::nullopt;
	}
	if (!(byte >= 0 && byte <= 255))
	{
		std::cout << "Please, enter a number in [0, 255]";
		return std::nullopt;
	}
	Args args;
	args.byte = static_cast<unsigned char>(byte);
	return args;
}

unsigned char ReverseByte(unsigned char byte)
{
	int changingBit = 256;
	unsigned char result = 0;
	while (byte != 0)
	{
		result += (byte & 1) * (changingBit >>= 1);
		byte >>= 1;
	}
	return result;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	args->byte = ReverseByte(args->byte);
	std::cout << std::to_string(args->byte) << "\n";

	return 0;
}

//"$(ProjectDir)Tests.bat" "$(TargetPath)"