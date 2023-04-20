#include "Car.h"
#include <iostream>
#include <string>


namespace
{
    using namespace std;
	const string BEFORE_USER_INPUT_MESSAGE = ">";
	const string ERROR_INPUT_MESSAGE = "Wrong command";

	const string INFO_COMMAND = "Info";
	const string ENGINE_ON_COMMAND = "EngineOn";
	const string ENGINE_OFF_COMMAND = "EngineOff";
	const string SET_GEAR_COMMAND = "SetGear";
	const string SET_SPEED_COMMAND = "SetSpeed";
	// messages to startup
    
	void ReadUntilInputWithSymbols(string& input)
	{
		do
		{
			cout << BEFORE_USER_INPUT_MESSAGE << " ";
			getline(cin, input);
		} while (input.empty());
	}

	void ProcessUserCommand(string const& command)
	{
		if (command == INFO_COMMAND)
		{

		}
		if (command == ENGINE_ON_COMMAND)
		{

		}
		if (command == ENGINE_OFF_COMMAND)
		{

		}
		if (command == SET_GEAR_COMMAND)
		{

		}
		if (command == SET_SPEED_COMMAND)
		{

		}

		cout << ERROR_INPUT_MESSAGE << endl;
	}
}

int main()
{
	Car car;

}