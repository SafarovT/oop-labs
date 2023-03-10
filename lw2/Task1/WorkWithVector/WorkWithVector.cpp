#include "VectorHandler.h"

int main()
{
    VectorType vector;

    if (!ReadVector(std::cin, vector))
    {
        std::cout << "Please input a not empty valid vector" << std::endl;
        
        return ProgramEndCode::Error;
    }
    MultVectorOnMinValue(vector);
    PrintVectorSorted(std::cout, vector);

    return ProgramEndCode::Success;
}
