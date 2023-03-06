#include <iostream>
#include <algorithm>
#include <vector>

enum ProgramEndCode
{
    Success = 0, Error = 1
};

using VectorElementType = int;
using VectorType = std::vector<VectorElementType>;

void ReadVector(VectorType& vector)
{
    int inValue;
    while (std::cin >> inValue)
    {
        vector.push_back(inValue);
    }
}

void MultVectorOnMinValue(VectorType& vector)
{
    VectorType::iterator minElementIterator = std::min_element(vector.begin(), vector.end());
    auto multElementOnMinValue = [](VectorElementType element, VectorType::iterator minElementIterator) { return element * *minElementIterator; };
    std::transform(vector.begin(), vector.end(), vector.begin(), multElementOnMinValue);
}

void PrintVectorSorted(const VectorType& vector)
{
    std::sort(vector.begin(), vector.end());
    copy(vector.begin(), vector.end(), std::ostream_iterator<size_t>(std::cout, " "));
}

int main()
{
    VectorType vector;

    ReadVector(vector);
    MultVectorOnMinValue(vector);
    PrintVectorSorted(vector);

    return ProgramEndCode::Success;
}
