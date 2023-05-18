#include <iostream>
#include <vector>
#include "common.h"

#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CPoint.h"

namespace
{
	using namespace std;

	using Shapes = std::vector<CShape*>;
	using Params = vector<string>;
	struct Command
	{
		string keyWord;
		Params params;
	};

	const string BEFORE_USER_INPUT_MESSAGE = ">";
	const string UNKNOWN_COMMAND_MESSAGE = "Unknown command";
	const string ERROR_PARAMS_COUNT_MESSAGE = "Wrong params cound";
	const string ERROR_SYNTAX_MESSAGE = "Error syntax";
	const string EXIT_COMMAND = "exit";

	const string LINE_KEY_WORD = "line";
	const string RECTANGLE_KEY_WORD = "rectangle";
	const string TRIANGLE_KEY_WORD = "triangle";
	const string CIRCLE_KEY_WORD = "circle";
	const string HELP_KEY_WORD = "help";

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

	string Trim(std::string s) {
		RighTrim(s);
		LeftTrim(s);

		return s;
	}

	Command ParseUserInput(string const& input)
	{
		size_t separatorPos = input.find(' ');
		string keyWord = Trim(input.substr(0, separatorPos));
		Params params;

		if (separatorPos == string::npos)
		{
			return { keyWord, params };
		}

		string paramsString = Trim(input.substr(separatorPos));
		separatorPos = paramsString.find(' ');
		while (separatorPos != string::npos)
		{
			params.push_back(Trim(paramsString.substr(0, separatorPos)));
			paramsString = Trim(paramsString.substr(separatorPos + 1));
			separatorPos = paramsString.find(' ');
		}
		params.push_back(paramsString);

		return { keyWord, params };
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

	void ProcessHelpCommand()
	{
		cout << "line <x1> <y1> <x2> <y2> <outline_color>" << endl
			<< "rectangle <left_top_x> <left_top_y> <right_bottom_x> <right_bottom_y> <outline_color> <fill_color>" << endl
			<< "triangle <x1> <y1> <x2> <y2> <x3> <y3> <outline_color> <fill_color>" << endl
			<< "circle <center_x> <center_y> <radius> <outline_color> <fill_color>" << endl;
	}

	optional<CPoint> ParsePointParams(string xString, string yString)
	{
		auto x = StringToDouble(xString);
		auto y = StringToDouble(yString);

		if (!x || !y)
		{
			return nullopt;
		}

		return CPoint(*x, *y);
	}

	void AddLine(Params params, Shapes& shapes)
	{
		if (params.size() < 5)
		{
			cout << ERROR_PARAMS_COUNT_MESSAGE << endl;
			return;
		}
		auto startPoint = ParsePointParams(params[0], params[1]);
		auto endPoint = ParsePointParams(params[2], params[3]);
		auto color = StringToInt(params[4]);

		if (!startPoint || !endPoint || !color)
		{
			cout << ERROR_SYNTAX_MESSAGE << endl;
			return;
		}
		shapes.push_back(new CLineSegment(*startPoint, *endPoint, *color));
	}

	void AddRectangle(Params params, Shapes& shapes)
	{
		if (params.size() < 6)
		{
			cout << ERROR_PARAMS_COUNT_MESSAGE << endl;
			return;
		}
		auto leftTopPoint = ParsePointParams(params[0], params[1]);
		auto rightBottomPoint = ParsePointParams(params[2], params[3]);
		auto outlineColor = StringToInt(params[4]);
		auto fillColor = StringToInt(params[5]);

		if (!leftTopPoint || !rightBottomPoint || !outlineColor || !fillColor)
		{
			cout << ERROR_SYNTAX_MESSAGE << endl;
			return;
		}
		shapes.push_back(new CRectangle(*leftTopPoint, *rightBottomPoint, *outlineColor, *fillColor));
	}

	void AddTriangle(Params params, Shapes& shapes)
	{
		if (params.size() < 8)
		{
			cout << ERROR_PARAMS_COUNT_MESSAGE << endl;
			return;
		}

		auto vertex1 = ParsePointParams(params[0], params[1]);
		auto vertex2 = ParsePointParams(params[2], params[3]);
		auto vertex3 = ParsePointParams(params[4], params[5]);
		auto outlineColor = StringToInt(params[6]);
		auto fillColor = StringToInt(params[7]);

		if (!vertex1 || !vertex2 || !vertex3 || !outlineColor || !fillColor)
		{
			cout << ERROR_SYNTAX_MESSAGE << endl;
			return;
		}
		shapes.push_back(new CTriangle(*vertex1, *vertex2, *vertex3, *outlineColor, *fillColor));
	}

	void AddCircle(Params params, Shapes& shapes)
	{
		if (params.size() < 5)
		{
			cout << ERROR_PARAMS_COUNT_MESSAGE << endl;
			return;
		}
		auto centerPoint = ParsePointParams(params[0], params[1]);
		auto radius = StringToDouble(params[2]);
		auto outlineColor = StringToInt(params[3]);
		auto fillColor = StringToInt(params[4]);

		if (!centerPoint || !radius || !outlineColor || !fillColor)
		{
			cout << ERROR_SYNTAX_MESSAGE << endl;
			return;
		}
		shapes.push_back(new CCircle(*centerPoint, *radius, *outlineColor, *fillColor));
	}

	void ProcessUserCommand(Command const& command, Shapes& shapes)
	{
		if (command.keyWord == HELP_KEY_WORD)
		{
			ProcessHelpCommand();
			return;
		}
		else if (command.keyWord == LINE_KEY_WORD)
		{
			AddLine(command.params, shapes);
			return;
		}
		else if (command.keyWord == RECTANGLE_KEY_WORD)
		{
			AddRectangle(command.params, shapes);
			return;
		}
		else if (command.keyWord == CIRCLE_KEY_WORD)
		{
			AddCircle(command.params, shapes);
			return;
		}
		else if (command.keyWord == TRIANGLE_KEY_WORD)
		{
			AddTriangle(command.params, shapes);
			return;
		}

		cout << UNKNOWN_COMMAND_MESSAGE << endl;
	}
}

CShape* GetMaxAreaShape(Shapes const& shapes)
{
	CShape* maxAreaShape = shapes[0];
	for (size_t i = 1; i < shapes.size(); i++)
	{
		if (shapes[i]->GetArea() > maxAreaShape->GetArea())
		{
			maxAreaShape = shapes[i];
		}
	}

	return maxAreaShape;
}

CShape* GetMinPerimeterShape(Shapes const& shapes)
{
	CShape* minPerimeterShape = shapes[0];
	for (size_t i = 1; i < shapes.size(); i++)
	{
		if (shapes[i]->GetPerimeter() < minPerimeterShape->GetPerimeter())
		{
			minPerimeterShape = shapes[i];
		}
	}

	return minPerimeterShape;
}

int main(int argc, char* argv[])
{
	Shapes shapes;
	Command userCommand = ReadUserCommand();

	while (userCommand.keyWord != EXIT_COMMAND)
	{
		ProcessUserCommand(userCommand, shapes);
		userCommand = ReadUserCommand();
	}

	if (shapes.size() > 0)
	{
		cout << "Shape with max area: " <<  GetMaxAreaShape(shapes)->ToString() << endl;
		cout << "Shape with min perimeter: " << GetMinPerimeterShape(shapes)->ToString();
	}
	else
	{
		cout << "No shapes added";
	}

	return EXIT_SUCCESS;
}