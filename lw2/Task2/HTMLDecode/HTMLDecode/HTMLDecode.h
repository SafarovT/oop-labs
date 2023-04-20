#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <map>

enum ProgramEndCode
{
	Success = 0, Error = 1
};

std::string HTMLDecode(std::string_view html);