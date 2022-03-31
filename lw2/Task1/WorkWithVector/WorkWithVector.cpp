#include <iostream>
#include <algorithm>
#include <vector>

void ReadVector(std::vector<int> vector)
{
    int inValue;
    while (std::cin >> inValue && std::cin.eof())
    {
        vector.push_back(inValue);
    }
}

void MultOnMinValue(std::vector<int> vector)
{
    int minValue = vector[0];
    std::cout << "there";
    for (int element : vector)
    {
        if (element < minValue)
        {
            minValue = element;
        }
    }

    for (int element : vector)
    {
        element *= minValue;
    }

    /*std::for_each(vector.begin(), vector.end(),
        [](int i) {i *= minValue;}
    );*/
}

void PrintVector(std::vector<int> vector)
{
    std::sort(vector.begin(), vector.end());
    copy(vector.begin(), vector.end(), std::ostream_iterator<int>(std::cout, " "));
}

int main()
{
    std::vector<int> vector;

    ReadVector(vector);
    std::cout << "Readed\n";
    MultOnMinValue(vector);
    std::cout << "Multed\n";
    PrintVector(vector);

    return 0;
}
