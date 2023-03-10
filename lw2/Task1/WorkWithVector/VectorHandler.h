#pragma once

#include <iostream>
#include <algorithm>
#include <vector>


using VectorElementType = int;
using VectorType = std::vector<VectorElementType>;
enum ProgramEndCode
{
    Success = 0, Error = 1
};

bool ReadVector(std::istream& input, VectorType& vector);
void MultVectorOnMinValue(VectorType& vector);
void PrintVectorSorted(std::ostream& output, VectorType& vector);