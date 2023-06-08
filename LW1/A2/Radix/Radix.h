#pragma once
#include <string>
#include <stdexcept>

int StringToInt(std::string const& str, int radix);
std::string IntToString(int n, int radix);