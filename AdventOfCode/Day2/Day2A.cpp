#include "Day2A.h"

Day2A::Day2A()
{
}

Day2A::~Day2A()
{
}

void Day2A::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day2/Day2a_test.txt" : "Day2/Day2a.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString, ','))
    {
        if (inputString.size() > 0)
        {
            const int inputInt = static_cast<int>(std::stoi(inputString, nullptr, 0));
            input.push_back(inputInt);
        }
    }
    inputStream.close();

    if (!testMode)
    {
        //before running the program, replace position 1 with the value 12 and replace position 2 with the value 2
        input.at(1) = 12;
        input.at(2) = 2;
    }
}

void Day2A::ProcessData()
{
    //std::cout << "        Before: ";
    //PrintVector();

    for (size_t i = 0; i < input.size(); i += 4)
    {
        if (1 == input.at(i))
        {
            // Opcode 1 adds together numbers read from two positions and stores the result in a third position. 
            input.at(input.at(i + 3)) = input.at(input.at(i + 1)) + input.at(input.at(i + 2));
        }
        else if (2 == input.at(i))
        {
            //Opcode 2 works exactly like opcode 1, except it multiplies the two inputs instead of adding them.
            input.at(input.at(i + 3)) = input.at(input.at(i + 1)) * input.at(input.at(i + 2));
        }
        else if (99 == input.at(i))
        {
            //99 means that the program is finished and should immediately halt.
            break;
        }
    }

    //std::cout << "        After:  ";
    //PrintVector();
}

void Day2A::SaveOutput()
{
    std::cout << "Result: " << input.at(0) << std::endl;
}

void Day2A::PrintVector()
{
    std::for_each(input.begin(),
        input.end(),
        [](const auto &elem)
    {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}