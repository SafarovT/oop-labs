#include "Car.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace
{
    using namespace std;

	struct Command
	{
		string keyWord;
		string value;
	};

	const string BEFORE_USER_INPUT_MESSAGE = ">";
	const string UNKNOWN_COMMAND_MESSAGE = "Unknown command";

	const string INFO_COMMAND = "Info";
	const string ENGINE_ON_COMMAND = "EngineOn";
	const string ENGINE_OFF_COMMAND = "EngineOff";
	const string SET_GEAR_COMMAND = "SetGear";
	const string SET_SPEED_COMMAND = "SetSpeed";
	const string EXIT_COMMAND = "Exit";

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

	Command ParseUserInput(string const& input)
	{
		size_t keyValueDividerPos = input.find(' ');
		string keyWord = input.substr(0, keyValueDividerPos);

		string value;
		if (keyValueDividerPos != string::npos)
		{
			value = input.substr(keyValueDividerPos);
		}
		Trim(keyWord);
		Trim(value);

		return { keyWord, value };
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

	string EngineStateToString(bool isTurnedOn)
	{
		return isTurnedOn ? "Заведена" : "Заглушена";
	}

	string DirectionToString(Direction direction)
	{
		switch (direction)
		{
		case Direction::Backward:
			return "Назад";
		case Direction::NoDirection:
			return "Стоит на месте";
		case Direction::Forward:
			return "Вперед";
		default:
			"(Ошибка при определении нарпавления)";
		}
	}

	string GearToString(Gear gear)
	{
		switch (gear)
		{
		case Gear::Reverse:
			return "Задний ход";
		case Gear::Neutral:
			return "Нейтральная";
		case Gear::First:
			return "Первая";
		case Gear::Second:
			return "Вторая";
		case Gear::Third:
			return "Третья";
		case Gear::Fourth:
			return "Четвёртая";
		case Gear::Fifth:
			return "Пятая";
		default:
			return "(Ошибка при определении передачи)";
		}
	}

	optional<int> StringToInt(string const& s)
	{
		int number;
		try
		{
			number = stoi(s);
		}
		catch (invalid_argument& e)
		{
			return nullopt;
		}
		catch (std::out_of_range& e)
		{
			return nullopt;
		}

		return number;
	}

	void ProcessInfoCommand(Car const& car)
	{
		cout << "Машина " << EngineStateToString(car.IsTurnedOn()) << endl
			<< "Скорость: " << car.GetSpeed() << endl
			<< "Направление: " << DirectionToString(car.GetDirection()) << endl
			<< "Передача: " << GearToString(car.GetGear()) << endl;
	}

	void ProcessEngineOnCommand(Car& car)
	{
		if (!car.TurnOnEngine())
		{
			cout << "Error while turning engine on";
		}
	}

	void ProcessEngineOffCommand(Car& car)
	{
		if (!car.TurnOffEngine())
		{
			cout << "Error while turning engine off." << endl
				<< "Check gear (should be neutral) and speed (you should stay still)." << endl;
		}
	}

	void ProcessSetGearCommand(Car& car, Gear gear)
	{
		if (!car.SetGear(gear))
		{
			cout << "Error while setting gear." << endl
				<< "Maybee you should change your speed first." << endl;
		}
	}

	void ProcessSetSpeedCommand(Car& car, int speed)
	{
		if (!car.SetSpeed(speed))
		{
			cout << "Error while setting speed." << endl
				<< "Maybee you should switch your gear first." << endl;
		}
	}

	void ProcessUserCommand(Command const& command, Car& car)
	{
		if (command.keyWord == INFO_COMMAND)
		{
			ProcessInfoCommand(car);
			return;
		}
		if (command.keyWord == ENGINE_ON_COMMAND)
		{
			ProcessEngineOnCommand(car);
			return;
		}
		if (command.keyWord == ENGINE_OFF_COMMAND)
		{
			ProcessEngineOffCommand(car);
			return;
		}
		if (command.keyWord == SET_GEAR_COMMAND)
		{
			auto gear = StringToInt(command.value);
			auto isGearInValidRange = [](int gear) {
				return (gear <= static_cast<int>(Gear::Fifth) && gear >= static_cast<int>(Gear::Reverse)) ;
			};
			if (gear && isGearInValidRange(*gear))
			{
				ProcessSetGearCommand(car, static_cast<Gear>(*gear));
			}
			else
			{
				cout << "Enter a correct gear as a number in range [-1; 5]" << endl;
			}

			return;
		}
		if (command.keyWord == SET_SPEED_COMMAND)
		{
			auto speed = StringToInt(command.value);
			if (speed)
			{
				ProcessSetSpeedCommand(car, *speed);
			}
			else
			{
				cout << "Enter a speed as a correct number after " << SET_SPEED_COMMAND << endl;
			}

			return;
		}

		cout << UNKNOWN_COMMAND_MESSAGE << endl;
	}
}

int main()
{
	Car car;
	Command userCommand = ReadUserCommand();

	while (userCommand.keyWord != EXIT_COMMAND)
	{
		ProcessUserCommand(userCommand, car);
		userCommand = ReadUserCommand();
	}

	return EXIT_SUCCESS;
}