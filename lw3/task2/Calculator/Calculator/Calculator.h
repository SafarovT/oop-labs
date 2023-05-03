#pragma once
#include "Memory.h";
#include <iostream>

class Calculator
{
public:
	bool InitVariable();
	bool InitVariableWithValue();

private:
	Memory m_memory;
	const std::string EXIT_COMMAND = "exit";
	const std::string BEFORE_USER_INPUT_MESSAGE = "> ";
	std::string ReadUserCommand(std::istream& inputStream, std::ostream& outputStream) const;
};