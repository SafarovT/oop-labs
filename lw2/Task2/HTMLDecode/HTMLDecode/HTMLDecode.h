#pragma once
#include <iostream>
#include <string>
#include <optional>

enum ProgramEndCode
{
	Success = 0, Error = 1
};

std::string HTMLDecode(std::string const& html);