#include <iostream>
#include <algorithm>
#include <vector>

bool ReadVector(std::vector<double> vector)
{
    double inValue;
    while (std::cin >> inValue)
    {
        vector.push_back(inValue);
    }

    return true;
}

int main()
{
    std::vector<double> vector;
    if (!ReadVector(vector))
    {
        return 1;
    }

    return 0;
}
