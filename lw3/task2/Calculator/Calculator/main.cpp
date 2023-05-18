#include "main.h"
#include <math.h>

namespace
{
    using namespace std;

	struct Command
	{
		string keyWord;
		string args;
	};

	const int AMOUNT_DIGITS_AFTER_POINT = 2;

    const string BEFORE_USER_INPUT_MESSAGE = ">";
    const string UNKNOWN_COMMAND_MESSAGE = "Unknown command";
    const string EXIT_COMMAND = "exit";

    const string INIT_VAR_COMMAND_KEY_WORD = "var";
    const string INIT_VAR_WITH_VALUE_COMMAND_KEY_WORD = "let";
    const string INIT_FUNCTION_COMMAND_KEY_WORD = "fn";
    const string PRINT_VALUE_COMMAND_KEY_WORD = "print";
    const string PRINT_VARIABLES_COMMAND_KEY_WORD = "printvars";
    const string PRINT_FUNCTIONS_COMMAND_KEY_WORD = "printfns";

	void LeftTrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	void RighTrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	string Trim(std::string& s) {
		RighTrim(s);
		LeftTrim(s);

		return s;
	}

	double RoundNumber(double number)
	{
		double numberToMovePoint = pow(10, AMOUNT_DIGITS_AFTER_POINT);
		return round(number * numberToMovePoint) / numberToMovePoint;
	}

	Command ParseUserInput(string const& input)
	{
		size_t keyValueDividerPos = input.find(' ');
		string keyWord = input.substr(0, keyValueDividerPos);

		string args;
		if (keyValueDividerPos != string::npos)
		{
			args = input.substr(keyValueDividerPos);
		}
		Trim(keyWord);
		Trim(args);

		return { keyWord, args };
	}

	Command ReadUserCommand()
	{
		string input;
		do
		{
			cout << BEFORE_USER_INPUT_MESSAGE << " ";
			getline(cin, input);
		} while (input.empty());

		return ParseUserInput(input);
	}

	optional<size_t> GetOperationSignPos(std::string const& stringToSearchIn)
	{
		for (auto i = 0; i < stringToSearchIn.length(); i++)
		{
			if (stringToSearchIn[i] == '+' || stringToSearchIn[i] == '-' || stringToSearchIn[i] == '*' || stringToSearchIn[i] == '/')
			{
				return i;
			}
		}

		return nullopt;
	}

	bool ProcessInitVariableCommand(std::string const& args, Calculator& calculator)
	{
		return calculator.InitVariable(args);
	}

	bool ProcessInitVariableWithValueCommand(std::string const& args, Calculator& calculator)
	{
		size_t varValueDividerPos = args.find('=');
		std::string variableName = args.substr(0, varValueDividerPos);
		std::string variableValueString = args.substr(varValueDividerPos + 1);
		Trim(variableName);
		Trim(variableValueString);
		try
		{
			double value = stod(variableValueString);
			return calculator.InitVariable(variableName, value);
		}
		catch (invalid_argument const& ex)
		{
			return calculator.InitVariable(variableName, variableValueString);
		}
		catch (out_of_range const& ex)
		{
			cout << "Incorrect number" << endl;
			return true;
		}
	}

	bool ProcessInitFunctionCommand(string const& args, Calculator& calculator)
	{
		size_t functionValueDividerPos = args.find('=');
		string functionName = args.substr(0, functionValueDividerPos);
		Trim(functionName);
		string functionValue = args.substr(functionValueDividerPos + 1);
		auto operationSignPos = GetOperationSignPos(functionValue);
		if (operationSignPos)
		{
			string firstOperand = functionValue.substr(0, *operationSignPos);
			string secondOperand = functionValue.substr(*operationSignPos + 1);
			Trim(firstOperand);
			Trim(secondOperand);
			return calculator.InitFunction(functionName, firstOperand, functionValue[*operationSignPos], secondOperand);
		}
		else
		{
			Trim(functionValue);
			return calculator.InitFunction(functionName, functionValue);
		}
	}

	void ProcessPrintValueCommand(std::string const& args, Calculator& calculator)
	{
		cout << RoundNumber(calculator.GetValue(args)) << endl;
	}

	void ProcessPrintVariablesCommand(Calculator& calculator)
	{
		auto variables = calculator.GetVariables();
		for (auto variable : variables)
		{
			cout << variable.first << ": " << RoundNumber(variable.second.GetValue()) << endl;
		}
	}

	void ProcessPrintFunctionsCommand(Calculator& calculator)
	{
		auto variables = calculator.GetFunctions();
		for (auto variable : variables)
		{
			cout << variable.first << ": " << RoundNumber(variable.second.GetValue()) << endl;
		}
	}

	void ProcessUserCommand(Command command, Calculator& calculator)
	{
		if (command.keyWord == INIT_VAR_COMMAND_KEY_WORD)
		{
			if (!ProcessInitVariableCommand(command.args, calculator))
			{
				cout << "This name is unavailable or already used" << endl;
			}
			return;
		}
		if (command.keyWord == INIT_VAR_WITH_VALUE_COMMAND_KEY_WORD)
		{
			if (!ProcessInitVariableWithValueCommand(command.args, calculator))
			{
				cout << "Incorrect variable name" << endl;
			}
			return;
		}
		if (command.keyWord == INIT_FUNCTION_COMMAND_KEY_WORD)
		{
			if (!ProcessInitFunctionCommand(command.args, calculator))
			{
				cout << "Error in variable or function name" << endl;
			}
			return;
		}
		if (command.keyWord == PRINT_VALUE_COMMAND_KEY_WORD)
		{
			ProcessPrintValueCommand(command.args, calculator);
			return;
		}
		if (command.keyWord == PRINT_VARIABLES_COMMAND_KEY_WORD)
		{
			ProcessPrintVariablesCommand(calculator);
			return;
		}

		if (command.keyWord == PRINT_FUNCTIONS_COMMAND_KEY_WORD)
		{
			ProcessPrintFunctionsCommand(calculator);
			return;
		}

		cout << UNKNOWN_COMMAND_MESSAGE << endl;
	}
}

int main()
{
	Calculator calculator;
	Command userCommand = ReadUserCommand();

	while (userCommand.keyWord != EXIT_COMMAND)
	{
		ProcessUserCommand(userCommand, calculator);
		userCommand = ReadUserCommand();
	}

    return EXIT_SUCCESS;
}