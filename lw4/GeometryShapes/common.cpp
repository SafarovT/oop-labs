#include "common.h"
#include <format>

namespace
{
	const double AMOUNT_DIGITS_AFTER_POINT = 2;
}

std::string DoubleToString(double const number)
{
	double numberToMovePoint = pow(10, AMOUNT_DIGITS_AFTER_POINT);
	double resultNumber = round((number * numberToMovePoint) / numberToMovePoint);

	return std::format("{:.2f}", resultNumber);
}

std::string IntToHexNumber(uint32_t const number)
{
	return std::format("{:#06x}", number);
}

std::optional<double> StringToDouble(std::string numberString)
{
	try
	{
		double number = std::stod(numberString);


		return number;
	}
	catch (std::invalid_argument const& ex)
	{
	}
	catch (std::out_of_range const& ex)
	{
	}

	return std::nullopt;
}

std::optional<uint32_t> StringToInt(std::string numberString)
{
	try
	{
		uint32_t number = std::stoi(numberString);


		return number;
	}
	catch (std::invalid_argument const& ex)
	{
	}
	catch (std::out_of_range const& ex)
	{
	}

	return std::nullopt;
}