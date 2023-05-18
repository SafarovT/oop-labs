#pragma once
#include <math.h>
#include <string>
#include <optional>

std::string DoubleToString(double const number);
std::string IntToHexNumber(uint32_t const number);
std::optional<double> StringToDouble(std::string numberString);
std::optional<uint32_t> StringToInt(std::string numberString);