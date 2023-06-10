#include "Radix.h"
#include <iostream>

namespace
{
	using namespace std;

	const int MIN_RADIX = 2;
	const int MAX_RADIX = 36;
	const int MIN_INT = numeric_limits<int>::min();
	const int MAX_INT = numeric_limits<int>::max();
	const string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	bool IsRadixInvalid(int radix)
	{
		return radix < MIN_RADIX || radix > MAX_RADIX;
	}

	int GetDigitValue(char digit)
	{
		size_t value = DIGITS.find(digit);
		return value;
	}

	bool IsDigitCorrectForRadix(int radix, char digit)
	{
		size_t value = DIGITS.find(digit);
		return (value == string::npos || value >= radix);
	}

	bool IsOperationOverflowing()
}

int StringToInt(std::string const& str, int radix)
{
	if (IsRadixInvalid(radix))
	{
		throw invalid_argument("Invalid radix value");
	}
	
	size_t firstStringPos = 0;
	int numberSign = 1;
	if (str[0] == '-')
	{
		firstStringPos = 1;
		numberSign = -1;
	}

	int number = 0;

	for (size_t i = firstStringPos; i < str.length(); i++)
	{
		char digit = toupper(str[i]);
		int digitValue = GetDigitValue(digit) * numberSign;
		if (IsDigitCorrectForRadix(radix, digit))
		{
			throw invalid_argument("Invalid digit in number");
		}
		if (number > (MAX_INT - digitValue) / radix)
		{
			throw out_of_range("Digit is not in range");
		}
		number = number * radix + digitValue; // проверка на переполнение
	}

	return number * numberSign;
}

std::string IntToString(int num, int radix)
{
	if (IsRadixInvalid(radix))
	{
		throw invalid_argument("Invalid radix value");
	}

	if (num == 0)
	{
		return "0";
	}

	string str;
	bool isNegative = false;
	if (num < 0)
	{
		num *= -1;
		isNegative = true;
	}
	while (num)
	{
		str.push_back(DIGITS[num % radix]);
		num /= radix;
	}
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
	{
		swap(str[i], str[j]);
	}

	return isNegative ? ('-' + str) : str;
}