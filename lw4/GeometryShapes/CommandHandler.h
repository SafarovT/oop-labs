#pragma once
#include <istream>
#include <vector>
#include <optional>
#include "IShape.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CPoint.h"
#include "CCanvas.h"

class CommandHandler
{
public:
	CommandHandler(std::istream& input, std::ostream& output)
		: m_input(input)
		, m_output(output)
	{
	};

	void StartListening();
	void PrintResult() const;
	void DrawResult();
private:
	using Shapes = std::vector<IShape*>;
	using Params = std::vector<std::string>;
	struct Command
	{
		std::string keyWord;
		Params params;
	};

	std::istream& m_input;
	std::ostream& m_output;
	Shapes m_shapes;
	CCanvas m_canvas;
	Command m_command;

	const std::string BEFORE_USER_INPUT_MESSAGE = ">";
	const std::string UNKNOWN_COMMAND_MESSAGE = "Unknown command";
	const std::string ERROR_PARAMS_COUNT_MESSAGE = "Wrong params cound";
	const std::string ERROR_SYNTAX_MESSAGE = "Error syntax";
	const std::string EXIT_COMMAND = "exit";

	const std::string LINE_KEY_WORD = "line";
	const std::string RECTANGLE_KEY_WORD = "rectangle";
	const std::string TRIANGLE_KEY_WORD = "triangle";
	const std::string CIRCLE_KEY_WORD = "circle";
	const std::string HELP_KEY_WORD = "help";

	static Command ParseUserInput(std::string const& input);

	void ReadUserCommand();
	void ProcessHelpCommand();
	std::optional<CPoint> ParsePointParams(std::string const& xString, std::string const& yString);
	void AddLine(Params const& params);
	void AddRectangle(Params const& params);
	void AddTriangle(Params const& params);
	void AddCircle(Params const& params);
	void ProcessUserCommand();
	IShape* GetMaxAreaShape() const;
	IShape* GetMinPerimeterShape() const;
};