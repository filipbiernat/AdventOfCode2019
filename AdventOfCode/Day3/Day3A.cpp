#include "Day3A.h"

Day3A::Day3A()
{
}

Day3A::~Day3A()
{
}

void Day3A::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day3/Day3a_test.txt" : "Day3/Day3a.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString))
    {
        std::vector<std::string> inputWire;
        std::stringstream ss(inputString);
        while (std::getline(ss, inputString, ','))
        {
            if (inputString.size() > 0)
            {
                inputWire.push_back(inputString);
            }
        }
        input.push_back(inputWire);
    }
    inputStream.close();
}

void Day3A::ProcessData()
{
    auto wire1 = FillWire(input.at(0));
    auto wire2 = FillWire(input.at(1));
 
    std::vector<std::pair<int, int>> wireIntersections;
    std::sort(wire1.begin(), wire1.end());
    std::sort(wire2.begin(), wire2.end());

    std::set_intersection(wire1.begin(),
        wire1.end(),
        wire2.begin(),
        wire2.end(),
        back_inserter(wireIntersections));

    std::vector<int> distance;
    std::transform(wireIntersections.begin(),
        wireIntersections.end(),
        std::back_inserter(distance),
        [](const auto &elem)
    {
        //use the Manhattan distance for this measurement
        return std::abs(std::get<0>(elem)) + std::abs(std::get<1>(elem));
    });

    //find the intersection point closest to the central port
    //central port where they both start, this point does not count
    std::sort(distance.begin(), distance.end());
    std::nth_element(distance.begin(), distance.begin() + 1, distance.end(), std::less<int>());
    output = distance[1];
}

void Day3A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

std::vector<std::pair<int, int>> Day3A::FillWire(std::vector<std::string> wireInput)
{
    std::vector<std::pair<int, int>> wire;
    wire.push_back(std::make_pair(0, 0));

    for (auto& instruction : wireInput)
    {
        FillNextSection(wire, instruction);
    }
    return wire;
}

void Day3A::FillNextSection(std::vector<std::pair <int, int> >& coordinates, std::string& instruction)
{
    auto direction = instruction.substr(0, 1);
    auto distance = stoi(instruction.substr(1));
    for (int i = 0; i < distance; ++i)
    {
        coordinates.push_back(GetNextStep(coordinates.back(), direction));
    }
};

std::pair<int, int> Day3A::GetNextStep(std::pair<int, int>& previousStep, std::string direction)
{
    auto nextStep(previousStep);

    if (direction == "L")
    {
        --std::get<0>(nextStep);
    }
    else if (direction == "R")
    {
        ++std::get<0>(nextStep);
    }
    else if (direction == "U")
    {
        ++std::get<1>(nextStep);
    }
    else if (direction == "D")
    {
        --std::get<1>(nextStep);
    }

    return nextStep;
}
