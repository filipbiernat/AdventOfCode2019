#include "Day1A.h"

Day1A::Day1A()
{
}

Day1A::~Day1A()
{
}

void Day1A::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day1/Day1a_test.txt" : "Day1/Day1a.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString))
    {
        if (inputString.size() > 0)
        {
            const unsigned int inputUnsignedInt = static_cast<unsigned int>(std::stoul(inputString, nullptr, 0));
            input.push_back(inputUnsignedInt);
        }
    }
    inputStream.close();
}

void Day1A::ProcessData()
{
    auto lambda = [](unsigned int x) -> unsigned int 
    {
        //take its mass, divide by three, round down, and subtract 2
        return x / 3 - 2;
    };

    std::transform(input.begin(), input.end(), input.begin(), lambda);

    //then add together all the fuel values
    output = std::accumulate(input.begin(), input.end(), 0);
}

void Day1A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}
