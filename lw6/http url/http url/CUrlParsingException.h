#pragma once
#include <stdexcept>

class CUrlParsingException : public std::invalid_argument
{
public:
	CUrlParsingException(std::string const& message)
		: std::invalid_argument(message)
	{}
};