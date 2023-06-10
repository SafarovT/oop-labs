#include <vector>
#include <iostream>

namespace
{
	using namespace std;
}

template <typename T, typename Less>
inline bool FindMax(vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];
	for (T const& value : arr)
	{
		if (less(maxValue, value))
		{
			maxValue = value;
		}
	}

	return true;
}

template <typename T>
inline bool FindMax(vector<T> const& arr, T& maxValue)
{
	auto less = [](T value1, T value2) { return value1 < value2; };
	return FindMax(arr, maxValue, less);
}

template <>
inline bool FindMax<const char*>(vector<const char*> const& arr, const char*& maxValue)
{
	auto strLess = [](const char* str1, const char* str2) { return strcmp(str2, str1) > 0; };
	return FindMax(arr, maxValue, strLess);
}