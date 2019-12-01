#include "Day1B.h"

Day1B::Day1B()
{
}

Day1B::~Day1B()
{
}

void Day1B::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day1/Day1A_test.txt" : "Day1/Day1A.txt";

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
            const int inputInt = static_cast<int>(std::stoul(inputString, nullptr, 0));
            input.push_back(inputInt);
        }
    }
    inputStream.close();
}

void Day1B::ProcessData()
{
    std::function<int(int)> lambda = [&lambda](int x) -> int
    {
        //take its mass, divide by three, round down, and subtract 2
        int fuel = x / 3 - 2;
        //treat the fuel amount you just calculated as the input mass and repeat the process, 
        //continuing until a fuel requirement is zero or negative
        return fuel > 0 ? fuel + lambda(fuel) : 0;
    };

    std::transform(input.begin(), input.end(), input.begin(), lambda);
    //PrintVector();

    //then add together all the fuel values
    output = std::accumulate(input.begin(), input.end(), 0);
}

void Day1B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

void Day1B::PrintVector()
{
    std::for_each(input.begin(), 
                  input.end(),
                  [](const auto &elem)
                  {
                      std::cout << elem << " " << std::endl;
                  });
}
