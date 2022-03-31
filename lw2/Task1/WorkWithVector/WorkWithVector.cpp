#include <iostream>
#include <algorithm>
#include <vector>

void ReadVector(std::vector<double> vector)
{
    double inValue;
    while (std::cin >> inValue)
    {
        vector.push_back(inValue);
    }
}

int main()
{
    std::vector<double> vector;
    ReadVector(vector);

    double minValue = std::min_element(vector[0], vector[2]);

    return 0;
}
