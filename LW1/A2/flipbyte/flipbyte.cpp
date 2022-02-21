#include <iostream>
#include <optional>
#include <string>

struct Args
{
	unsigned char byte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	int result = 0;
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <byte>\n";
		return std::nullopt;
	}
	while (*argv[1])
	{
		if (*argv[1] >= '0' && *argv[1] <= '9')
		{
			result += *argv[1]++ - '0';
			if (*argv[1])
			{
				result *= 10;
			}
			if (result > 255)
			{
				std::cout << "Please, enter a value in [0, 255]";	
				return std::nullopt;
			}
		}
		else
		{
			std::cout << "Please, enter a value in [0, 255]";
			return std::nullopt;
		}
	}
	Args args;
	args.byte = static_cast<unsigned char>(result);
	return args;
}

unsigned char ReverseByte(unsigned char byte)
{
	int base = 256;
	unsigned char res = 0;
	while (byte != 0)
	{
		res += (byte & 1) * (base >>= 1);
		byte >>= 1;
	}
	return res;
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