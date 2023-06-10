#include "common.h"

namespace
{
	using namespace std;
}

string StringToLowerCase(string stringToTransform)
{
	transform(stringToTransform.cbegin(), stringToTransform.cend(), stringToTransform.begin(), ::tolower);

	return stringToTransform;
}