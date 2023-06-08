#include "Radix.h"
#include <iostream>
#include <optional>

namespace
{
    using namespace std;
    struct Args
    {
        int sourceRadix = 10;
        int resultRadix = 10;
        string number;
    };
    const string ERROR_RADIX_MESSAGE = "Radix needs to be a number";

    optional<int> ReadInt(string const& str)
    {
        int number;
        try
        {
            number = stoi(str);
        }
        catch (invalid_argument& e)
        {
            return nullopt;
        }
        catch (out_of_range& e)
        {
            return nullopt;
        }
        return number;
    }

    optional<Args> ParseArgs(int argc, char* argv[])
    {
        if (argc != 4)
        {
            cout << "Error params, usage: <source radix> <result radix> <number>" << endl;
            return nullopt;
        }
        Args args;
        auto sourceRadix = ReadInt(argv[1]);
        auto resultRadix = ReadInt(argv[2]);
        if (!sourceRadix || !resultRadix)
        {
            cout << ERROR_RADIX_MESSAGE;
            return nullopt;
        }
        args.sourceRadix = *sourceRadix;
        args.resultRadix = *resultRadix;
        args.number = argv[3];

        return args;
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    try
    {
        int number = StringToInt(args->number, args->sourceRadix);
        string str = IntToString(number, args->resultRadix);
        cout << str << endl;
    }
    catch (invalid_argument& e)
    {
        cout << ERROR_RADIX_MESSAGE << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}