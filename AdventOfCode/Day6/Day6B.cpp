#include "Day6B.h"

Day6B::Day6B()
{
}

Day6B::~Day6B()
{
}

void Day6B::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day6/Day6B_test.txt" : "Day6/Day6A.txt";

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

void Day6B::ProcessData()
{
    //What is the minimum number of orbital transfers required to move from the object YOU are orbiting to the object SAN is orbiting? 
    output = std::get<0>(CountOrbits("COM", 0)) - 2;
}

void Day6B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

std::tuple<int, bool, bool> Day6B::CountOrbits(std::string node, int level)
{
    int orbits = 0;
    bool hasSanta = "SAN" == node;
    bool hasYou = "YOU" == node;

    for (auto& elem : input[node])
    {
        auto result = CountOrbits(elem, level + 1);
        orbits += std::get<0>(result);
        hasSanta = hasSanta || std::get<1>(result);
        hasYou = hasYou || std::get<2>(result);
    }

    //Increment only if has "SAN" or has "YOU". Not if both!
    if ((hasSanta || hasYou) && (hasSanta != hasYou))
    {
        ++orbits;
    }

    return std::make_tuple(orbits, hasSanta, hasYou);
}