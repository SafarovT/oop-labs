#include "CommandHandler.h"
#include "Common.h"

using namespace std;

CommandHandler::Command CommandHandler::ParseUserInput(string const& input)
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

void CommandHandler::ReadUserCommand()
{
	string commandText;
	do
	{
		getline(m_input, commandText);
	} while (commandText.empty());

	m_command = ParseUserInput(commandText);
}

void CommandHandler::ProcessHelpCommand()
{
	m_output << "line <x1> <y1> <x2> <y2> <outline_color>" << endl
		<< "rectangle <left_top_x> <left_top_y> <right_bottom_x> <right_bottom_y> <outline_color> <fill_color>" << endl
		<< "triangle <x1> <y1> <x2> <y2> <x3> <y3> <outline_color> <fill_color>" << endl
		<< "circle <center_x> <center_y> <radius> <outline_color> <fill_color>" << endl;
}

optional<CPoint> CommandHandler::ParsePointParams(string const& xString, string const& yString)
{
	auto x = StringToDouble(xString);
	auto y = StringToDouble(yString);

	if (!x || !y)
	{
		return nullopt;
	}

	return CPoint(*x, *y);
}

void CommandHandler::AddLine(Params const& params)
{
	if (params.size() < 5)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	auto startPoint = ParsePointParams(params[0], params[1]);
	auto endPoint = ParsePointParams(params[2], params[3]);
	auto color = ParseHex(params[4]);

	if (!startPoint || !endPoint || !color)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_shapes.push_back(new CLineSegment(*startPoint, *endPoint, *color));
}

void CommandHandler::AddRectangle(Params const& params)
{
	if (params.size() < 6)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	auto leftTopPoint = ParsePointParams(params[0], params[1]);
	auto rightBottomPoint = ParsePointParams(params[2], params[3]);
	auto outlineColor = ParseHex(params[4]);
	auto fillColor = ParseHex(params[5]);

	if (!leftTopPoint || !rightBottomPoint || !outlineColor || !fillColor)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_shapes.push_back(new CRectangle(*leftTopPoint, *rightBottomPoint, *outlineColor, *fillColor));
}

void CommandHandler::AddTriangle(Params const& params)
{

	if (params.size() < 8)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}

	auto vertex1 = ParsePointParams(params[0], params[1]);
	auto vertex2 = ParsePointParams(params[2], params[3]);
	auto vertex3 = ParsePointParams(params[4], params[5]);
	auto outlineColor = ParseHex(params[6]);
	auto fillColor = ParseHex(params[7]);

	if (!vertex1 || !vertex2 || !vertex3 || !outlineColor || !fillColor)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_shapes.push_back(new CTriangle(*vertex1, *vertex2, *vertex3, *outlineColor, *fillColor));
}

void CommandHandler::AddCircle(Params const& params)
{
	if (params.size() < 5)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	auto centerPoint = ParsePointParams(params[0], params[1]);
	auto radius = StringToDouble(params[2]);
	auto outlineColor = ParseHex(params[3]);
	auto fillColor = ParseHex(params[4]);

	if (!centerPoint || !radius || !outlineColor || !fillColor)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_shapes.push_back(new CCircle(*centerPoint, *radius, *outlineColor, *fillColor));
}

void CommandHandler::ProcessUserCommand()
{
	if (m_command.keyWord == HELP_KEY_WORD)
	{
		ProcessHelpCommand();// command=>func
		return;
	}
	else if (m_command.keyWord == LINE_KEY_WORD)
	{
		AddLine(m_command.params);
		return;
	}
	else if (m_command.keyWord == RECTANGLE_KEY_WORD)
	{
		AddRectangle(m_command.params);
		return;
	}
	else if (m_command.keyWord == CIRCLE_KEY_WORD)
	{
		AddCircle(m_command.params);
		return;
	}
	else if (m_command.keyWord == TRIANGLE_KEY_WORD)
	{
		AddTriangle(m_command.params);
		return;
	}

	m_output << UNKNOWN_COMMAND_MESSAGE << endl;
}

IShape* CommandHandler::GetMaxAreaShape() const
{
	IShape* maxAreaShape = m_shapes[0];
	for (size_t i = 1; i < m_shapes.size(); i++)
	{
		if (m_shapes[i]->GetArea() > maxAreaShape->GetArea())
		{
			maxAreaShape = m_shapes[i];
		}
	}

	return maxAreaShape;
}

IShape* CommandHandler::GetMinPerimeterShape() const
{
	IShape* minPerimeterShape = m_shapes[0];
	for (size_t i = 1; i < m_shapes.size(); i++)
	{
		if (m_shapes[i]->GetPerimeter() < minPerimeterShape->GetPerimeter())
		{
			minPerimeterShape = m_shapes[i];
		}
	}

	return minPerimeterShape;
}

void CommandHandler::StartListening()
{
	ReadUserCommand();
	while (m_command.keyWord != EXIT_COMMAND)
	{
		ProcessUserCommand();
		ReadUserCommand();
	}
}

void CommandHandler::PrintResult() const
{
	if (m_shapes.size() == 0)
	{
		m_output << "No shapes added" << endl;
	}
	else
	{
		m_output << "Shape with max area: " << GetMaxAreaShape()->ToString() << endl
		     << "Shape with min perimeter: " << GetMinPerimeterShape()->ToString();
	}
}

void CommandHandler::DrawResult()
{
	for (auto shape : m_shapes)
	{
		shape->Draw(m_canvas);
	}
	m_canvas.DisplayResult();
}