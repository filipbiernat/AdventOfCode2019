#include "Day6A.h"

Day6A::Day6A()
{
}

Day6A::~Day6A()
{
}

void Day6A::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day6/Day6A_test.txt" : "Day6/Day6A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString))
    {
        std::vector<std::string> inputLine;
        std::stringstream ss(inputString);
        while (std::getline(ss, inputString, ')'))
        {
            if (inputString.size() > 0)
            {
                inputLine.push_back(inputString);
            }
        }
        //In the map data, this orbital relationship is written AAA)BBB, which means "BBB is in orbit around AAA".
        input[inputLine.at(0)].insert(inputLine.at(1));
    }
    inputStream.close();
}

void Day6A::ProcessData()
{
    //What is the total number of direct and indirect orbits in your map data?
    output = CountOrbits("COM", 0);
}

void Day6A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

int Day6A::CountOrbits(std::string node, int level)
{
    int orbits = level;
    for (auto& elem : input[node])
    {
        orbits += CountOrbits(elem, level + 1);
    }
    return orbits;
}
