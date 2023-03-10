#include "VectorHandler.h"

bool ReadVector(std::istream& input, VectorType& vector)
{
    VectorElementType inValue;
    while (input >> inValue)
    {
        vector.push_back(inValue);
    }
    if (!input.eof())
    {
        return false;
    };

    return !vector.empty();
}

void MultVectorOnMinValue(VectorType& vector)
{
    VectorElementType minElement = *std::ranges::min_element(vector);
    for (VectorElementType& element : vector)
    {
        element *= minElement;
    }
}

void PrintVectorSorted(std::ostream& output, VectorType& vector)
{
    std::sort(vector.begin(), vector.end());
    copy(vector.begin(), vector.end(), std::ostream_iterator<VectorElementType>(output, " "));
}